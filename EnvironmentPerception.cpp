/*
 * @file EnvironmentPerception.cpp
 * @brief See EnvrionmentPerception.h
 * @author Arménio Pinto
 *
 * Copyright (C) 2015 by Arménio Pinto.
 * Please read the file LICENSE for the license details.
 */

#include "EnvironmentPerception.h"

EnvironmentPerception::EnvironmentPerception(Runtime& runtime,
		Expression& expression) :
		_runtime(runtime), _expression(expression) {
}

void EnvironmentPerception::init() {
	pinMode(FRONT_IR_SENSOR_PIN, INPUT);
	pinMode(DOWN_RIGHT_IR_SENSOR_PIN, INPUT);
	_expression.say("EnvironmentPerception INIT OK");
}

float EnvironmentPerception::lookAhead() {
	int sum = 0;
	for (int i = 0; i < IR_SENSOR_N_SAMPLES; i++) {
		sum += analogRead(FRONT_IR_SENSOR_PIN);
		delay(2);
	}
	int average = sum / IR_SENSOR_N_SAMPLES;

	float voltage = ((float) average) * (5.0f / 1023.0f);

	if (voltage < FRONT_IR_SENSOR_REF_V[1]) {
		return -1;
	} else if (voltage
			>= FRONT_IR_SENSOR_REF_V[FRONT_IR_SENSOR_N_REF_SAMPLES - 1]) {
		return 5.0;
	} else {
		float slope = 0.0f, vmin = 0.0f, dmin = 0.0f;
		for (int i = 2; i < FRONT_IR_SENSOR_N_REF_SAMPLES - 1; i++) {
			if (voltage < FRONT_IR_SENSOR_REF_V[i]) {
				vmin = FRONT_IR_SENSOR_REF_V[i - 1];
				float vmax = FRONT_IR_SENSOR_REF_V[i];
				dmin = FRONT_IR_SENSOR_REF_1D[i - 1];
				float dmax = FRONT_IR_SENSOR_REF_1D[i];
				slope = (dmax - dmin) / (vmax - vmin);
				break;
			}
		}

		// Line equation:
		return 1.0f / ((voltage - vmin) * slope + dmin);
	}
}

EnvironmentPerception::Down EnvironmentPerception::lookDown() {
	int leftValue = analogRead(DOWN_LEFT_IR_SENSOR_PIN);
	int rightValue = analogRead(DOWN_RIGHT_IR_SENSOR_PIN);
	if (leftValue < 800 && rightValue < 800) {
		return BOTH;
	} else if (leftValue < 800) {
		return LEFT;
	} else if (rightValue < 800) {
		return RIGHT;
	} else {
		return NONE;
	}
}

String EnvironmentPerception::hear() {
	return _runtime.readln();
}
