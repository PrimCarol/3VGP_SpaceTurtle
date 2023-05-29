#ifndef _SPACE_TURTLE_COLLIDER_H_
#define _SPACE_TURTLE_COLLIDER_H_ 1

#include <transform.hpp>

namespace ST {

	class ColliderComponent {
	public:
		/**
		* @brief Constructor
		*/
		ColliderComponent();

		/**
		* @brief Get the min point of the collider
		*/
		glm::vec3 getMinPoint() const;
		/**
		* @brief Get the max point of the collider
		*/
		glm::vec3 getMaxPoint() const;

		/**
		* @brief Set the min point of the collider
		*/
		void setMinPoint(const glm::vec3 xyz);
		/**
		* @brief Set the max point of the collider
		*/
		void setMaxPoint(const glm::vec3 xyz);
		
		//void draw() const;

		bool active_;

		/**
		* @brief Destructor
		*/
		~ColliderComponent();
	
	private:
		/*glm::vec3 center_;
		glm::vec3 size_;*/
		glm::vec3 minPoint_;
		glm::vec3 maxPoint_;
	};
}

#endif