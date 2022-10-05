#ifndef _SPACE_TURTLE_TRIANGLE_H_
#define _SPACE_TURTLE_TRIANGLE_H_ 1

#include <glad.h>
//#include <matrix_4.h>
#include <glm.hpp>
#include <transform.hpp>

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
		Triangle(glm::vec3 pos, glm::vec3 scale);

		void Move(glm::vec3 newPos);
		void Scale(glm::vec3 newScale);
		void RotateX(float r);
		void RotateY(float r);
		void RotateZ(float r);
		
		glm::vec3 getPosition();

		void Draw();

		~Triangle();
	private:
		void init();
		GLuint mesh;
		GLuint program;

		glm::mat4 m_transform;

		Triangle(const Triangle& o);
	};
}

#endif