/*
 * @file Expression.cpp
 * @brief See expression.h
 * @author Arménio Pinto
 *
 * Copyright (C) 2015 by Arménio Pinto
 * Please read the file LICENSE for the license details.
 */

#include "Expression.h"

Expression::Expression() :
		VSerial(RX_PIN, TX_PIN) {
}

void Expression::init() {
	Serial.begin(9600);
	VSerial.begin(9600);
	say("Expression INIT OK");
}

void Expression::say(String something) {
	Serial.println(something);
	VSerial.println(something);
}
