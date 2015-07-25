/*
 * @file Expression.h
 * @brief The library that deals with the robot's expression capabilities.
 * @author Arménio Pinto
 *
 * Copyright (C) 2015 by Arménio Pinto
 * Please read the file LICENSE for the license details.
 */

#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include "Arduino.h"

#include "Runtime.h"

class Expression {
public:
	Expression(Runtime& runtime);

	void init();

	/**
	 * @brief Uses the default expression means to say something.
	 *
	 * @param something the message to say.
	 */
	void say(String something);

private:
	Runtime& _runtime;
};

#endif
