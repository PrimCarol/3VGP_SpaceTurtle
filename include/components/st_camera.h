#ifndef _SPACE_TURTLE_CAMERA_H_
#define _SPACE_TURTLE_CAMERA_H_ 1

#include <transform.hpp>

namespace ST {

	class Window;
	class Texture;

	/**
	* @brief Camera Type
	*/
	enum CameraType {
		kCam_Perspective,
		kCam_Orthographic,
	};

	class CameraComponent {
	public:
		/**
		* @brief Constructor.
		*/
		CameraComponent();

		/**
		* @brief Set the camera to Perspective
		* @param float fov
		* @param float ratio
		* @param float nearPlane
		* @param float farPlane
		*/
		void setPerspective(float fov, float ratio, float nearPlane, float farPlane);
		/**
		* @brief Set the camera to Orthographic
		* @param float horizontal
		* @param float vertical
		* @param float nearPlane
		* @param float farPlane
		*/
		void setOrthographic(float h, float v, float nearPlane, float farPlane);

		/**
		* @brief Return the type of the camera.
		*/
		ST::CameraType getCameraType() const;

		glm::mat4 view;
		glm::mat4 projection;

		/**
		* @brief Make camera look to some point
		* @param glm::vec3 myPos the position of the start point
		* @param glm::vec3 target the position the target to look
		* @param glm::vec3 upCamVector UpVector
		*/
		void lookAt(glm::vec3 myPos, glm::vec3 target, glm::vec3 upCamVector);

		CameraType type;

		// Perspective
		float fov_;
		float ratio_;

		//Orthographic
		float horizontal_;
		float vertical_;

		float nearPlane_;
		float farPlane_;

		~CameraComponent();
	};
}

#endif