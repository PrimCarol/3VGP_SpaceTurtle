#ifndef _SPACE_TURTLE_MESH_H_
#define _SPACE_TURTLE_MESH_H_ 1

#include <glad.h>

namespace ST {

	struct VertexInfo {
		float x, y, z; // Position
		//float nx, ny, nz; // Normals
		float r, g, b; // Color
		//float u, v; // UVs
	};

	class Mesh{
	public:
		Mesh();


		~Mesh();
	private:
		GLuint mesh;
		unsigned short* indices;
		Mesh(const Mesh& o);
	};
}

#endif