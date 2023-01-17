#ifndef _SPACE_TURTLE_HIERARCHY_H_
#define _SPACE_TURTLE_HIERARCHY_H_ 1

#include <components/st_components.h>

namespace ST {

	class HierarchyComponent : public Components {
	public:
		HierarchyComponent();

		int parentID;

		~HierarchyComponent();
	};
}

#endif