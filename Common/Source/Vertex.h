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
};

struct Transform {
	float rotate;
	float translateX;
	float translateY;
	float translateZ;
	float scale;
	Transform(float r = 0, float tX = 0, float tY = 0, float tZ = 0, float s = 1) {
		Set(r, tX, tY, tZ, s);
	}
	void Set(float r, float tX, float tY, float tZ, float s) {
		this->rotate = r;
		this->translateX = tX;
		this->translateY = tY;
		this->translateZ = tZ;
		this->scale = s;
	}
	void Set(Transform& t) {
		this->rotate = t.rotate;
		this->translateX = t.translateX;
		this->translateY = t.translateY;
		this->translateZ = t.translateZ;
		this->scale = t.scale;
	}
};

struct TexCoord {
	float u, v;
	TexCoord(float u = 0, float v = 0) {
		Set(u, v);
	}
	void Set(float u, float v) {
		this->u = u;
		this->v = v;
	}
};

struct Vertex {
	Position pos;
	Color color;
	Vector3 normal;
	TexCoord texCoord;
};

#endif