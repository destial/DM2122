#include "Scene4.h"
#include "Application.h"
#include <iostream>

Scene4::Scene4() {
}

Scene4::~Scene4() {
}

void Scene4::Init() {
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	m_programID = LoadShaders(
		"Shader//TransformVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader"
	);
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	glUseProgram(m_programID);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", 1, 1, 1);
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("axes");

	rotateAngle = 0;
	translateX = 0;
	translateY = 0;
	scaleAll = 1;
	reverse = false;
	up = false;
	scaling = false;
	SetToIdentity();
	view.SetToIdentity();
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	camera.Init(Vector3(4, 3, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Scene4::Update(double dt) {
	if (Application::IsKeyPressed('1')) {
		glEnable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed('2')) {
		glDisable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed('3')) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	} 
	if (Application::IsKeyPressed('4')) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (Application::IsKeyPressed('W')) {
		scaleAll+=0.1;
	}
	if (Application::IsKeyPressed('S')) {
		scaleAll -= 0.1;
	}

	rotateAngle -= 0.5;
	camera.Update(dt);
}

void Scene4::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetToIdentity();
	view.SetToLookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
	);
	scale.SetToScale(scaleAll, scaleAll, scaleAll);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	meshList[GEO_CUBE]->Render();
	meshList[GEO_AXES]->Render();

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Scene4::Exit() {
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}

void Scene4::SetToIdentity() {
	translate.SetToIdentity(); 
	rotate.SetToIdentity(); 
	scale.SetToIdentity();
	model.SetToIdentity(); 
}
