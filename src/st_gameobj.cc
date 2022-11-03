#include <st_gameobj.h>

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
		case ST::kComp_Mesh:
			printf("- Mesh\n");
			break;
		case ST::kComp_Material:
			printf("- Material\n");
			break;
		}
	}
	printf("\n");
}

ST::GameObj::~GameObj(){

}
