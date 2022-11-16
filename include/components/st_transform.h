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
		void Move(const glm::vec3 newPos);
		void RotateX(const float r);
		void RotateY(const float r);
		void RotateZ(const float r);

		/*Set a forced position*/
		void setPosition(const glm::vec3 pos);
		/*Set a forced scale*/
		void setScale(const glm::vec3 newScale);

		void setVelocity(const glm::vec3 vel);
		const glm::vec3 getVelocity();

		const glm::vec3 getPosition();
		const glm::vec3 getScale();
		const glm::vec3 getRotation();

		~TransformComponent();

		glm::mat4 m_transform_;
	private:
		glm::vec3 movementVelocity;
		//TransformComponent(const TransformComponent& o);
	};
}

#endif