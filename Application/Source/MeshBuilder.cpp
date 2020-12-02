#include "MeshBuilder.h"
#include <GL\glew.h>
#include <vector>
#include "Vector3.h"
#include "MyMath.h"

Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ) {
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	v.pos.Set(lengthX, 0.f, 0.f); v.color.Set(1.f, 0, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(-(lengthX), 0.f, 0.f); v.color.Set(1.f, 0, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(0.f, lengthY, 0.f); v.color.Set(0, 1.f, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(0.f, -(lengthY), 0.f); v.color.Set(0, 1.f, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(0.f, 0.f, lengthZ); v.color.Set(0, 0, 1.f); vertex_buffer_data.push_back(v);
	v.pos.Set(0.f, 0.f, -(lengthZ)); v.color.Set(0, 0, 1.f); vertex_buffer_data.push_back(v);
	for (unsigned i = 0; i < vertex_buffer_data.size(); i++) {
		index_buffer_data.push_back(i);
	}
	Mesh* mesh = new Mesh(meshName);
	mesh->indexSize = index_buffer_data.size();
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_LINES;
	return mesh;
}

Mesh* MeshBuilder::GenerateAxes(const std::string& meshName) {
	return GenerateAxes(meshName, 100, 100, 100);
}

Mesh* MeshBuilder::GenerateAxes(const std::string& meshName, float length) {
	return GenerateAxes(meshName, length, length, length);
}

Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color, float lengthX, float lengthY) {
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	v.color = color;
	v.pos.Set(0.5f * lengthX, 0.5f * lengthY, 0.f);	v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * lengthX, 0.5f * lengthY, 0.f); v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * lengthX, -0.5f * lengthY, 0.f); v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * lengthX, -0.5f * lengthY, 0.f); v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateQuad(const std::string& meshName, float length) {
	Vertex v;
	return GenerateQuad(meshName, v.color, length, length);
}

Mesh* MeshBuilder::GenerateQuad(const std::string& meshName, Color color, float length) {
	return GenerateQuad(meshName, color, length, length);
}

Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ) {
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	v.color = color;
	v.pos.Set(-0.5f * lengthX, -0.5f * lengthY, -0.5f * lengthZ); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * lengthX, -0.5f * lengthY, 0.5f * lengthZ); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * lengthX, 0.5f * lengthY, 0.5f * lengthZ);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * lengthX, 0.5f * lengthY, -0.5f * lengthZ);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * lengthX, -0.5f * lengthY, -0.5f * lengthZ); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * lengthX, 0.5f * lengthY, -0.5f * lengthZ); vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * lengthX, -0.5f * lengthY, 0.5f * lengthZ);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * lengthX, -0.5f * lengthY, -0.5f * lengthZ); vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * lengthX, -0.5f * lengthY, -0.5f * lengthZ); vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * lengthX, 0.5f * lengthY, -0.5f * lengthZ);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * lengthX, -0.5f * lengthY, -0.5f * lengthZ); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * lengthX, -0.5f * lengthY, -0.5f * lengthZ); vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * lengthX, -0.5f * lengthY, -0.5f * lengthZ); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * lengthX, 0.5f * lengthY, 0.5f * lengthZ);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * lengthX, 0.5f * lengthY, -0.5f * lengthZ); vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * lengthX, -0.5f * lengthY, 0.5f * lengthZ);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * lengthX, -0.5f * lengthY, 0.5f * lengthZ); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * lengthX, -0.5f * lengthY, -0.5f * lengthZ); vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * lengthX, 0.5f * lengthY, 0.5f * lengthZ);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * lengthX, -0.5f * lengthY, 0.5f * lengthZ);  vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * lengthX, -0.5f * lengthY, 0.5f * lengthZ);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * lengthX, 0.5f * lengthY, 0.5f * lengthZ); vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * lengthX, -0.5f * lengthY, -0.5f * lengthZ); vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * lengthX, 0.5f * lengthY, -0.5f * lengthZ); vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * lengthX, -0.5f * lengthY, -0.5f * lengthZ); vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * lengthX, 0.5f * lengthY, 0.5f * lengthZ); vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * lengthX, -0.5f * lengthY, 0.5f * lengthZ);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * lengthX, 0.5f * lengthY, 0.5f * lengthZ); vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * lengthX, 0.5f * lengthY, -0.5f * lengthZ);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * lengthX, 0.5f * lengthY, -0.5f * lengthZ); vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * lengthX, 0.5f * lengthY, 0.5f * lengthZ); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * lengthX, 0.5f * lengthY, -0.5f * lengthZ); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * lengthX, 0.5f * lengthY, 0.5f * lengthZ);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * lengthX, 0.5f * lengthY, 0.5f * lengthZ); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * lengthX, 0.5f * lengthY, 0.5f * lengthZ);  vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * lengthX, -0.5f * lengthY, 0.5f * lengthZ); vertex_buffer_data.push_back(v);

	for (unsigned i = 0; i < 36; ++i) {
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateCube(const std::string &meshName, float size) {
	Vertex v;
	return GenerateCube(meshName, v.color, size, size, size);
}

Mesh* MeshBuilder::GenerateCube(const std::string& meshName, Color color, float size) {
	return GenerateCube(meshName, color, size, size, size);
}

Mesh* MeshBuilder::GenerateCube(const std::string& meshName, float lengthX, float lengthY, float lengthZ) {
	Vertex v;
	return GenerateCube(meshName, v.color, lengthX, lengthY, lengthZ);
}

float sphereX(double& phi, double& theta) {
	return (cos(phi) * cos(theta));
}

float sphereY(double& phi, double& theta) {
	return (sin(phi));
}

float sphereZ(double& phi, double& theta) {
	return (cos(phi) * sin(theta));
}

Mesh* MeshBuilder::GenerateSphere(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float radius) {
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	v.color = color;
	unsigned index = 0;
	double pi = Math::PI;
	double degreePerStack = pi / numStack;
	double degreePerSlice = (2 * pi) / numSlice;
	for (unsigned stack = 0; stack < numStack + 1; ++stack) {
		double phi = -(pi / 2) + stack * degreePerStack;
		for (unsigned slice = 0; slice < numSlice + 1; ++slice) {
			double theta = slice * degreePerSlice;
			v.pos.Set(radius * sphereX(phi, theta), radius * sphereY(phi, theta), radius * sphereZ(phi, theta));
			v.normal.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi, theta));
			v.normal.Normalized();
			vertex_buffer_data.push_back(v);
			index_buffer_data.push_back((numSlice + 1) * stack + slice + 0);
			index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0);
		}
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateRing(const std::string& meshName, float radius) {
	Vertex v;
	return GenerateRing(meshName, v.color, 30, 30, radius-5, radius);
}

Mesh* MeshBuilder::GenerateRing(const std::string& meshName, Color color, float radius) {
	return GenerateRing(meshName, color, 30, 30, radius-5, radius);
}

Mesh* MeshBuilder::GenerateRing(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float innerRadius, float outerRadius) {
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float degreePerStack = Math::TWO_PI / numStack;
	float degreePerSlice = Math::TWO_PI / numSlice;
	float x1, z1;
	float x2, y2, z2;
	for (unsigned stack = 0; stack < numStack + 1; ++stack) {
		for (unsigned slice = 0; slice < numSlice + 1; ++slice) {
			z1 = outerRadius * cos(stack * degreePerStack);
			x1 = outerRadius * sin(stack * degreePerStack);
			z2 = (outerRadius + innerRadius * cos(slice * degreePerSlice)) * cos(stack * degreePerStack);
			y2 = innerRadius * sin(slice * degreePerSlice);
			x2 = (outerRadius + innerRadius * cos(slice * degreePerSlice)) * sin(stack * degreePerStack);
			v.pos.Set(x2, y2, z2); v.color.Set(color); vertex_buffer_data.push_back(v);
			v.pos.Set(x2-x1, y2, z2-z1); v.color.Set(color); vertex_buffer_data.push_back(v);
		}
	}
	for (unsigned stack = 0; stack < numStack; ++stack) {
		for (unsigned slice = 0; slice < numSlice + 1; ++slice) {
			index_buffer_data.push_back((numSlice + 1) * stack + slice + 0);
			index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0);
		}
	}

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateSphere(const std::string& meshName, float radius) {
	Vertex v;
	return GenerateSphere(meshName, v.color, 36, 36, radius);
}

Mesh* MeshBuilder::GenerateSphere(const std::string& meshName, Color color, float radius) {
	return GenerateSphere(meshName, color, 36, 36, radius);
}

Mesh* MeshBuilder::GenerateCircle(const std::string& meshName, Color color, unsigned numSlice, float radius = 1.f) {
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float degree = Math::TWO_PI / numSlice;

	v.pos.Set(0, 0, 0);  vertex_buffer_data.push_back(v);
	for (int i = 0; i < numSlice+1; ++i) {
		float theta = i*degree;
		v.pos.Set(radius*cos(theta), 0, radius*sin(theta)); 
		v.color.Set(color); 
		vertex_buffer_data.push_back(v);
		index_buffer_data.push_back(i + 1);
		index_buffer_data.push_back(0);
	}

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateCircle(const std::string& meshName, Color color, unsigned numSlice) {
	return GenerateCircle(meshName, color, numSlice, 1);
}

Mesh* MeshBuilder::GenerateCircle(const std::string& meshName, float radius) {
	Vertex v;
	return GenerateCircle(meshName, v.color, 20, radius);
}