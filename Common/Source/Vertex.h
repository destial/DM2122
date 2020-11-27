#ifndef VERTEX_H
#define VERTEX_H

#include "Vector3.h"

struct Position {
	float x, y, z;
	Position(float x = 0, float y = 0, float z = 0) {
		Set(x, y, z);
	}
	void Set(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	void Set(Position& pos) {
		this->x = pos.x;
		this->y = pos.y;
		this->z = pos.z;
	}
};

struct Color {
	float r, g, b;
	Color(float r = 1, float g = 1, float b = 1) {
		Set(r, g, b);
	}
	void Set(float r, float g, float b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
	void Set(Color &color) {
		this->r = color.r;
		this->g = color.g;
		this->b = color.b;
	}
};

struct Transform {
	float rotate;
	float translateX;
	float translateY;
	float scale;
	Transform(float r = 0, float tX = 0, float tY = 0, float s = 1) {
		Set(r, tX, tY, s);
	}
	void Set(float r, float tX, float tY, float s) {
		this->rotate = r;
		this->translateX = tX;
		this->translateY = tY;
		this->scale = s;
	}
	void Set(Transform& t) {
		this->rotate = t.rotate;
		this->translateX = t.translateX;
		this->translateY = t.translateY;
		this->scale = t.scale;
	}
};

struct Vertex {
	Position pos;
	Color color;
	Vector3 normal;
};

#endif