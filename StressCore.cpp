/*
 * @file StressCore.cpp
 * @brief See StressCore.h.
 * @author Arménio Pinto
 *
 * Copyright (C) 2015 by Arménio Pinto
 * Please read the file LICENSE for the license details.
 */

#include "Arduino.h"
#include "StressCore.h"

Runtime runtime;
Expression expression = Expression(runtime);
Perception perception = Perception(runtime, expression);
Motion motion = Motion(runtime, expression);

void setup() {
	runtime.init();
	expression.init();
	perception.init();
	motion.init();
	motion.freeze();
}

bool movingLeft = false;
bool movingRight = false;
#define moving (movingLeft || movingRight)

void keep_direction() {
	float* orientation = perception.motion.getOrientation();
	float yaw = orientation[0];

	if (yaw < -10.0f) {
		if (!moving || movingLeft) {
			motion.rotateRight();
			movingLeft = false;
			movingRight = true;
			expression.say("right");
		}
	} else if (yaw > 10.0f) {
		if (!moving || movingRight) {
			motion.rotateLeft();
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

void loop() {
	keep_direction();
}
