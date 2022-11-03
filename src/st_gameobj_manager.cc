#include <st_gameobj_manager.h>


//template<typename ...Component>
//inline ST::GameObj& ST::GameObj_Manager::createGameObj(Component ...comp){
//	static_assert(true && ... && std::is_base_of<Component, Component>::value);
//	Entity e{ std::fordware<Patata>(patata)... };
//	return e;
//}

#define MAX_TRANSFORM_COMPONENTS 5
#define MAX_MESH_COMPONENTS 5
#define MAX_MATERIAL_COMPONENTS 5

ST::GameObj_Manager::GameObj_Manager(){

	printf("***** GameObj Manager Created *****\n");

	// ******************** Duda *********************
	// Mejor manera de pre reservar la memoria para los componentes??

	//transformComponentList_.reserve(10);
	//meshComponentList_.reserve(10);
	//materialComponentList_.reserve(10);

	for (size_t i = 0; i < MAX_TRANSFORM_COMPONENTS; i++){
		transformComponentList_.push_back(&ST::TransformComponent());
	}
	for (size_t i = 0; i < MAX_MESH_COMPONENTS; i++) {
		meshComponentList_.push_back(&ST::MeshComponent());
	}
	for (size_t i = 0; i < MAX_MATERIAL_COMPONENTS; i++) {
		materialComponentList_.push_back(&ST::MaterialComponent());
	}
	// ******************** Duda *********************

	TransCompIndex_ = 0;
	MeshCompIndex_ = 0;
	MatCompIndex_ = 0;
}

ST::ComponentId ST::GameObj_Manager::createTransformComponent(){
	ST::TransformComponentId result;
	result.value = TransCompIndex_++;
	result.type = ST::kComp_Trans;
	
	if (result.value >= MAX_TRANSFORM_COMPONENTS) {
		result.value = -1;
		result.type = kComp_None;
	}

	return result;
}

ST::ComponentId ST::GameObj_Manager::createMeshComponent(){
	ST::MeshComponentId result;
	result.value = MeshCompIndex_++;
	result.type = ST::kComp_Mesh;

	if (result.value >= MAX_MESH_COMPONENTS) {
		result.value = -1;
		result.type = kComp_None;
	}

	return result;
}

ST::ComponentId ST::GameObj_Manager::createMaterialComponent() {
	ST::MaterialComponentId result;
	result.value = MatCompIndex_++;
	result.type = ST::kComp_Material;

	if (result.value >= MAX_MATERIAL_COMPONENTS) {
		result.value = -1;
		result.type = kComp_None;
	}

	return result;
}

ST::GameObj* ST::GameObj_Manager::createGameObj(std::vector<ComponentId> c){

	// do something ??
	ST::GameObj* go = new ST::GameObj();
	if (go) {
		printf("***** Obj Created *****\n");
		go->components = c;
	}

	return go;
}

ST::GameObj_Manager::GameObj_Manager(const GameObj_Manager& o){}

//ST::TransformComponent* ST::GameObj_Manager::getTransformComponent(size_t id){
//	if (id == -1) { return NULL; }
//	if (id > transformComponentList_.size()) { return NULL; }
//	return transformComponentList_.at(id);
//}

//ST::MeshComponent* ST::GameObj_Manager::getMeshComponent(size_t id){
//	if (id == -1) { return NULL; }
//  if (id > meshComponentList_.size()) { return NULL; }
//	return meshComponentList_.at(id);
//}

//ST::MaterialComponent* ST::GameObj_Manager::getMaterialComponent(size_t id){
//	if (id == -1) { return NULL; }
//  if (id > materialComponentList_.size()) { return NULL; }
//	return materialComponentList_.at(id);
//}

ST::GameObj_Manager::~GameObj_Manager(){}
