#ifndef _SPACE_TURTLE_HIERARCHY_H_
#define _SPACE_TURTLE_HIERARCHY_H_ 1

#include <components/st_components.h>


namespace ST {

	class GameObj;

	class HierarchyComponent : public Components {
	public:
		HierarchyComponent();

		void setParent(const ST::GameObj& g);
		const int getParentID() const;

		~HierarchyComponent();
	private:
		int parentID;
	};
}

#endif