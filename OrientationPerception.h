/*
 * @file OrientationPerception.h
 * @brief The library that deals with the robot's orientation perception.
 * @author Arménio Pinto
 *
 * Copyright (C) 2015, 2016 by Arménio Pinto.
 * Please read the file LICENSE for the license details.
 */

#ifndef ORIENTATION_PERCEPTION_H_
#define ORIENTATION_PERCEPTION_H_

#include "Arduino.h"
#include "Wire.h"

#include "Runtime.h"

// The sensor offsets obtained from calibration.
#define MPU6050_GYRO_X_OFFSET 71
#define MPU6050_GYRO_Y_OFFSET 16
#define MPU6050_GYRO_Z_OFFSET 26
#define MPU6050_ACCEL_Z_OFFSET 1298

class OrientationPerception {
public:
	OrientationPerception(Runtime& runtime);

	void init();

	/**
	 * @brief Returns the robot's orientation.
	 *
	 * @return the orientation in yaw, pitch and roll angles in degrees.
	 */
	float* getOrientation();

private:
	Runtime& _runtime;
	uint16_t packetSize;
};

#endif
