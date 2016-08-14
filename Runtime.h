/*
 * @file Runtime.h
 * @brief The library that deals with the robot's platform runtime.
 * @author Arménio Pinto
 *
 * Copyright (C) 2015, 2016 by Arménio Pinto.
 * Please read the file LICENSE for the license details.
 */

#ifndef RUNTIME_H_
#define RUNTIME_H_

#include "Arduino.h"
#include "avr/sleep.h"
#include "ArduinoJson.h"

#define SERIAL_SPEED 19200

#define EOL '\n'

#define PHASE_INIT F("INIT")
#define PHASE_CONN F("CONNECT")

#define STATE_OK F("OK")
#define STATE_FAILED F("FAILED")

class Runtime {
public:
	Runtime();

	void init();

	/** @brief Halts the robot's platform. */
	void halt();

	/** @brief Resets the robot's platform. */
	void reset();

	/** @brief Prints a message to the available outputs. */
	void println(String message);

	/**
	 * @brief Reads a message from the available inputs.
	 *
	 * @return the message or an empty string, if none was available.
	 */
	String readln();

	/**
	 * @brief Notifies a component's state.
	 */
	void notifyState(String component, String phase, String state);

};

#endif
