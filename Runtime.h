/*
 * @file Runtime.h
 * @brief The library that deals with the robot's platform runtime.
 * @author Arménio Pinto
 *
 * Copyright (C) 2015 by Arménio Pinto
 * Please read the file LICENSE for the license details.
 */

#ifndef RUNTIME_H_
#define RUNTIME_H_

#include "Arduino.h"
#include "avr/sleep.h"

#include "Expression.h"

class Runtime {
public:
	Runtime(Expression& expression);

	void init();

	/** @brief Halts the robot's platform. */
	void halt();

private:
	Expression& _expression;
};

#endif
