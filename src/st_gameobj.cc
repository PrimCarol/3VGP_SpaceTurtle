#include <st_gameobj.h>
#include <st_gameobj_manager.h>

ST::GameObj::GameObj(){
	gm_ = nullptr;

	//parent = nullptr;
	//childs = nullptr;
}

void ST::GameObj::checkComponents(){
	printf("<- Components ->\n");
	for (int i = 0; i < components.size(); i++) {

		switch (components[i].type) {
		case ST::kComp_Trans:
			printf("- Transform\n");
			break;
		case ST::kComp_Render:
			printf("- Render\n");
			break;
		}
	}
	printf("\n");
}

ST::Components* ST::GameObj::getComponent(ST::CompType t){
	for (int i = 0; i < components.size(); i++) {
		if (components[i].type == t) {
			//Have this component.
			switch (t) {
			case ST::kComp_Trans:
				return &gm_->transformComponentList_[components[i].value];
				break;
			case ST::kComp_Render:
				return &gm_->renderComponentList_[components[i].value];
				break;
			}
		}
	}
	return nullptr;
}

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

ST::GameObj::~GameObj(){
	// Eliminar el "vinculo" de los componentes del Manager
	for (int i = 0; i < components.size(); i++) {
		switch (components[i].type) {
		case ST::kComp_Trans:
			gm_->transformComponentList_.erase(gm_->transformComponentList_.begin() + components[i].value);
			break;
		case ST::kComp_Render:
			gm_->renderComponentList_.erase(gm_->renderComponentList_.begin() + components[i].value);
			break;
		}
		
	}
	//printf("Destroy GameObj");
}
