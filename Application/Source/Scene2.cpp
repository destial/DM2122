#include "Scene2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

Scene2::Scene2() {
}

Scene2::~Scene2() {
}

void Scene2::Init() {
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	m_programID = LoadShaders(
		"Shader//TransformVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader"
	);
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	glUseProgram(m_programID);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

	static const GLfloat vertex_buffer_data[] = {
		-0.5, 0.2, 0,
		-0.5, -0.2, 0,
		-0.2, -0.8, 0,
		0.2, -0.8, 0,
		0.5, -0.2, 0,
		0.5, 0.2, 0,
		0.2, 0.8, 0,
		-0.2, 0.8, 0,
		-0.5, 0.2, 0
	};

	static const GLfloat color_buffer_data[] = {
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	};
	rotateAngle = 0;
	translateX = 0;
	translateY = 0;
	scaleAll = 1;
	reverse = false;
	up = false;
	scale = false;

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	glEnable(GL_DEPTH_TEST);
}

void Scene2::Update(double dt) {
	if (rotateAngle > 180 || rotateAngle < -180) {
		if (reverse) reverse = false;
		else reverse = true;
	}
	if (!reverse)
		rotateAngle += (float)(90 * dt);
	else if (reverse)
		rotateAngle -= (float)(90 * dt);
	if (translateY > 40 || translateY < -40) {
		if (up) up = false;
		else up = true;
	}
	if (!up) 
		translateY += (float)(-50 * dt);
	else if (up) 
		translateY += (float)(50 * dt);

	if (scaleAll > 50 || scaleAll < 1) {
		if (scale) scale = false;
		else scale = true;
	}
	if (!scale)
		scaleAll += (float)(30 * dt);
	else
		scaleAll += (float)(-30 * dt);
	if (translateX > 50 || translateX < -50) {
		if (side) side = false;
		else side = true;
	}
	if (!side)
		translateX += (float)(35 * dt);
	else
		translateX -= (float)(35 * dt);
}

void Scene2::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	Mtx44 translate, rotate, scale;
	Mtx44 model, view, projection;
	Mtx44 MVP;

	translate.SetToIdentity(); rotate.SetToIdentity(); scale.SetToIdentity();
	model.SetToIdentity(); view.SetToIdentity();

	projection.SetToOrtho(-40, +40, -30, +30, -10, +10);

	scale.SetToScale(scaleAll, scaleAll, scaleAll);
	rotate.SetToRotation(-rotateAngle, 0, 0, 1);
	translate.SetToTranslation(translateX+30, translateY, 0);

	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 9);

	translate.SetToIdentity(); rotate.SetToIdentity(); scale.SetToIdentity();
	model.SetToIdentity(); view.SetToIdentity();

	projection.SetToOrtho(-40, +40, -30, +30, -10, +10);

	scale.SetToScale(scaleAll, scaleAll, scaleAll);
	rotate.SetToRotation(-rotateAngle, 0, 0, 1);
	translate.SetToTranslation(translateX-30, translateY, 0);

	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 9);

	translate.SetToIdentity(); rotate.SetToIdentity(); scale.SetToIdentity();
	model.SetToIdentity(); view.SetToIdentity();

	projection.SetToOrtho(-40, +40, -30, +30, -10, +10);

	scale.SetToScale(scaleAll, scaleAll, scaleAll);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	translate.SetToTranslation(translateX, translateY, 0);

	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 9);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Scene2::Exit() {
	glDeleteProgram(m_programID);
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}
