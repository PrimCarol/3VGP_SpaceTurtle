#include <st_gameobj_manager.h>

#include <st_gameobj.h>

#include <components/st_transform.h>
#include <components/st_render.h>
#include <components/st_collider.h>
#include <components/st_hierarchy.h>

ST::GameObj_Manager::GameObj_Manager(){

	addComponentClass<ST::RenderComponent>();
	addComponentClass<ST::TransformComponent>();
	addComponentClass<ST::HierarchyComponent>();
	
	// ------- Create Basic Program -------
	basicProgram = std::make_unique<ST::Program>();

	ST::Shader vertex(E_VERTEX_SHADER);
	GLchar* textVertex = (GLchar*)ST::basic_vShader_text;
	vertex.loadSource(textVertex);

	ST::Shader fragment(E_FRAGMENT_SHADER);
	GLchar* textFragment = (GLchar*)ST::basic_fShader_text;
	fragment.loadSource(textFragment);

	basicProgram->attach(vertex);
	basicProgram->attach(fragment);
	basicProgram->link();
}

//template <class T>
//std::vector<std::optional<T>>* ST::GameObj_Manager::GetComponentVector() {
//	auto comp_vector = component_map_.find(typeid(T).hash_code());
//	if (comp_vector == component_map_.end()) return nullptr;
//
//	auto casted_comp_vector = static_cast<ComponentVector_Implementation<T>*>(comp_vector->second.get());
//
//	return &casted_comp_vector->vector;
//}
//
//std::unique_ptr<ST::GameObj> ST::GameObj_Manager::createGameObj() {
//
//	auto go = std::make_unique<ST::GameObj>();
//	if (go) {
//		//printf("\n***** Obj Created *****\n");
//		//go->components = c;
//
//		components_map[typeid(ST::RenderComponent).hash_code()] = std::make_unique<ComponentVector_Implementation<RenderComponent> >();
//
//		std::vector<ST::ComponentId> comps;
//		//comps.push_back(createHierarchyComponent());
//		//comps.push_back(createTransformComponent());
//		//comps.push_back(createRenderComponent());
//		//comps.push_back(createColliderComponent());
//		go->addComponents(comps);
//		go->gm_ = this;
//
//		go->setID((int)GameObjsList_.size());
//
//		//char provisionalName[20];
//		//sprintf(provisionalName, "GameObj %d", (int)GameObjsList_.size());
//		//go->setName(provisionalName);
//
//		GameObjsList_.push_back(go.get());
//	}
//	return go;
//}

size_t ST::GameObj_Manager::size() const{
	return last_gameObj_;
}

ST::GameObj_Manager::GameObj_Manager(const GameObj_Manager& o){

}

ST::GameObj_Manager::~GameObj_Manager(){
	//transformComponentList_.clear();
	//renderComponentList_.clear();
	//hierarchyComponentList_.clear();
	//colliderComponentList_.clear();
}
