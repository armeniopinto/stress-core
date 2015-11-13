/*
 * @file Motion.h
 * @brief The library that deals with the robot's movement.
 * @author Arménio Pinto
 *
 * Copyright (C) 2015 by Arménio Pinto.
 * Please read the file LICENSE for the license details.
 */

#ifndef MOTION_H_
#define MOTION_H_

#include "Runtime.h"
#include "Expression.h"

class Motion {
public:
	/** @brief The possible motion speeds. */
	enum Speed {
		SLOW, NORMAL, FAST
	};

	Motion(Runtime& runtime, Expression& expression,
			MotionPerception& perception);

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

	/** @brief Moves the robot forward at a specific speed. */
	void go(Speed speed);

	/** @brief Moves the robot backwards. */
	void reverse();

	/** @brief Moves the robot backwards at a specific speed. */
	void reverse(Speed speed);

	/** @brief Rotates the robot to the left indefinitely. */
	void turnLeft(Speed speed);

	/** @brief Rotates the robot to the left for an angle. */
	void turnLeft(int angle);

	/** @brief Rotates the robot to the right indefinitely. */
	void turnRight(Speed speed);

	/** @brief Turns Rotate robot to the right for an angle. */
	void turnRight(int angle);

private:
	Runtime& _runtime;
	Expression& _expression;
	MotionPerception& _perception;
};

#endif
