/*
 * @file Motion.h
 * @brief The library that deals with the robot's movement.
 * @author Arménio Pinto
 *
 * Copyright (C) 2015 by Arménio Pinto
 * Please read the file LICENSE for the license details.
 */

#ifndef MOTION_H_
#define MOTION_H_

#include "Arduino.h"
#include "Servo.h"

#include "Runtime.h"
#include "Expression.h"

#define LEFT_SERVO_PIN 9
#define RIGHT_SERVO_PIN 10

#define LEFT_SERVO_NEUTRAL 1416
#define RIGHT_SERVO_NEUTRAL 1390

#define LEFT_SERVO_FULL 300
#define RIGHT_SERVO_FULL 220

class Motion {
public:
	Motion(Runtime& runtime, Expression& expression);

	void init();

	/** @brief Sets the left servo duty cycle. */
	void setLeft(int duty);

	/** @brief Sets the left servo duty cycle. */
	void setRight(int duty);

	/** @brief Immediately (abruptly) stops the robot's movement. */
	void freeze();

	/** @brief Gracefully stops the robot's movement. */
	void stop();

	/** @brief Moves the robot forward. */
	void go();

	/** @brief Moves the robot backwards. */
	void reverse();

	/** @brief Rotates the robot to the left indefinitely. */
	void rotateLeft();

	/** @brief Rotates the robot to the left for an amount of time. */
	void rotateLeft(int millis);

	/** @brief Rotates the robot to the right indefinitely. */
	void rotateRight();

	/** Turns Rotate robot to the right for an amount of time. */
	void rotateRight(int millis);

private:
	Runtime& _runtime;
	Expression& _expression;
};

#endif
