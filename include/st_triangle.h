#ifndef _SPACE_TURTLE_TRIANGLE_H_
#define _SPACE_TURTLE_TRIANGLE_H_ 1

#include <glm.hpp>
#include <transform.hpp>

#include "st_program.h"
#include "st_buffer.h"

namespace ST {

	struct VertexInfo{
		float x, y, z;
		float r, g, b;
	};

	class Triangle{ // Imaginando que esto es un nodo general.
	public:
		Triangle();
		Triangle(glm::vec3 pos, glm::vec3 scale);

		void Move(glm::vec3 newPos);
		void Scale(glm::vec3 newScale);
		void RotateX(float r);
		void RotateY(float r);
		void RotateZ(float r);
		
		glm::vec3 getPosition();
		glm::vec3 getScale();
		glm::vec3 getRotation();

		void Draw();

		~Triangle();
	private:
		void init(); // Esto iria en otro sitio.
		
		GLuint mesh; // Esto seria un geometry.
		//ST::Buffer b_vertex;
		//ST::Buffer b_indices;
		ST::Program program;

		glm::mat4 m_transform;

		Triangle(const Triangle& o);
	};
}

#endif