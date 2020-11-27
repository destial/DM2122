#ifndef MATERIAL_H
#define MATERIAL_H

struct Component {
	float r, g, b;
	Component(float r = 0.1f, float g = 0.1f, float b = 0.1f) {
		Set(r, g, b);
	}
	void Set(float r, float g, float b) {
		this->r = r; this->g = g; this->b = b;
	}
};

struct Material {
	Component kAmbient;
	Component kDiffuse;
	Component kSpecular;
	float kShininess;
	Material() {
		this->kAmbient.Set(0.f, 0.f, 0.f);
		this->kAmbient.Set(0.f, 0.f, 0.f);
		this->kSpecular.Set(0.f, 0.f, 0.f);
		this->kShininess = 1.f;
	};
};

#endif