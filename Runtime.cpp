/*
 * @file Runtime.cpp
 * @brief See Runtime.h
 * @author Arménio Pinto
 *
 * Copyright (C) 2015, 2016 by Arménio Pinto.
 * Please read the file LICENSE for the license details.
 */

#include "Runtime.h"

#define COMPONENT_NAME F("Runtime")

#define ATTRIB_TYPE F("type")
#define ATTRIB_DATA F("data")
#define ATTRIB_COMP F("component")
#define ATTRIB_PHASE F("phase")
#define ATTRIB_STATE F("state")

Runtime::Runtime() :
		VSerial(RX_PIN, TX_PIN) {
}

void Runtime::init() {
	Serial.begin(SERIAL_SPEED);
	VSerial.begin(VSERIAL_SPEED);
	notifyState(COMPONENT_NAME, PHASE_INIT, STATE_OK);
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
	root[ATTRIB_TYPE] = "Event";
	JsonObject& data = buffer.createObject();
	root[ATTRIB_DATA] = data;
	data[ATTRIB_COMP] = component;
	data[ATTRIB_PHASE] = phase;
	data[ATTRIB_STATE] = state;

	char text[256];
	root.printTo(text, sizeof(text));
	Serial.println(text);
	VSerial.println(text);
}
