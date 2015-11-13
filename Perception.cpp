/*
 * @file Perception.cpp
 * @brief See Perception.h
 * @author Arménio Pinto
 *
 * Copyright (C) 2015 by Arménio Pinto.
 * Please read the file LICENSE for the license details.
 */

#include "Perception.h"

Perception::Perception(Runtime& runtime, Expression& expression) :
		environment(runtime, expression), motion(runtime, expression) {
}

void Perception::init() {
	environment.init();
	motion.init();
}
