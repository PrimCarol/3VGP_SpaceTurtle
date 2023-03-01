#ifndef _SPACE_TURTLE_CAMERA_H_
#define _SPACE_TURTLE_CAMERA_H_ 1

#include <transform.hpp>

namespace ST {

	class Window;

	enum CameraType {
		kCam_Perpective,
		kCam_Orthographic,
	};

	class CameraComponent {
	public:
		CameraComponent();

		void setPerspective(float fov, float ratio, float nearPlane, float farPlane);
		void setOrthographic(float h, float v, float nearPlane, float farPlane);

		ST::CameraType getCameraType() const;

		glm::mat4 view;
		glm::mat4 projection;

		void lookAt(glm::vec3 myPos, glm::vec3 target, glm::vec3 upCamVector);

		~CameraComponent();
		//CameraComponent(const CameraComponent& o);
	
	//private:
		CameraType type;

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