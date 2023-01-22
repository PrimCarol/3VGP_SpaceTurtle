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
	};
}

#endif