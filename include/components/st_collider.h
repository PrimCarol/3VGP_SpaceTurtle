#ifndef _SPACE_TURTLE_COLLIDER_H_
#define _SPACE_TURTLE_COLLIDER_H_ 1

#include <transform.hpp>

namespace ST {

	class ColliderComponent {
	public:
		ColliderComponent();

		glm::vec3 getMinPoint() const;
		glm::vec3 getMaxPoint() const;

		void setMinPoint(const glm::vec3 xyz);
		void setMaxPoint(const glm::vec3 xyz);
		
		void draw() const;

		bool active_;

		~ColliderComponent();
		//ColliderComponent(const ColliderComponent& o);
	
	private:
		/*glm::vec3 center_;
		glm::vec3 size_;*/
		glm::vec3 minPoint_;
		glm::vec3 maxPoint_;
	};
}

#endif