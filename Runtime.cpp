/*
 * @file Runtime.cpp
 * @brief See Runtime.h
 * @author Arménio Pinto
 *
 * Copyright (C) 2015 by Arménio Pinto
 * Please read the file LICENSE for the license details.
 */

#include "Runtime.h"

Runtime::Runtime(Expression& expression) :
		_expression(expression) {
}

void Runtime::init() {
	_expression.say("Runtime INIT OK");
}

void Runtime::halt() {
	_expression.say("Bye.");
	_expression.say("HALT");
	cli();
	sleep_enable()
	;
	sleep_cpu()
	;
}
