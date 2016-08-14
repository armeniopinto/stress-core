/*
 * @file Sensorimotor.cpp
 * @brief See Sensorimotor.h.
 * @author Arménio Pinto
 *
 * Copyright (C) 2015, 2016 by Arménio Pinto.
 * Please read the file LICENSE for the license details.
 */

#include "Sensorimotor.h"

#include "Arduino.h"

#define COMPONENT_NAME F("Sensorimotor")

Sensorimotor::Sensorimotor(Runtime& runtime, Perception& perception,
		Motion& motion) :
		_runtime(runtime), _perception(perception), _motion(motion) {
	movingLeft = false;
	movingRight = false;
}

void Sensorimotor::init() {
	_runtime.notifyState(COMPONENT_NAME, PHASE_INIT, STATE_OK);
}

#define moving (movingLeft || movingRight)

void Sensorimotor::keepDirection() {
	float* orientation = _perception.orientation.getOrientation();
	float yaw = orientation[0];

	if (yaw < -10.0f) {
		if (!moving || movingLeft) {
			_motion.turnRight(_motion.NORMAL);
			movingLeft = false;
			movingRight = true;
		}
	} else if (yaw > 10.0f) {
		if (!moving || movingRight) {
			_motion.turnLeft(_motion.NORMAL);
			movingLeft = true;
			movingRight = false;
		}
	} else if (moving) {
		_motion.stop();
		movingLeft = false;
		movingRight = false;
	}
}

void Sensorimotor::dance() {
	_motion.go();
	delay(2000);
	_motion.reverse();
	delay(2000);
	_motion.turnLeft(90);
	_motion.go();
	delay(2000);
	_motion.reverse();
	delay(2000);
	_motion.turnRight(180);
	_motion.go();
	delay(2000);
	_motion.reverse();
	delay(2000);
	_motion.turnLeft(90);
	_motion.reverse();
	delay(2000);
	_motion.go();
	delay(2000);
	_motion.stop();
}
