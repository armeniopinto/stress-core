/*
 * @file Command.h
 * @brief The library that deals with the robot's command handling.
 * @author Arménio Pinto
 *
 * Copyright (C) 2016 by Arménio Pinto.
 * Please read the file LICENSE for the license details.
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include "ArduinoJson.h"

#include "Runtime.h"
#include "OrientationPerception.h"

class Command {
public:
	Command(Runtime& runtime, OrientationPerception& orientation);

	void init();

	String handle(String command);

private:
	Runtime& _runtime;
	OrientationPerception& _orientation;

	void echo();

	void getOrientation(JsonObject& response);
};

#endif
