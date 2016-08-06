/*
 * @file Runtime.cpp
 * @brief See Runtime.h
 * @author Arménio Pinto
 *
 * Copyright (C) 2015 by Arménio Pinto.
 * Please read the file LICENSE for the license details.
 */

#include "Runtime.h"

Runtime::Runtime() :
		VSerial(RX_PIN, TX_PIN) {
}

void Runtime::init() {
	Serial.begin(SERIAL_SPEED);
	VSerial.begin(VSERIAL_SPEED);
	notifyState("Runtime", "INIT", STATE_OK);
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
	if (Serial.available() > 0) {
		return Serial.readStringUntil(EOL);
	} else if (VSerial.available() > 0) {
		return VSerial.readStringUntil(EOL);
	} else {
		return "";
	}
}

void Runtime::notifyState(String component, String phase, String state) {
	StaticJsonBuffer<256> buffer;
	JsonObject& root = buffer.createObject();
	root["type"] = "Event";
	JsonObject& data = buffer.createObject();
	root["data"] = data;
	data["component"] = component;
	data["phase"] = phase;
	data["state"] = state;

	char text[256];
	root.printTo(text, sizeof(text));
	Serial.println(text);
	VSerial.println(text);
}
