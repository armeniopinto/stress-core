/*
 * @file Sensorimotor.h
 * @brief Combines the perception and motion components.
 * @author Arménio Pinto
 *
 * Copyright (C) 2015, 2016 by Arménio Pinto.
 * Please read the file LICENSE for the license details.
 */

#ifndef SENSORIMOTOR_H_
#define SENSORIMOTOR_H_

#include "Arduino.h"

#include "Runtime.h"
#include "Perception.h"
#include "Motion.h"

class Sensorimotor {
public:
	Sensorimotor(Runtime& runtime, Perception& perception, Motion& motion);

	void init();

	void loop();

	void keepDirection();

	void dance();

private:
	Runtime& _runtime;
	Perception& _perception;
	Motion& _motion;

	bool movingLeft, movingRight;
};

#endif
