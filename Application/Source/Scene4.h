#ifndef SCENE_4_H
#define SCENE_4_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "GL\glew.h"
#include "shader.hpp"
#include <cmath>

class Scene4 : public Scene {
	enum GEOMETRY_TYPE {
		GEO_AXES = 0,
		GEO_QUAD,
		GEO_CUBE,
		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE {
		U_MVP = 0,
		U_TOTAL
	};
	Mesh* meshList[NUM_GEOMETRY];
private:
	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_indexBuffer[NUM_GEOMETRY];
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
	Camera camera;
public:
	Scene4();
	~Scene4();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	virtual void SetToIdentity();
};

#endif