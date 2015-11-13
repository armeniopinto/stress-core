/*
 * @file StressCore.h
 * @brief The main file application.
 * @author Arménio Pinto
 *
 * Copyright (C) 2015 by Arménio Pinto.
 * Please read the file LICENSE for the license details.
 */

#ifndef STRESS_CORE_H_
#define STRESS_CORE_H_

#include "Arduino.h"

#include "Runtime.h"
#include "Expression.h"
#include "Perception.h"
#include "Motion.h"

#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
}
#endif

#endif
