#ifndef _SPACE_TURTLE_RAYCAST_H_
#define _SPACE_TURTLE_RAYCAST_H_ 1

#include <transform.hpp>

#include <st_window.h>

namespace ST {

	class CameraComponent;

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

		glm::vec3 ScreenPosToWorldRay(const ST::Window& w, const ST::CameraComponent& cam);

		~Raycast();
	private:
		//Raycast(const Raycast& o);
	};
}

#endif