#ifndef _SPACE_TURTLE_TRIANGLE_H_
#define _SPACE_TURTLE_TRIANGLE_H_ 1

#include <glad.h>

namespace ST {

	struct VertexInfo {
		float x, y, z; // Position
		//float nx, ny, nz; // Normals
		float r, g, b; // Color
		//float u, v; // UVs
	};

	class Triangle{
	public:
		Triangle();

		
		void Draw();


		~Triangle();
	private:
		GLuint mesh;
		GLuint program;
		Triangle(const Triangle& o);
	};
}

#endif