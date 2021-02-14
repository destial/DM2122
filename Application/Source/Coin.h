#pragma once
#include "Vector3.h"
struct Coin {
	Coin() { up = rotate = collected = false; };
	~Coin() {};
	Vector3 position;
	bool up, rotate, collected;
};