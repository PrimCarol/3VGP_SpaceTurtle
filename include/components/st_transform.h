#ifndef _SPACE_TURTLE_TRANSFORM_H_
#define _SPACE_TURTLE_TRANSFORM_H_ 1

#include <components/st_components.h>
#include <transform.hpp>

namespace ST {

	class TransformComponent : public Components {
	public:
		TransformComponent();

		//----------------- Transforms ------------------
		/*Moves based on your current position*/
		void Move(glm::vec3 newPos);
		void RotateX(float r);
		void RotateY(float r);
		void RotateZ(float r);

		/*Set a forced position*/
		void setPosition(const glm::vec3 pos);
		/*Set a forced scale*/
		void setScale(const glm::vec3 newScale);

		glm::vec3 getPosition();
		glm::vec3 getScale();
		glm::vec3 getRotation();

		~TransformComponent();
	private:
		glm::mat4 m_transform_;
		//TransformComponent(const TransformComponent& o);
	};
}

#endif