#ifndef _SPACE_TURTLE_HIERARCHY_H_
#define _SPACE_TURTLE_HIERARCHY_H_ 1

#include <components/st_components.h>

namespace ST {

	class GameObj;

	class HierarchyComponent : public Components {
	public:
		HierarchyComponent();
		/* We pass the object that we want to be its parent */
		void setParent(const ST::GameObj& g);
		/* Return the ID of his parent. Return -1 if don't have. */
		const int getParentID() const;

		~HierarchyComponent();
	private:
		int parentID;
	};
}

#endif