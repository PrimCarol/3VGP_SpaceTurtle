#ifndef _SPACE_TURTLE_TRANSFORM_H_
#define _SPACE_TURTLE_TRANSFORM_H_ 1

#include <components/st_components.h>
#include <transform.hpp>

namespace ST {

	class TransformComponent : public Components {
	public:
		TransformComponent();

		//----------------- Transforms ------------------
		/* Moves based on your current position */
		void Move(const glm::vec3 newPos);
		void RotateX(const float r);
		void RotateY(const float r);
		void RotateZ(const float r);

		/* Set a forced position */
		void setPosition(const glm::vec3 pos);
		/* Set a forced scale */
		void setScale(const glm::vec3 newScale);

		/* Getters */
		const glm::vec3 getPosition();
		const glm::vec3 getScale();
		const glm::vec3 getRotation();

		const glm::vec3 getForward();
		const glm::vec3 getUp();
		const glm::vec3 getRight();

		~TransformComponent();

		glm::mat4 m_transform_;

		//void setVelocity(const glm::vec3 vel); // esto deberia de ser en un componente de fisica.
		//const glm::vec3 getVelocity(); // esto deberia de ser en un componente de fisica.
	private:
		//glm::vec3 movementVelocity; // esto deberia de ser en un componente de fisica.

		// ---- Directional Vectors ----
		void updateDirectionalVectors();
		glm::vec3 vectorForward_;
		glm::vec3 vectorUp_;
		glm::vec3 vectorRight_;
		//TransformComponent(const TransformComponent& o);
	};
}

#endif