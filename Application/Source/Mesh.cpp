#include "Mesh.h"
#include "Vertex.h"
#include "GL\glew.h"

Mesh::Mesh(const std::string &meshName)
	: name(meshName)
	, mode(DRAW_TRIANGLES) {
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &indexBuffer);
}

Mesh::~Mesh() {
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
}

void Mesh::Render() {
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)sizeof(Position));

	glBindBuffer(GL_ARRAY_BUFFER, indexBuffer);

	switch (mode) {
	case (DRAW_TRIANGLES):
		glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
		break;
	case (DRAW_TRIANGLE_STRIP):
		glDrawElements(GL_TRIANGLE_STRIP, indexSize, GL_UNSIGNED_INT, 0);
		break;
	case (DRAW_LINES):
		glDrawElements(GL_LINES, indexSize, GL_UNSIGNED_INT, 0);;
		break;
	default:
		glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
		break;
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}