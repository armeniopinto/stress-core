/*
 * @file Motion.cpp
 * @brief See Motion.h
 * @author Arménio Pinto
 *
 * Copyright (C) 2015, 2016 by Arménio Pinto.
 * Please read the file LICENSE for the license details.
 */

#include "Arduino.h"
#include "Servo.h"

#include "Motion.h"

#define MPU_COMP_NAME F("Motion")

#define LEFT_SERVO_PIN 9
#define RIGHT_SERVO_PIN 10

#define LEFT_SERVO_NEUTRAL 1416
#define RIGHT_SERVO_NEUTRAL 1390

Servo leftServo;
Servo rightServo;

int leftServoSpeeds[] = { 50, 200, 300 };
int rightServoSpeeds[] = { 40, 160, 220 };

Motion::Motion(Runtime& runtime, OrientationPerception& orientation) :
		_runtime(runtime), _orientation(orientation) {
}

void Motion::init() {
	leftServo.attach(LEFT_SERVO_PIN);
	rightServo.attach(RIGHT_SERVO_PIN);
	freeze();
_runtime.notifyState(MPU_COMP_NAME, PHASE_INIT, STATE_OK);
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
go(FAST);
}

void Motion::go(Speed speed) {
setLeft(LEFT_SERVO_NEUTRAL - leftServoSpeeds[speed]);
setRight(RIGHT_SERVO_NEUTRAL + rightServoSpeeds[speed]);
}

void Motion::reverse() {
reverse(FAST);
}

void Motion::reverse(Speed speed) {
setLeft(LEFT_SERVO_NEUTRAL + leftServoSpeeds[speed]);
setRight(RIGHT_SERVO_NEUTRAL - rightServoSpeeds[speed]);
}

void Motion::turnLeft(Speed speed) {
setLeft(LEFT_SERVO_NEUTRAL + leftServoSpeeds[speed]);
setRight(RIGHT_SERVO_NEUTRAL + rightServoSpeeds[speed]);
}

int adjustAngle(int angle) {
return (angle >= 0 ? angle : 360 + angle) % 360;
}

void Motion::turnLeft(int angle) {
int startYaw = adjustAngle(_orientation.getOrientation()[0]);
int stopYaw = adjustAngle(startYaw - angle);
turnLeft(NORMAL);
bool keepTurning = true;
while (keepTurning) {
	int yaw = adjustAngle(_orientation.getOrientation()[0]);
	keepTurning = yaw > stopYaw || (stopYaw > startYaw && yaw <= startYaw);
}
stop();
}

void Motion::turnRight(Speed speed) {
setLeft(LEFT_SERVO_NEUTRAL - leftServoSpeeds[speed]);
setRight(RIGHT_SERVO_NEUTRAL - rightServoSpeeds[speed]);
}

void Motion::turnRight(int angle) {
int startYaw = adjustAngle(_orientation.getOrientation()[0]);
int stopYaw = adjustAngle(startYaw + angle);
turnRight(NORMAL);
bool keepTurning = true;
while (keepTurning) {
	int yaw = adjustAngle(_orientation.getOrientation()[0]);
	keepTurning = yaw < stopYaw || (stopYaw < startYaw && yaw >= startYaw);
}
stop();
}
