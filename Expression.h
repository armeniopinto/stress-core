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
#include "SoftwareSerial.h"

#define RX_PIN 11
#define TX_PIN 12

class Expression {
public:
	Expression();

	void init();

	/**
	 * @brief Uses the default expression means to say something.
	 *
	 * @param something the message to say.
	 */
	void say(String something);

private:
	SoftwareSerial VSerial;
};

#endif
