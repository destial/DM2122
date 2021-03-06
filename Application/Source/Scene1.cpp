#include "Scene1.h"
#include "GL\glew.h"

#include "shader.hpp"

Scene1::Scene1() {
}

Scene1::~Scene1() {
}

void Scene1::Init() {
	// Init VBO here
	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	m_programID = LoadShaders(
		"Shader//SimpleVertexShader.vertexshader", 
		"Shader//SimpleFragmentShader.fragmentshader"
	);
	glUseProgram(m_programID);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Generate buffers
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
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	// 2nd Triangle
	static const GLfloat vertex_buffer_data2[] = {
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

	static const GLfloat color_buffer_data2[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data2), vertex_buffer_data2, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data2), color_buffer_data2, GL_STATIC_DRAW);

	glEnable(GL_DEPTH_TEST);
}

void Scene1::Update(double dt) {
}

void Scene1::Render() {
	// Render VBO here

	// Clear color buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(0); // 1st attribute buffer: vertices
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 9);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Scene1::Exit() {
	// Cleanup VBO here
	glDeleteProgram(m_programID);
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}
