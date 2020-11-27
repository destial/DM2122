#ifndef MESH_H
#define MESH_H

#include <string>
#include "Material.h"

class Mesh {
public:
	enum DRAW_MODE {
		DRAW_TRIANGLES, //default mode
		DRAW_TRIANGLE_STRIP,
		DRAW_LINES,
		DRAW_TRIANGLE_FAN,
		DRAW_MODE_LAST,
	};
	Mesh(const std::string &meshName);
	~Mesh();
	void Render();

	const std::string name;
	Material material;
	DRAW_MODE mode;
	unsigned vertexBuffer;
	unsigned indexBuffer;
	unsigned indexSize;
};

#endif