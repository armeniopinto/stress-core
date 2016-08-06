/*
 * @file OrientationPerception.cpp
 * @brief See OrientationPerception.h
 * @author Arménio Pinto
 *
 * Copyright (C) 2015, 2016 by Arménio Pinto.
 * Please read the file LICENSE for the license details.
 */

#include "OrientationPerception.h"
#include "contrib/MPU6050_6Axis_MotionApps20.h"

MPU6050 mpu;

/** Indicates when DMP data is available. */
volatile bool mpuInterrupt = false;
void dmpDataReady() {
	mpuInterrupt = true;
}

OrientationPerception::OrientationPerception(Runtime& runtime) :
		_runtime(runtime) {
	packetSize = 0;
}

void OrientationPerception::init() {
	Wire.begin();
	TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)

	mpu.initialize();
	if (!mpu.testConnection()) {
		_runtime.notifyState("MPU6050", "CONNECT", "FAILED");
		_runtime.halt();
	}
	_runtime.notifyState("MPU6050", "CONNECT", "OK");

	uint8_t status = mpu.dmpInitialize();
	if (status != 0) {
		_runtime.notifyState("MPU6050", "INIT", "FAILED " + status);
		_runtime.halt();
	}
	_runtime.notifyState("MPU6050", "INIT", "OK");

	mpu.setXGyroOffset(MPU6050_GYRO_X_OFFSET);
	mpu.setYGyroOffset(MPU6050_GYRO_Y_OFFSET);
	mpu.setZGyroOffset(MPU6050_GYRO_Z_OFFSET);
	mpu.setZAccelOffset(MPU6050_ACCEL_Z_OFFSET);

	mpu.setDMPEnabled(true);
	attachInterrupt(0, dmpDataReady, RISING);
	packetSize = mpu.dmpGetFIFOPacketSize();
	_runtime.notifyState("MPU6050", "DMP", "OK");

	_runtime.notifyState("MotionPerception", "INIT", "OK");
}

float* OrientationPerception::getOrientation() {
	// TODO: implement a timeout.
	while (!mpuInterrupt) {
	}
	mpuInterrupt = false;

	uint8_t status = mpu.getIntStatus();
	uint16_t count = mpu.getFIFOCount();
	if ((status & 0x10) || count == 1024) {
		mpu.resetFIFO();
		return getOrientation();
	}

	if (status & 0x02) {
		// Waits until enough data is available.
		while (count < packetSize) {
			count = mpu.getFIFOCount();
		}

		uint8_t buffer[64];
		mpu.getFIFOBytes(buffer, packetSize);

		Quaternion q;
		VectorFloat gravity;
		static float ypr[3];
		mpu.dmpGetQuaternion(&q, buffer);
		mpu.dmpGetGravity(&gravity, &q);
		mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
		ypr[0] = ypr[0] * 180 / M_PI;
		ypr[1] = ypr[1] * 180 / M_PI;
		ypr[2] = ypr[2] * 180 / M_PI;
		return ypr;

	} else {
		return getOrientation();
	}
}
