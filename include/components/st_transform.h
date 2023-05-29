#ifndef _SPACE_TURTLE_TRANSFORM_H_
#define _SPACE_TURTLE_TRANSFORM_H_ 1

#include <transform.hpp>

namespace ST {
	
	class TransformComponent {
	public:
		TransformComponent();

		//----------------- Transforms ------------------
		/**
		*@brief Moves based on your current position. (Preferably use DeltaTime() from ST::Window)
		*/ 
		void Move(const glm::vec3 newPos);
		/**
		*@brief Add rotation on your current rotation X axis in degrees
		*/
		void RotateX(const float r);
		/**
		*@brief Add rotation on your current rotation Y axis in degrees
		*/
		void RotateY(const float r);
		/**
		*@brief Add rotation on your current rotation Z axis in degrees
		*/
		void RotateZ(const float r);

		/**
		*@brief Set a forced position
		*/
		void setPosition(const glm::vec3 pos);
		/**
		*@brief Set a forced position
		*/
		void setPosition(const float posX, const float posY, const float posZ);
		
		/**
		*@brief Set a forced scale
		*/
		void setScale(const glm::vec3 newScale);
		/**
		*@brief Set a forced scale
		*/
		void setScale(const float scaleX, const float scaleY, const float scaleZ);

		/**
		*@brief Set a forced rotation X axis in degrees
		*/
		void setRotateX(const float r);
		/**
		*@brief Set a forced rotation Y axis in degrees
		*/
		void setRotateY(const float r);
		/**
		*@brief Set a forced rotation Z axis in degrees
		*/
		void setRotateZ(const float r);

		/* Getters */
		/**
		*@brief Get position
		*/
		const glm::vec3 getPosition() const;
		/**
		*@brief Get scale
		*/
		const glm::vec3 getScale() const;
		/**
		*@brief Get Rotation
		*/
		const glm::vec3 getRotation() const;

		/**
		*@brief Get Forward vector
		*/
		const glm::vec3 getForward() const;
		/**
		*@brief Get Up vector
		*/
		const glm::vec3 getUp() const;
		/**
		*@brief Get Right vector
		*/
		const glm::vec3 getRight() const;

		glm::mat4 m_transform_;
		glm::mat4 m_world_transform_;

		glm::mat4 m_Position_;
		glm::mat4 m_Rotation_;

		glm::mat4 m_World_Position_;
		glm::mat4 m_World_Rotation_;

		bool dirty;

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