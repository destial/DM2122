#ifndef LIGHT_H
#define LIGHT_H

#include "Vertex.h"
struct Light {
	Position pos;
	Color color;
	float power;
	float kC, kL, kQ;
	void Set(Position pos, Color color, float power, float kC, float kL, float kQ) {
		this->pos = pos;
		this->color = color;
		this->power = power;
		this->kC = kC;
		this->kL = kL;
		this->kQ = kQ;
	}
	Light() {
		this->pos.Set(0, 20, 0);
		this->color.Set(1, 1, 1);
		Set(pos, color, 1, 1.f, 0.01f, 0.001f);
	}
};

#endif
