/*
 * @file EnvironmentPerception.h
 * @brief The library that deals with the robot's perception of the environment.
 * @author Arménio Pinto
 *
 * Copyright (C) 2015 by Arménio Pinto.
 * Please read the file LICENSE for the license details.
 */

#ifndef ENVIRONMENT_PERCEPTION_H_
#define ENVIRONMENT_PERCEPTION_H_

#include "Arduino.h"

#include "Runtime.h"
#include "Expression.h"

#define DOWN_LEFT_IR_SENSOR_PIN A1
#define DOWN_RIGHT_IR_SENSOR_PIN A2
#define FRONT_IR_SENSOR_PIN A3

/** The front IR sensor minimum output voltage. */
#define FRONT_IR_SENSOR_MIN_V 0.3f

/** The front IR sensor maximum output voltage. */
#define FRONT_IR_SENSOR_MAX_V 3.2f

/** The number of reference samples used for the front IR sensor. */
#define FRONT_IR_SENSOR_N_REF_SAMPLES 12

/** The front IR sensor inverse of distance reference values. */
const float FRONT_IR_SENSOR_REF_1D[12] = { 1.0f / 80.0f, 1.0f / 50.0f, 1.0f
		/ 40.0f, 1.0f / 30.0f, 1.0f / 25.0f, 1.0f / 20.0f, 1.0f / 15.0f, 1.0f
		/ 10.0f, 1.0f / 8.0f, 1.0f / 7.0f, 1.0f / 6.0f, 1.0f / 5.0f };

/** The front IR sensor voltage reference values. */
const float FRONT_IR_SENSOR_REF_V[12] = { 0.4f /*80*/, 0.6f /*50*/,
		0.74f /*40*/, 0.92f /*30*/, 1.09f /*25*/, 1.3f /*20*/, 1.62f /*15*/,
		2.3f /*10*/, 2.72f /*8*/, 2.99f /*7*/, 3.15f /*6*/, 3.09f /*5*/};

/** The IR sensor voltage when there are no obstacles or there's over 80cm. */
#define IR_SENSOR_80CM_V 0.44f

/** The IR sensor voltages when there's an obstacle at 10cm. */
#define IR_SENSOR_10CM_V 2.32f

/** The number of IR sensor samples to take on each read. */
#define IR_SENSOR_N_SAMPLES 20

class EnvironmentPerception {
public:
	enum Down {
		NONE, LEFT, RIGHT, BOTH
	};

	EnvironmentPerception(Runtime& runtime, Expression& expression);

	void init();

	/**
	 * @brief Detects an object in front of the proximity sensor.
	 *
	 * @return the object's distance (up to 80cm) of -1 if there's no object (or it's over 80cm).
	 */
	float lookAhead();

	/**
	 * @brief Detects ground beneath the robot.
	 *
	 * @return true of there's ground, otherwise false.
	 */
	Down lookDown();

	/**
	 * @brief Reads a message from the default input.
	 *
	 * @return the heard message or NULL, if none was available.
	 */
	String hear();

private:
	Runtime& _runtime;
	Expression& _expression;
};

#endif
