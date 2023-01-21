#include <components/st_hierarchy.h>

#include <st_gameobj.h>

ST::HierarchyComponent::HierarchyComponent(){
	parentID = -1;
}

void ST::HierarchyComponent::setParent(const ST::GameObj& g){
	parentID = g.getID();
}

const int ST::HierarchyComponent::getParentID() const{
	return parentID;
}

ST::HierarchyComponent::~HierarchyComponent(){
}
