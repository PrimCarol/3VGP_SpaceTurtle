#ifndef _SPACE_TURTLE_CAMERA_H_
#define _SPACE_TURTLE_CAMERA_H_ 1

#include <components/st_transform.h>

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

		void update();

		~Camera();
		//Camera(const Camera& o);

		ST::TransformComponent transform_;

		glm::mat4 view;
		glm::mat4 projection;

	private:
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