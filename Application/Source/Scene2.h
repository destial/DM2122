#ifndef SCENE_2_H
#define SCENE_2_H

#include "Scene.h"
#include "Mtx44.h"
#include "GL\glew.h"
#include "shader.hpp"
#include <cmath>

class Scene2 : public Scene {
	enum GEOMETRY_TYPE {
		GEO_TRIANGLE_1,
		GEO_TRIANGLE_2,
		GEO_QUAD_1,
		GEO_QUAD_2,
		GEO_SPHERE_1,
		GEO_STAR_1,
		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE {
		U_MVP = 0,
		U_TOTAL
	};
private:
	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	float rotateAngle;
	float translateX;
	float translateY;
	float scaleAll;
	bool reverse;
	bool up;
	bool side;
	bool scaling;
	float r, g, b;
	Mtx44 translate, rotate, scale;
	Mtx44 model, view, projection;
	Mtx44 MVP;
public:
	Scene2();
	~Scene2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	virtual void Draw(GEOMETRY_TYPE type, GLenum e);
	virtual void SetToIdentity();
};

#endif