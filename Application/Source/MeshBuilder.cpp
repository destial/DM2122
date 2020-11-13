#include "MeshBuilder.h"
#include <GL\glew.h>
#include <vector>

Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ) {
	const GLfloat vertex_buffer_data[] = {
		0
	};
	const GLfloat color_buffer_data[] = {
		0
	};
	const GLuint index_buffer_data[] = {
		0
	};
	Mesh* mesh = new Mesh(meshName);
	return mesh;
}

Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, float lengthX, float lengthY) {
	const GLfloat vertex_buffer_data[] = {
		0
	};
	const GLfloat color_buffer_data[] = {
		0
	};
	const GLuint index_buffer_data[] = {
		0
	};
	Mesh *mesh = new Mesh(meshName);

	return mesh;
}

Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color &color, float lengthX, float lengthY, float lengthZ) {
	std::vector<Vertex> vertex_data;
	std::vector<unsigned> index_data;
	Vertex vertex;
	int index = 0;
	vertex.pos.Set(0.5, 0.5, 0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(-0.5, -0.5, 0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(-0.5, 0.5, 0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(0.5, 0.5, 0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(-0.5, -0.5, 0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(0.5, -0.5, 0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(0.5, -0.5, -0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(0.5, 0.5, -0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(0.5, 0.5, 0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(0.5, -0.5, 0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(0.5, 0.5, -0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(0.5, -0.5, -0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(0.5, -0.5, -0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(-0.5, 0.5, -0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(0.5, 0.5, -0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(0.5, -0.5, -0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(-0.5, 0.5, -0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(-0.5, -0.5, -0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(-0.5, -0.5, -0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(-0.5, 0.5, 0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(-0.5, 0.5, -0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(-0.5, -0.5, -0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(-0.5, 0.5, 0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(-0.5, -0.5, 0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(-0.5, 0.5, -0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(-0.5, -0.5, -0.5); vertex.color.Set(color); vertex_data.push_back(vertex);
	vertex.pos.Set(0.5, -0.5, -0.5); vertex.color.Set(color); vertex_data.push_back(vertex);

	for (int i = 0; i < 36; i++) {
		index_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);
	mesh->indexSize = index_data.size();
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(Vertex), &vertex_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_data.size() * sizeof(GLuint), &index_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateCube(const std::string &meshName, float size) {
	Vertex v;
	return GenerateCube(meshName, v.color, size, size, size);
}

Mesh* MeshBuilder::GenerateCube(const std::string& meshName, Color &color, float size) {
	return GenerateCube(meshName, color, size, size, size);
}

Mesh* MeshBuilder::GenerateCube(const std::string& meshName, float lengthX, float lengthY, float lengthZ) {
	Vertex v;
	return GenerateCube(meshName, v.color, lengthX, lengthY, lengthZ);
}