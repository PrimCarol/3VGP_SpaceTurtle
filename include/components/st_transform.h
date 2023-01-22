#ifndef _SPACE_TURTLE_TRANSFORM_H_
#define _SPACE_TURTLE_TRANSFORM_H_ 1

#include <components/st_components.h>
#include <transform.hpp>

#include <st_gameobj.h>

namespace ST {
	
	class TransformComponent : public Components {
	public:
		TransformComponent();

		//----------------- Transforms ------------------
		/* Moves based on your current position */
		void Move(const glm::vec3 newPos);
		/* Add rotation on your current rotation X axis in radiants*/
		void RotateX(const float r);
		/* Add rotation on your current rotation Y axis in radiants*/
		void RotateY(const float r);
		/* Add rotation on your current rotation Z axis in radiants*/
		void RotateZ(const float r);

		/* Set a forced position */
		void setPosition(const glm::vec3 pos);
		/* Set a forced scale */
		void setScale(const glm::vec3 newScale);
		/* Set a forced rotation X axis in radiants */
		void setRotateX(const float r);
		/* Set a forced rotation Y axis in radiants */
		void setRotateY(const float r);
		/* Set a forced rotation Z axis in radiants */
		void setRotateZ(const float r);

		/* Getters */
		const glm::vec3 getPosition() const;
		const glm::vec3 getScale() const;
		const glm::vec3 getRotation() const;

		const glm::vec3 getForward() const;
		const glm::vec3 getUp() const;
		const glm::vec3 getRight() const;

		glm::mat4 m_transform_;

		glm::mat4 m_Position_;
		glm::mat4 m_Rotation_;

		void updateDirectionalVectors();

		~TransformComponent();
	private:

		// ---- Basic Transform values ----
		glm::vec3 position_;
		glm::vec3 rotation_;
		glm::vec3 scale_;

		// ---- Directional Vectors ----
		//void updateTransformMatrix();
		glm::vec3 vectorForward_;
		glm::vec3 vectorUp_;
		glm::vec3 vectorRight_;

		//TransformComponent(const TransformComponent& o);
	};
}

#endif