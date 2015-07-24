/*
 * @file Motion.cpp
 * @brief See Motion.h
 * @author Arménio Pinto
 *
 * Copyright (C) 2015 by Arménio Pinto
 * Please read the file LICENSE for the license details.
 */

#include "Motion.h"

Servo leftServo;
Servo rightServo;

Motion::Motion(Runtime& runtime, Expression& expression) :
		_runtime(runtime), _expression(expression) {
}

void Motion::init() {
	leftServo.attach(LEFT_SERVO_PIN);
	rightServo.attach(RIGHT_SERVO_PIN);
	freeze();
	_expression.say("Motion INIT OK");
}

void Motion::setLeft(int duty) {
	leftServo.writeMicroseconds(duty);
}

void Motion::setRight(int duty) {
	rightServo.writeMicroseconds(duty);
}

void Motion::freeze() {
	setLeft(LEFT_SERVO_NEUTRAL);
	setRight(RIGHT_SERVO_NEUTRAL);
}

void Motion::stop() {
	freeze();
}

void Motion::go() {
	setLeft(LEFT_SERVO_NEUTRAL - LEFT_SERVO_FULL);
	setRight(RIGHT_SERVO_NEUTRAL + RIGHT_SERVO_FULL);
}

void Motion::reverse() {
	setLeft(LEFT_SERVO_NEUTRAL + LEFT_SERVO_FULL);
	setRight(RIGHT_SERVO_NEUTRAL - RIGHT_SERVO_FULL);
}

void Motion::rotateLeft() {
	setLeft(LEFT_SERVO_NEUTRAL + LEFT_SERVO_FULL);
	setRight(RIGHT_SERVO_NEUTRAL + RIGHT_SERVO_FULL);
}

void Motion::rotateLeft(int millis) {
	rotateLeft();
	delay(millis);
	stop();
}

void Motion::rotateRight() {
	setLeft(LEFT_SERVO_NEUTRAL - LEFT_SERVO_FULL);
	setRight(RIGHT_SERVO_NEUTRAL - RIGHT_SERVO_FULL);
}

void Motion::rotateRight(int millis) {
	rotateRight();
	delay(millis);
	stop();
}
