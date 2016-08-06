/*
 * @file Perception.cpp
 * @brief See Perception.h
 * @author Arménio Pinto
 *
 * Copyright (C) 2015, 2016 by Arménio Pinto.
 * Please read the file LICENSE for the license details.
 */

#include "Perception.h"

Perception::Perception(Runtime& runtime) :
		environment(runtime), orientation(runtime) {
}

void Perception::init() {
	environment.init();
	orientation.init();
}
