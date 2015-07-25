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
#include "SoftwareSerial.h"

#define RX_PIN 11
#define TX_PIN 12

class Runtime {
public:
	Runtime();

	void init();

	/** @brief Halts the robot's platform. */
	void halt();

	/** @brief Prints a message to the available outputs. */
	void println(String message);

private:
	/** @brief The virtual serial port. */
	SoftwareSerial VSerial;
};

#endif
