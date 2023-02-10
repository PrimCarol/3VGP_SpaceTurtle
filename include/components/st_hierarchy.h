#ifndef _SPACE_TURTLE_HIERARCHY_H_
#define _SPACE_TURTLE_HIERARCHY_H_ 1

#include <vector>

namespace ST {

	class GameObj;

	class HierarchyComponent {
	public:
		HierarchyComponent();
		/* We pass the object that we want to be its parent */
		void setParent(const ST::GameObj& g);
		/* Return the ID of his parent. Return -1 if don't have. */
		const int getParentID() const;

		//const int getChildID(int index) const;
		//const int childSize() const;

		~HierarchyComponent();
	private:
		int parentID;
		//std::vector<int> childsID;
	};
}

#endif