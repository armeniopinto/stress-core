/*
 * @file MotionPerception.h
 * @brief The library that deals with the robot's motion perception.
 * @author Arm�nio Pinto
 *
 * Copyright (C) 2015 by Arm�nio Pinto
 * Please read the file LICENSE for the license details.
 */

#ifndef MOTION_PERCEPTION_H_
#define MOTION_PERCEPTION_H_

#include "Arduino.h"
#include "Wire.h"

#include "Runtime.h"
#include "Expression.h"

// The sensor offsets obtained from calibration.
#define MPU6050_GYRO_X_OFFSET 42
#define MPU6050_GYRO_Y_OFFSET 22
#define MPU6050_GYRO_Z_OFFSET 32
#define MPU6050_ACCEL_Z_OFFSET 1298

class MotionPerception {
public:
	MotionPerception(Runtime& runtime, Expression& expression);

	void init();

	/**
	 * @brief Returns the robot's orientation.
	 *
	 * @return the orientation in yaw, pitch and roll angles in degrees.
	 */
	float* getOrientation();

private:
	Runtime& _runtime;
	Expression& _expression;
	uint16_t packetSize;
};

#endif
