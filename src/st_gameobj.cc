#include <st_gameobj.h>
#include <st_gameobj_manager.h>

ST::GameObj::GameObj(){

}

//void ST::GameObj::addComponent(const ST::Components* c){
//	components.push_back(*c);
//}
//
//int ST::GameObj::numComponents() const{
//	return components.size();
//}

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
