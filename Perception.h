/*
 * @file Perception.h
 * @brief The library that deals with the robot's sensors.
 * @author Arménio Pinto
 *
 * Copyright (C) 2015 by Arménio Pinto.
 * Please read the file LICENSE for the license details.
 */

#ifndef PERCEPTION_H_
#define PERCEPTION_H_

#include "Arduino.h"

#include "Runtime.h"
#include "Expression.h"
#include "EnvironmentPerception.h"
#include "MotionPerception.h"

class Perception {
public:
	Perception(Runtime& runtime, Expression& expression);

	void init();

	EnvironmentPerception environment;
	MotionPerception motion;
};

#endif
