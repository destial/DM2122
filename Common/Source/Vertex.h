#pragma once
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
	void Set(Color &color) {
		this->r = color.r;
		this->g = color.g;
		this->b = color.b;
	}
};

struct Vertex {
	Position pos;
	Color color;
};
