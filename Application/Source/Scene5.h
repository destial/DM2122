#ifndef SCENE_5_H
#define SCENE_5_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "GL\glew.h"
#include "shader.hpp"
#include <cmath>

class Scene5 : public Scene {
	enum GEOMETRY_TYPE {
		GEO_AXES = 0,
		GEO_SUN,
		GEO_MERCURY,
		GEO_MOON,
		GEO_EARTH,
		GEO_RING,
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
	float rotateAngle2;
	float translateX;
	float translateY;
	float scaleAll;
	bool reverse;
	bool up;
	bool side;
	bool scaling;
	float r, g, b;
	MS modelStack, viewStack, projectionStack;
	Camera camera;
public:
	Scene5();
	~Scene5();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	void SetToIdentity();
};

#endif