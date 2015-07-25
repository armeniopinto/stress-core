/*
 * @file Runtime.cpp
 * @brief See Runtime.h
 * @author Arménio Pinto
 *
 * Copyright (C) 2015 by Arménio Pinto
 * Please read the file LICENSE for the license details.
 */

#include "Runtime.h"

Runtime::Runtime() :
		VSerial(RX_PIN, TX_PIN) {
}

void Runtime::init() {
	Serial.begin(9600);
	VSerial.begin(9600);
	println("Runtime INIT OK");
}

void Runtime::halt() {
	println("Bye.");
	println("HALT");
	cli();
	sleep_enable()
	;
	sleep_cpu()
	;
}

void Runtime::println(String message) {
	Serial.println(message);
	VSerial.println(message);
}

String Runtime::readln() {
	String s = "";
	bool havail = Serial.available() > 0;
	bool vavail = VSerial.available() > 0;
	if (havail || vavail) {
		while (true) {
			char c = havail ? Serial.read() : VSerial.read();
			if (c != '\n') {
				s.concat(c);
			} else {
				break;
			}
		}
		return s;
	}

	return s;
}
