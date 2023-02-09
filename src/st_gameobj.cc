#include <st_gameobj.h>

//#include <components/st_hierarchy.h>
//#include <components/st_transform.h>
//#include <components/st_render.h>

//ST::GameObj::GameObj(size_t id,
//	GameObj_Manager& em) {
//
//}

int ST::GameObj::getID() const{
	return ID_;
}

//void ST::GameObj::setID(int id){
//	ID_ = id;
//}

template<typename C> C* ST::GameObj::getComponent() {
	return  id_ == null_id ? nullptr : gm_.getComponent<C>(*this);
}

// Iterator interface
bool ST::GameObj::operator!=(const ST::GameObj& other) const {
	return other.ID_ != ID_;
}

//ST::GameObj& ST::GameObj::operator++() {
//	if (ID_ >= gm_.size() - 1) ID_ = null_id;
//	else ++ID_;
//	return *this;
//}

ST::GameObj& ST::GameObj::operator*() {
	return *this;
}

//const char* ST::GameObj::getName(){
//	return name_;
//}
//
//void ST::GameObj::setName(const char* name){
//	name_ = name != nullptr ? name : "GameObj";
//}

/*
void ST::GameObj::addChild(GameObj* c){
	if (c) {
		c->parent = this;
		childs.push_back(c);
	}
}
void ST::GameObj::removeChild(const unsigned int index){
	if (index < childs.size()) {
		childs.erase(childs.begin() + index);
	}
}
ST::GameObj* ST::GameObj::getChild(const unsigned int index){
	if (index >= childs.size()) {
		return nullptr;
	}
	return childs[index];
}
ST::GameObj* ST::GameObj::getParent(){
	return parent;
}
*/

//ST::Components* ST::GameObj::getComponent(ST::CompType t){
//	for (int i = 0; i < components.size(); i++) {
//		if (components[i].type == t) {
//			//Have this component.
//			switch (t) {
//			case ST::kComp_Trans:
//				return &gm_->transformComponentList_[components[i].value];
//				break;
//			case ST::kComp_Render:
//				return &gm_->renderComponentList_[components[i].value];
//				break;
//			case ST::kComp_Hierarchy:
//				return &gm_->hierarchyComponentList_[components[i].value];
//				break;
//			//case ST::kComp_Collider:
//			//	return &gm_->colliderComponentList_[components[i].value];
//			//	break;
//			}
//		}
//	}
//	return nullptr;
//}

//ST::HierarchyComponent* ST::GameObj::getComponentHierarchy() {
//	for (int i = 0; i < components.size(); i++) {
//		if (components[i].type == ST::kComp_Hierarchy) {
//			return &gm_->hierarchyComponentList_[components[i].value].value();
//		}
//	}
//	return nullptr;
//}
//
//ST::TransformComponent* ST::GameObj::getComponentTransform(){
//	for (int i = 0; i < components.size(); i++) {
//		if (components[i].type == ST::kComp_Trans) {
//			return &gm_->transformComponentList_[components[i].value].value();
//		}
//	}
//	return nullptr;
//}
//
//ST::RenderComponent* ST::GameObj::getComponentRender() {
//	for (int i = 0; i < components.size(); i++) {
//		if (components[i].type == ST::kComp_Render) {
//			return &gm_->renderComponentList_[components[i].value].value();
//		}
//	}
//	return nullptr;
//}

//template<class T>
//T* ST::GameObj::getComponent(){
//	std::vector<std::optional<T>>* vector = gm_->GetComponentVector<T>();
//	std::optional<T>* component = &vector->at(id_); // Algo parecido para añadir.
//
//	if (component->has_value()) return &(component->value());
//
//	return nullptr;
//}

//void ST::GameObj::addComponents(std::vector<ComponentId> c){
//	for (int i = 0; i < c.size(); i++){
//		components.push_back(c[i]);
//	}
//}

//template<class T>
//void ST::GameObj::addComponents(T* component){
//
//}

//void ST::GameObj::Destroy(){
//
//}

ST::GameObj::~GameObj(){
	// Eliminar el "vinculo" de los componentes del Manager
	/*for (int i = 0; i < components.size(); i++) {
		switch (components[i].type) {
		case ST::kComp_Trans:
			gm_->transformComponentList_.erase(gm_->transformComponentList_.begin() + components[i].value);
			break;
		case ST::kComp_Render:
			gm_->renderComponentList_.erase(gm_->renderComponentList_.begin() + components[i].value);
			break;
		case ST::kComp_Collider:
			gm_->colliderComponentList_.erase(gm_->colliderComponentList_.begin() + components[i].value);
			break;
		}
		
	}*/
	//printf("Destroy GameObj");
}
