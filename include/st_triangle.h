#ifndef _SPACE_TURTLE_TRIANGLE_H_
#define _SPACE_TURTLE_TRIANGLE_H_ 1

#include <glad.h>
#include <matrix_4.h>

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

		void Move(Vector3 newPos);
		void Scale(Vector3 newScale);
		void Rotate(Vector3 newRot);
		void Draw();


		~Triangle();
	private:
		GLuint mesh;
		GLuint program;
		Matrix4x4 m_transform;

		Triangle(const Triangle& o);
	};
}

#endif