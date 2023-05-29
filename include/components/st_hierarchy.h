#ifndef _SPACE_TURTLE_HIERARCHY_H_
#define _SPACE_TURTLE_HIERARCHY_H_ 1

#include <vector>

namespace ST {

	class GameObj;

	class HierarchyComponent {
	public:
		/**
		* @brief Constructor
		*/
		HierarchyComponent();
		
		/**
		* @brief We pass the object that we want to be its parent
		*/
		void setParent(const ST::GameObj& g);
		/**
		* @brief Remove the parent of this GameObj
		*/
		void removeParent(ST::GameObj& thischild);

		/**
		* @brief Add the GameObj to child
		*/
		void addChild(const ST::GameObj& g);

		/**
		* @brief Return the ID of his parent. Return -1 if don't have.
		*/
		const int getParentID() const;

		/**
		* @brief Return the ID of the child in index
		* @param index of the child
		*/
		const int getChildID(int index) const;
		/**
		* @brief Return the size of the childrens.
		*/
		const int childSize() const;

		~HierarchyComponent();
	private:
		int parentID;
		std::vector<int> childsID;
	};
}

#endif