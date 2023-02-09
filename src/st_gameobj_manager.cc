#include <st_gameobj_manager.h>

#include <st_gameobj.h>

#include <components/st_transform.h>
#include <components/st_render.h>
#include <components/st_collider.h>
#include <components/st_hierarchy.h>

#define MAX_OBJS 50000

ST::GameObj_Manager::GameObj_Manager(){

	//printf("***** GameObj Manager Created *****\n");

	//GameObjsList_.reserve(MAX_OBJS);

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

template<typename... Cs>
ST::GameObj ST::GameObj_Manager::createGameObj(Cs... components) {
	GameObj ref{ last_gameObj_++, *this };
	for (auto& [type, component_list] : component_map_) {
		component_list->grow(last_entity_);
	}
	(addComponent<Cs>(ref, components), ...);
	return ref;
}

template<typename C>
ST::GameObj ST::GameObj_Manager::getGameObj(const C& component) const {
	auto mut_this = const_cast<ST::GameObj_Manager*>(this);
	do {
		auto cl = mut_this->getComponentVector<C>();
		if (!cl) break;

		auto hacky_ptr = reinterpret_cast<const std::optional<C>*>(&component);
		auto begin = cl->data();
		auto end = begin + cl->size();
		if (hacky_ptr < begin || hacky_ptr >= end) break;

		auto distance = static_cast<size_t>(hacky_ptr - cl->data());
		return ST::GameObj{ distance, *mut_this };
	} while (false);
	return ST::GameObj{ ST::GameObj::null_id,*mut_this };
}

template<typename C>
bool ST::GameObj_Manager::addComponent(ST::GameObj ref, C component) {
	auto cl = getComponentList<C>();
	if (!cl) return false;
	cl->at(ref.id_) = std::forward<C>(component);
	return true;
}

template<typename C>
void ST::GameObj_Manager::addComponentClass() {
	std::unique_ptr<ComponentVector> ptr = std::make_unique<ComponentListImpl<C>>();
	ptr->grow(last_gameObj_);
	component_map_.insert({ typeid(C) , std::move(ptr) });
}

template<typename C>
std::vector<std::optional<C>>* ST::GameObj_Manager::getComponentVector() {
	auto result = component_map_.find(std::type_index{ typeid(C) });
	if (result == component_map_.end()) return nullptr;
	auto ptr = static_cast<ComponentListImpl<C>*>(result->second.get());
	return &(ptr->component_list);
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

//const int ST::GameObj_Manager::getGameObjNum(){
//	return (int)GameObjsList_.size();
//}

ST::GameObj_Manager::GameObj_Manager(const GameObj_Manager& o){

}

ST::GameObj_Manager::~GameObj_Manager(){
	//transformComponentList_.clear();
	//renderComponentList_.clear();
	//hierarchyComponentList_.clear();
	//colliderComponentList_.clear();
}
