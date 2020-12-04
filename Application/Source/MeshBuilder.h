#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"

class MeshBuilder {
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);

	static Mesh* GenerateQuad(const std::string &meshName, Color color, float lengthX, float lengthY);

	static Mesh* GenerateCube(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ);

	static Mesh* GenerateCircle(const std::string& meshName, Color color, unsigned numSlice, float radius);

	static Mesh* GenerateSphere(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float radius);

	static Mesh* GenerateRing(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float innerRadius, float outerRadius);

	static Mesh* GenerateCylinder(const std::string& meshName, Color color, unsigned numSlice, float radius, float height);

	static Mesh* GenerateCone(const std::string& meshName, Color color, unsigned numSlice, float radius, float height);
};

#endif