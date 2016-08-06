/*
 * @file Command.cpp
 * @brief See Command.h
 * @author Arménio Pinto
 *
 * Copyright (C) 2015, 2016 by Arménio Pinto.
 * Please read the file LICENSE for the license details.
 */

#include "Arduino.h"

#include "Command.h"

#define COMPONENT_NAME F("Command")

Command::Command(Runtime& runtime, OrientationPerception& orientation) :
		_runtime(runtime), _orientation(orientation) {
}

void Command::init() {
	_runtime.notifyState(COMPONENT_NAME, PHASE_INIT, STATE_OK);
}

void Command::echo() {
}

void Command::getOrientation(JsonObject& response) {
	JsonObject& data = response["data"];
	float* ypr = _orientation.getOrientation();
	data["yaw"] = ypr[0];
	data["pitch"] = ypr[1];
	data["roll"] = ypr[2];
}

String Command::handle(String message) {
	StaticJsonBuffer<256> buffer;
	JsonObject& command = buffer.parseObject(message);
	if (strcmp(command["type"], "Request") == 0) {

		JsonObject& response = buffer.createObject();
		response["type"] = "Response";
		response["id"] = command["id"];
		response["data"] = buffer.createObject();

		if (strcmp(command["what"], "Echo") == 0) {
			echo();

		} else if (strcmp(command["what"], "GetOrientation") == 0) {
			getOrientation(response);
		}
		char text[256];
		response.printTo(text, sizeof(text));
		return String(text);
	}
	return "";
}
