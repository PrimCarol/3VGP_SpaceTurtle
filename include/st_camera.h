#ifndef _SPACE_TURTLE_CAMERA_H_
#define _SPACE_TURTLE_CAMERA_H_ 1

#include <components/st_transform.h>

#include <st_window.h>

namespace ST {

	enum CameraType {
		kCam_Perpective,
		kCam_Orthographic,
	};

	class Camera{
	public:
		Camera();

		void setPerspective(float fov, float ratio, float nearPlane, float farPlane);
		void setOrthographic(float h, float v, float nearPlane, float farPlane);

		void setTarget(glm::vec3 target);

		void fpsMovement(ST::Window& w, float MoveSpeed = 30.0f, float RotateSpeed = 0.5f);

		void update();

		~Camera();
		//Camera(const Camera& o);

		ST::TransformComponent transform_;

		glm::mat4 view;
		glm::mat4 projection;

	private:
		CameraType type;
		
		glm::vec3 target_;

		// Perspective
		float fov_;
		float ratio_;

		//Orthographic
		float horizontal_;
		float vertical_;

		float nearPlane_;
		float farPlane_;
	};
}

#endif