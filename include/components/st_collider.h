#ifndef _SPACE_TURTLE_COLLIDER_H_
#define _SPACE_TURTLE_COLLIDER_H_ 1

#include <components/st_components.h>
#include <transform.hpp>

namespace ST {

	class ColliderComponent : public Components {
	public:
		ColliderComponent();


		//void draw() const;


		~ColliderComponent();
		//ColliderComponent(const ColliderComponent& o);


		glm::vec3 center_;
		glm::vec3 size_;

		//glm::vec3 colliderPoint_min(-1.0f, -1.0f, -1.0f); // Collider
		//glm::vec3 colliderPoint_max(1.0f, 1.0f, 1.0f);
	};
}

#endif