/*
 * @file Runtime.cpp
 * @brief See Runtime.h
 * @author Arménio Pinto
 *
 * Copyright (C) 2015, 2016 by Arménio Pinto.
 * Please read the file LICENSE for the license details.
 */

#include "Runtime.h"

#include "avr/sleep.h"

#include "Perception.h"
#include "Motion.h"
#include "Sensorimotor.h"
#include "Expression.h"

Runtime runtime = Runtime();
Perception perception = Perception(runtime);
Motion motion = Motion(runtime, perception.orientation);
Sensorimotor sensorimotor = Sensorimotor(runtime, perception, motion);
Expression expression = Expression(runtime);

void setup() {
	runtime.init();
}

void loop() {
	runtime.loop();
}

#define COMPONENT_NAME F("Runtime")

#define ATTRIB_TYPE F("type")
#define ATTRIB_DATA F("data")
#define ATTRIB_COMP F("component")
#define ATTRIB_PHASE F("phase")
#define ATTRIB_STATE F("state")

Runtime::Runtime() {
}

void Runtime::init() {
	Serial.begin(SERIAL_SPEED);
	perception.init();
	motion.init();
	motion.freeze();
	sensorimotor.init();
	expression.init();
	notifyState(COMPONENT_NAME, PHASE_INIT, STATE_OK);
}

void Runtime::loop() {
	listenCommands();
}

void Runtime::halt() {
	notifyState(COMPONENT_NAME, PHASE_HALT, "BYE");
	cli();
	sleep_enable()
	;
	sleep_cpu()
	;
}

void (*resetHack)(void) = 0;

void Runtime::reset() {
	resetHack();
}

void Runtime::println(String message) {
	Serial.println(message);
}

String Runtime::readln() {
	if (Serial.available() > 0) {
		return Serial.readStringUntil(EOL);
	} else {
		return "";
	}
}

void Runtime::notifyState(String component, String phase, String state) {
	StaticJsonBuffer<256> buffer;
	JsonObject& root = buffer.createObject();
	root[ATTRIB_TYPE] = "Event";
	JsonObject& data = buffer.createObject();
	root[ATTRIB_DATA] = data;
	data[ATTRIB_COMP] = component;
	data[ATTRIB_PHASE] = phase;
	data[ATTRIB_STATE] = state;

	char text[256];
	root.printTo(text, sizeof(text));
	Serial.println(text);
}

void Runtime::listenCommands() {
	String message = perception.environment.hear();
	if (message != "") {
		expression.say(handleCommand(message));
	}
}

String Runtime::handleCommand(String message) {
	StaticJsonBuffer<256> buffer;
	JsonObject& command = buffer.parseObject(message);
	if (strcmp(command["type"], "Request") == 0) {

		JsonObject& response = buffer.createObject();
		response["type"] = "Response";
		response["id"] = command["id"];
		response["data"] = buffer.createObject();

		if (strcmp(command["what"], "Reset") == 0) {
			runtime.reset();

		} else if (strcmp(command["what"], "Tchau") == 0) {
			tchau(response);

		} else if (strcmp(command["what"], "Echo") == 0) {
			echo();

		} else if (strcmp(command["what"], "GetOrientation") == 0) {
			getOrientation(response, buffer);

		} else if (strcmp(command["what"], "Go") == 0) {
			motion.go();

		} else if (strcmp(command["what"], "Stop") == 0) {
			motion.stop();

		} else if (strcmp(command["what"], "Dance") == 0) {
			sensorimotor.dance();
		}

		char text[256];
		response.printTo(text, sizeof(text));
		return String(text);
	}
	return "";
}

void Runtime::echo() {
}

void Runtime::getOrientation(JsonObject& response, JsonBuffer& buffer) {
	JsonObject& data = response["data"];
	JsonObject& odata = buffer.createObject();
	data["orientation"] = odata;
	float* ypr = perception.orientation.getOrientation();
	odata["yaw"] = ypr[0];
	odata["pitch"] = ypr[1];
	odata["roll"] = ypr[2];
}

void Runtime::tchau(JsonObject& response) {
	response["type"] = "TchauAck";
}
