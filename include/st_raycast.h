#ifndef _SPACE_TURTLE_RAYCAST_H_
#define _SPACE_TURTLE_RAYCAST_H_ 1

#include <transform.hpp>

#include <st_gameobj_manager.h>
#include <st_window.h>

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

/*		void ScreenPosToWorldRay(ST::Window w, ST::GameObj_Manager gm, glm::vec3& out_direction) {

			// The ray Start and End positions, in Normalized Device Coordinates (Have you read Tutorial 4 ?)
			glm::vec4 lRayStart_NDC(
				((float)mouseX / (float)screenWidth - 0.5f) * 2.0f, // [0,1024] -> [-1,1]
				((float)mouseY / (float)screenHeight - 0.5f) * 2.0f, // [0, 768] -> [-1,1]
				-1.0, // The near plane maps to Z=-1 in Normalized Device Coordinates
				1.0f
			);
			glm::vec4 lRayEnd_NDC(
				((float)mouseX / (float)screenWidth - 0.5f) * 2.0f,
				((float)mouseY / (float)screenHeight - 0.5f) * 2.0f,
				0.0,
				1.0f
			);


			// The Projection matrix goes from Camera Space to NDC.
			// So inverse(ProjectionMatrix) goes from NDC to Camera Space.
			glm::mat4 InverseProjectionMatrix = glm::inverse(ProjectionMatrix);

			// The View Matrix goes from World Space to Camera Space.
			// So inverse(ViewMatrix) goes from Camera Space to World Space.
			glm::mat4 InverseViewMatrix = glm::inverse(ViewMatrix);

			glm::vec4 lRayStart_camera = InverseProjectionMatrix * lRayStart_NDC;    lRayStart_camera /= lRayStart_camera.w;
			glm::vec4 lRayStart_world = InverseViewMatrix * lRayStart_camera; lRayStart_world /= lRayStart_world.w;
			glm::vec4 lRayEnd_camera = InverseProjectionMatrix * lRayEnd_NDC;      lRayEnd_camera /= lRayEnd_camera.w;
			glm::vec4 lRayEnd_world = InverseViewMatrix * lRayEnd_camera;   lRayEnd_world /= lRayEnd_world.w;


			// Faster way (just one inverse)
			//glm::mat4 M = glm::inverse(ProjectionMatrix * ViewMatrix);
			//glm::vec4 lRayStart_world = M * lRayStart_NDC; lRayStart_world/=lRayStart_world.w;
			//glm::vec4 lRayEnd_world   = M * lRayEnd_NDC  ; lRayEnd_world  /=lRayEnd_world.w;


			glm::vec3 lRayDir_world(lRayEnd_world - lRayStart_world);
			lRayDir_world = glm::normalize(lRayDir_world);


			out_origin = glm::vec3(lRayStart_world);
			out_direction = glm::normalize(lRayDir_world);
		}
*/
		~Raycast();
	private:
		//Raycast(const Raycast& o);
	};
}

#endif