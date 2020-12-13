#ifndef ASSIGNMENTSCENE_H
#define ASSIGNMENTSCENE_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Material.h"
#include "GL\glew.h"
#include "shader.hpp"
#include <cmath>

class AssignmentScene : public Scene {
	enum GEOMETRY_TYPE {
		GEO_AXES = 0,
		GEO_SPHERE,
		GEO_SPHERE2,
		GEO_LIGHT,
		GEO_QUAD,
		GEO_CIRCLE,
		GEO_CYL,
		GEO_CONE,
		GEO_CUBE,
		GEO_TORUS,
		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE {
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,

		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,

		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,

		U_NUMLIGHTS,
		U_LIGHTENABLED,
		U_TOTAL,
	};
private:
	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_indexBuffer[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	Mesh* meshList[NUM_GEOMETRY];
	bool lighton, reverse, hit;
	Light light[1];
	MS modelStack, viewStack, projectionStack;
	Camera camera;
	Transform head, body, middle, leftarm, rightarm, nose, lefteye, righteye, hail;

	Color RED = Color(1.f, 0.f, 0.f);
	Color GREEN = Color(0.f, 1.f, 0.f);
	Color BLUE = Color(0.f, 0.f, 1.f);
	Color WHITE = Color(.9f, .9f, .9f);
	Color YELLOW = Color(1.f, 1.f, 0.f);
	Color PURPLE = Color(1.f, 0.f, 1.f);
	Color CYAN = Color(0.f, 1.f, 1.f);
	Color BROWN = Color(.6f, .1f, .2f);
	Color BLACK = Color(0.f, 0.f, 0.f);
	Color ORANGE = Color((195 / 255), (82 / 255), (20 / 255));
	void RenderMesh(Mesh* mesh, bool enableLight);
	void Reset();
public:
	AssignmentScene();
	~AssignmentScene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};

#endif