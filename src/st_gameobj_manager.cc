#include <st_gameobj_manager.h>

//template<typename ...Component>
//inline ST::GameObj& ST::GameObj_Manager::createGameObj(Component ...comp){
//	static_assert(true && ... && std::is_base_of<Component, Component>::value);
//	Entity e{ std::fordware<Patata>(patata)... };
//	return e;
//}

#define MAX_TRANSFORM_COMPONENTS 5
#define MAX_RENDER_COMPONENTS 5

ST::GameObj_Manager::GameObj_Manager(){

	printf("***** GameObj Manager Created *****\n");

	// ******************** Duda *********************
	// Mejor manera de pre reservar la memoria para los componentes??

	transformComponentList_.reserve(MAX_TRANSFORM_COMPONENTS);
	renderComponentList_.reserve(MAX_RENDER_COMPONENTS);

	//for (size_t i = 0; i < MAX_TRANSFORM_COMPONENTS; i++){
	//	transformComponentList_.push_back(ST::TransformComponent());
	//}
	//for (size_t i = 0; i < MAX_RENDER_COMPONENTS; i++) {
	//	renderComponentList_.push_back(ST::RenderComponent());
	//}
	
	// ******************** Duda *********************

	TransCompIndex_ = 0;
	RenderCompIndex_ = 0;
}

ST::ComponentId ST::GameObj_Manager::createTransformComponent(){
	
	if (TransCompIndex_ >= MAX_TRANSFORM_COMPONENTS) {
		return ST::TransformComponentId();
	}

	ST::TransformComponentId result;
	result.value = TransCompIndex_++;
	result.type = ST::kComp_Trans;

	transformComponentList_.push_back(ST::TransformComponent());
	return result;
}

ST::ComponentId ST::GameObj_Manager::createRenderComponent(){
	if (RenderCompIndex_ >= MAX_RENDER_COMPONENTS) {
		return ST::RenderComponentId();
	}

	ST::RenderComponentId result;
	result.value = RenderCompIndex_++;
	result.type = ST::kComp_Render;

	renderComponentList_.push_back(ST::RenderComponent());
	return result;
}

std::unique_ptr<ST::GameObj> ST::GameObj_Manager::createGameObj(std::vector<ComponentId> c){

	auto go = std::make_unique<ST::GameObj>();
	if (go) {
		printf("\n***** Obj Created *****\n");
		go->components = c;
		go->gm_ = this;
	}

	return go;
}

void ST::GameObj_Manager::UpdateTransforms(){
	for (int i = 0; i < transformComponentList_.size(); i++){
		transformComponentList_[i].Move(glm::vec3(0.0f,1.0f,0.0f));
		if (transformComponentList_[i].getPosition().y > 100.0f) {
			transformComponentList_[i].setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		}
		printf("Obj[%d] Pos-> %f - %f - %f\n", i, transformComponentList_[i].getPosition().x,
											      transformComponentList_[i].getPosition().y,
											      transformComponentList_[i].getPosition().z);
	}
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
