#include <components/st_hierarchy.h>

#include <st_gameobj.h>
#include <st_gameobj_manager.h>

ST::HierarchyComponent::HierarchyComponent(){
	parentID = -1;
}

void ST::HierarchyComponent::setParent(const ST::GameObj& g){
	parentID = g.getID();
	g.getComponent<ST::HierarchyComponent>()->addChild(g.gm_.getGameObj(*this));
}

void ST::HierarchyComponent::removeParent(ST::GameObj& thischild) {		
	if (thischild.gm_.getComponentVector<ST::HierarchyComponent>()->at(parentID).has_value()) {
		ST::HierarchyComponent& parentComp = thischild.gm_.getComponentVector<ST::HierarchyComponent>()->at(parentID).value();
		for (int i = 0; i < parentComp.childSize(); i++) {
			if (parentComp.getChildID(i) == thischild.getID()) {
				parentComp.childsID.erase(parentComp.childsID.begin() + i);
				exit;
			}
		}
	}
	parentID = -1;
}

void ST::HierarchyComponent::addChild(const ST::GameObj& g){
	childsID.push_back(g.getID());
	g.getComponent<ST::HierarchyComponent>()->parentID = g.gm_.getGameObj(*this).getID();
}

const int ST::HierarchyComponent::getParentID() const{
	return parentID;
}

const int ST::HierarchyComponent::getChildID(int index) const{
	if (index < childSize()) {
		return childsID.at(index);
	}
}

const int ST::HierarchyComponent::childSize() const{
	return childsID.size();
}

ST::HierarchyComponent::~HierarchyComponent(){
	childsID.clear();
}
