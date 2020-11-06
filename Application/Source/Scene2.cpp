#include "Scene2.h"

Scene2::Scene2() {
}

Scene2::~Scene2() {
}

void Scene2::Init() {
	glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
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

	static const GLfloat triangle_vertex[] = {
		-20, -20, 0,
		0, 20, 0,
		20, -20, 0
	};

	static const GLfloat triangle_color[] = {
		0.05f, 0.4f, 0.1f,
		0.05f, 0.4f, 0.1f,
		0.05f, 0.4f, 0.1f
	};

	static const GLfloat triangle_color2[] = {
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f
	};

	static const GLfloat quad_vertex[] = {
		-20, -20, 0,
		20, 20, 0,
		20, -20, 0,
		-20, 20, 0,
		-20, -20, 0
	};

	static const GLfloat quad_color[] = {
		0.6f, 0.0f, 0.1f,
		0.6f, 0.0f, 0.1f,
		0.6f, 0.0f, 0.1f,
		0.6f, 0.0f, 0.1f,
		0.6f, 0.0f, 0.1f
	};

	static const GLfloat quad_color2[] = {
		0.6f, 0.2f, 0.1f,
		0.6f, 0.2f, 0.1f,
		0.6f, 0.2f, 0.1f,
		0.6f, 0.2f, 0.1f,
		0.6f, 0.2f, 0.1f
	};

	static const GLfloat star_vertex[] = {
		-5, 2, 0,
		5, 2, 0,
		-3, -8, 0,
		0, 8, 0,
		3, -8, 0
	};

	static const GLfloat star_color[] = {
		0.6f, 0.0f, 0.1f,
		0.6f, 0.0f, 0.1f,
		0.6f, 0.0f, 0.1f,
		0.6f, 0.0f, 0.1f,
		0.6f, 0.0f, 0.1f
	};

	rotateAngle = 0;
	translateX = 0;
	translateY = 0;
	scaleAll = 0;
	reverse = false;
	up = false;
	scaling = false;
	projection.SetToOrtho(-40, +40, -30, +30, -10, +10);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertex), triangle_vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_color), triangle_color, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertex), triangle_vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_color2), triangle_color2, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_QUAD_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertex), quad_vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_QUAD_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad_color), quad_color, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_QUAD_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertex), quad_vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_QUAD_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad_color2), quad_color2, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_STAR_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(star_vertex), star_vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_STAR_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(star_color), star_color, GL_STATIC_DRAW);

	glEnable(GL_DEPTH_TEST);
}

void Scene2::Update(double dt) {
	if (reverse) {
		rotateAngle += 0.5;
	} else {
		rotateAngle -= 0.5;
	}
	if (rotateAngle >= 5)
		reverse = false;
	if (rotateAngle <= -5)
		reverse = true;
	if (scaling) {
		scaleAll += 0.005;
		translateY += 0.1;
	} else {
		scaleAll -= 0.005;
		translateY -= 0.1;
	}
	if (scaleAll > 0.1)
		scaling = false;
	if (scaleAll <= 0.05)
		scaling = true;
}

void Scene2::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	translate.SetToTranslation(25, 10, 0);
	scale.SetToScale(0.3, 0.3, 0.3);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	Draw(GEO_TRIANGLE_1, GL_TRIANGLE_FAN);

	translate.SetToTranslation(25, 5, 0);
	scale.SetToScale(0.32, 0.32, 0.32);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	Draw(GEO_TRIANGLE_1, GL_TRIANGLE_FAN);

	translate.SetToTranslation(25, 0, 0);
	scale.SetToScale(0.35, 0.35, 0.35);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	Draw(GEO_TRIANGLE_1, GL_TRIANGLE_FAN);

	translate.SetToTranslation(-25, -14 + translateY, 1);
	scale.SetToScale(0.2, scaleAll, 1);
	Draw(GEO_TRIANGLE_2, GL_TRIANGLE_FAN);

	translate.SetToTranslation(-23, -15 + translateY, 0.5);
	scale.SetToScale(0.2, scaleAll, 1);
	Draw(GEO_TRIANGLE_2, GL_TRIANGLE_FAN);

	translate.SetToTranslation(-26.5, -14.5 + translateY, 1);
	scale.SetToScale(0.2, scaleAll, 1);
	Draw(GEO_TRIANGLE_2, GL_TRIANGLE_FAN);

	translate.SetToTranslation(-25, 5, 0);
	scale.SetToScale(0.32, 1.1, 1);
	Draw(GEO_QUAD_1, GL_TRIANGLE_STRIP);

	translate.SetToTranslation(25, -7, 0);
	scale.SetToScale(0.1, 0.2, 1);
	Draw(GEO_QUAD_2, GL_TRIANGLE_STRIP);

	translate.SetToTranslation(-25, -15.3, 1);
	scale.SetToScale(0.33, 0.02, 1);
	Draw(GEO_QUAD_2, GL_TRIANGLE_STRIP);

	translate.SetToTranslation(-25, -15.3, 1);
	rotate.SetToRotation(10, 0, 0, 1);
	scale.SetToScale(0.33, 0.02, 1);
	Draw(GEO_QUAD_2, GL_TRIANGLE_STRIP);

	translate.SetToTranslation(-25, -15.3, 1);
	rotate.SetToRotation(-10, 0, 0, 1);
	scale.SetToScale(0.33, 0.02, 1);
	Draw(GEO_QUAD_2, GL_TRIANGLE_STRIP);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Scene2::Exit() {
	glDeleteProgram(m_programID);
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}

void Scene2::SetToIdentity() {
	translate.SetToIdentity(); 
	rotate.SetToIdentity(); 
	scale.SetToIdentity();
	model.SetToIdentity(); 
	view.SetToIdentity();
}

void Scene2::Draw(GEOMETRY_TYPE type, GLenum e) {
	MVP = projection * view * (translate * rotate * scale);
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[type]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[type]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
	glDrawArrays(e, 0, 9);
	SetToIdentity();
}
