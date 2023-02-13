#include <st_gameobj.h>

int ST::GameObj::getID() const{
	return ID_;
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
