#include "Mesh.h"
#include "Vertex.h"
#include "GL\glew.h"

Mesh::Mesh(const std::string &meshName): name(meshName), mode(DRAW_TRIANGLES), textureID(0) {
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &indexBuffer);
}

Mesh::~Mesh() {
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	if (textureID > 0) {
		glDeleteTextures(1, &textureID);
	}
}

void Mesh::Render() {
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	if (textureID > 0) glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color)));
	if (textureID > 0) 
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color) + sizeof(Vector3)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	switch (mode) {
	case (DRAW_TRIANGLES):
		glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
		break;
	case (DRAW_TRIANGLE_STRIP):
		glDrawElements(GL_TRIANGLE_STRIP, indexSize, GL_UNSIGNED_INT, 0);
		break;
	case (DRAW_LINES):
		glDrawElements(GL_LINES, indexSize, GL_UNSIGNED_INT, 0);
		break;
	case (DRAW_TRIANGLE_FAN):
		glDrawElements(GL_TRIANGLE_FAN, indexSize, GL_UNSIGNED_INT, 0);
		break;
	default:
		glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
		break;
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	if (textureID > 0) 
		glDisableVertexAttribArray(3);
}

void Mesh::Render(unsigned offset, unsigned count) {
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	if (textureID > 0) glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color)));
	if (textureID > 0)
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color) + sizeof(Vector3)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	switch (mode) {
	case (DRAW_TRIANGLES):
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
		break;
	case (DRAW_TRIANGLE_STRIP):
		glDrawElements(GL_TRIANGLE_STRIP, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
		break;
	case (DRAW_LINES):
		glDrawElements(GL_LINES, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
		break;
	case (DRAW_TRIANGLE_FAN):
		glDrawElements(GL_TRIANGLE_FAN, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
		break;
	default:
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
		break;
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	if (textureID > 0)
		glDisableVertexAttribArray(3);
}
