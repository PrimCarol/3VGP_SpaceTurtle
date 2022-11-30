#ifndef _SPACE_TURTLE_RAYCAST_H_
#define _SPACE_TURTLE_RAYCAST_H_ 1

#include <transform.hpp>

namespace ST {
	
	class Raycast {
	public:
		Raycast();

		bool TraceRay(
			glm::vec3 ray_origin,
			glm::vec3 ray_direction,
			glm::vec3 aabb_min,
			glm::vec3 aabb_max,
			glm::mat4 ModelMatrix,
			float& intersection_distance
		);

		void drawRay(glm::vec3 start, glm::vec3 end);

		~Raycast();
	private:
		//Raycast(const Raycast& o);
	};
}

#endif