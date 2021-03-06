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
#include "EnvironmentPerception.h"
#include "OrientationPerception.h"

class Perception {
public:
	Perception(Runtime& runtime);

	void init();

	EnvironmentPerception environment;
	OrientationPerception orientation;
};

#endif
