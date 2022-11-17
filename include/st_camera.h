#ifndef _SPACE_TURTLE_CAMERA_H_
#define _SPACE_TURTLE_CAMERA_H_ 1

#include <components/st_transform.h>

namespace ST {

	class Camera{
	public:
		Camera(int width, int height, glm::vec3 pos);

		void updateMatrix(float fov, float nearPlane, float farPlane);

		~Camera();
		//Camera(const Camera& o);

		ST::TransformComponent transform_;

		glm::mat4 view;
		glm::mat4 projection;

	private:
		int width_, height_;
	};
}

#endif