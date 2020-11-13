#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"

class MeshBuilder {
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName, float lengthX, float lengthY);
	static Mesh* GenerateCube(const std::string &meshName, Color &color, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateCube(const std::string &meshName, float size);
	static Mesh* GenerateCube(const std::string &meshName, Color &color, float size);
	static Mesh* GenerateCube(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
};

#endif