#ifndef ASSIGNMENT_SCENE2_H
#define ASSIGNMENT_SCENE2_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Camera2.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Material.h"
#include "GL\glew.h"
#include "shader.hpp"
#include "Application.h"
#include <cmath>

class AssignmentScene2 : public Scene {
	enum GEOMETRY_TYPE {
		GEO_SPHERE,
		GEO_SPHERE2,
		GEO_CONE,
		GEO_SUN,
		GEO_CYL,

		GEO_CASTLEROOF,
		GEO_CASTLEWALL,
		GEO_CASTLEPILLAR,

		GEO_GLOCK,

		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,

		GEO_HOUSE1,
		GEO_HOUSE2,
		GEO_TREE,

		GEO_TREETOP,
		GEO_TREEBARK,

		GEO_GROUND,
		GEO_TEXT,
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
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_LIGHTENABLED,

		U_TEXT_ENABLED,
		U_TEXT_COLOR,
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
	Transform objects[NUM_GEOMETRY];
	Transform head, body, middle, leftarm, rightarm, nose, lefteye, righteye, hail, object;
	bool lighton, reverse, pickup, complete;
	Light light[1];
	MS modelStack, viewStack, projectionStack;
	Camera3 camera;
	float bounds;

	Color RED = Color(1.f, 0.f, 0.f);
	Color GREEN = Color(0.f, 1.f, 0.f);
	Color BLUE = Color(0.f, 0.f, 1.f);
	Color WHITE = Color(1.f, 1.f, 1.f);
	Color YELLOW = Color(1.f, 1.f, 0.f);
	Color PURPLE = Color(1.f, 0.f, 1.f);
	Color CYAN = Color(0.f, 1.f, 1.f);
	Color BROWN = Color(.6f, .1f, .2f);
	Color BLACK = Color(0.f, 0.f, 0.f);
	Color ORANGE = Color((195 / 255), (82 / 255), (20 / 255));
	Color GRAY = Color(0.4f, 0.4f, 0.4f);

	void RenderMesh(Mesh* mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderFacingText(Mesh* mesh, std::string text, Color color, float size, float x, float y, float z);
	void RenderImageOnScreen(Mesh* mesh, float size, float x, float y);
	void RenderGun();
	void RenderSkybox();
	void RenderA01Character(float x, float y, float z, float size, float rotate);
	void RenderCastle();
	void RenderTree(float x, float y, float z, float size, float rotate);
	void Reset();
public:
	AssignmentScene2();
	~AssignmentScene2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Update(double dt, Mouse mouse);
	virtual void Render();
	virtual void Exit();
};

#endif