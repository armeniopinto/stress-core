/*
 * @file StressCore.cpp
 * @brief See StressCore.h.
 * @author Arménio Pinto
 *
 * Copyright (C) 2015, 2016 by Arménio Pinto.
 * Please read the file LICENSE for the license details.
 */

#include "Arduino.h"

#include "StressCore.h"

#define COMPONENT_NAME F("Core")

Runtime runtime;
Expression expression = Expression(runtime);
Perception perception = Perception(runtime);
Motion motion = Motion(runtime, perception.orientation);
Command command = Command(runtime, perception.orientation);

void setup() {
	runtime.init();
	expression.init();
	perception.init();
	motion.init();
	motion.freeze();
	command.init();
	runtime.notifyState(COMPONENT_NAME, PHASE_INIT, STATE_OK);
}

bool movingLeft = false;
bool movingRight = false;
#define moving (movingLeft || movingRight)

void keep_direction() {
	float* orientation = perception.orientation.getOrientation();
	float yaw = orientation[0];

	if (yaw < -10.0f) {
		if (!moving || movingLeft) {
			motion.turnRight(motion.NORMAL);
			movingLeft = false;
			movingRight = true;
			expression.say("right");
		}
	} else if (yaw > 10.0f) {
		if (!moving || movingRight) {
			motion.turnLeft(motion.NORMAL);
			expression.say("left");
			movingLeft = true;
			movingRight = false;
		}
	} else if (moving) {
		expression.say("stop");
		motion.stop();
		movingLeft = false;
		movingRight = false;
	}
}

bool going = false;

void avoid_falls() {
	EnvironmentPerception::Down down = perception.environment.lookDown();
	if (down == perception.environment.NONE) {
		motion.freeze();
		motion.reverse();
		delay(200);
		motion.stop();
		motion.turnLeft(90);
		going = false;
	} else if (down == perception.environment.LEFT) {
		// Only the left-side sensor detects ground.
		motion.freeze();
		motion.turnLeft(30);
		going = false;
	} else if (down == perception.environment.RIGHT) {
		// Only the right-side sensor detects ground.
		motion.freeze();
		motion.turnRight(30);
		going = false;
	} else {
		if (!going) {
			motion.go();
			going = true;
		}
	}
}

void avoid_obstacles() {
	float distance = perception.environment.lookAhead();
	if (distance != -1 && distance < 10.0f) {
		motion.freeze();
		motion.turnLeft(45);
		going = false;
	} else {
		if (!going) {
			motion.go();
			going = true;
		}
	}
}

void handleCommand() {
	String message = perception.environment.hear();
	if (message != "") {
		expression.say(command.handle(message));
	}
}

void loop() {
	handleCommand();
}
