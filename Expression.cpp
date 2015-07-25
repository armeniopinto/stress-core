/*
 * @file Expression.cpp
 * @brief See expression.h
 * @author Arm�nio Pinto
 *
 * Copyright (C) 2015 by Arm�nio Pinto
 * Please read the file LICENSE for the license details.
 */

#include "Expression.h"

Expression::Expression(Runtime& runtime) :
		_runtime(runtime) {
}

void Expression::init() {
	say("Expression INIT OK");
}

void Expression::say(String something) {
	_runtime.println(something);
}
