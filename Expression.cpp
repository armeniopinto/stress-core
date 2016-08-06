/*
 * @file Expression.cpp
 * @brief See expression.h
 * @author Arménio Pinto
 *
 * Copyright (C) 2015, 2016 by Arménio Pinto.
 * Please read the file LICENSE for the license details.
 */

#include "Expression.h"

#define MPU_COMP_NAME F("Expression")

Expression::Expression(Runtime& runtime) :
		_runtime(runtime) {
}

void Expression::init() {
	_runtime.notifyState(MPU_COMP_NAME, PHASE_INIT, STATE_OK);
}

void Expression::say(String something) {
	_runtime.println(something);
}
