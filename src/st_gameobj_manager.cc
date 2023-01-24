#include <st_gameobj_manager.h>

//template<typename ...Component>
//inline ST::GameObj& ST::GameObj_Manager::createGameObj(Component ...comp){
//	static_assert(true && ... && std::is_base_of<Component, Component>::value);
//	Entity e{ std::fordware<Patata>(patata)... };
//	return e;
//}

/*
 template <class T>
	inline T* get_component() {
		for (unsigned int i = 0; components_.size(); i++) {
			T* aux = dynamic_cast<T*>(components_[i]);
			if (aux) {
				return aux;
			}
		}
		return nullptr;
	}

	 TransformComponent* transform_cmp = m.get_component<TransformComponent>();
*/

//#include <st_raycast.h>

#define MAX_OBJS 50000
#define MAX_TRANSFORM_COMPONENTS MAX_OBJS
#define MAX_RENDER_COMPONENTS MAX_OBJS
#define MAX_COLLIDER_COMPONENTS MAX_OBJS

ST::GameObj_Manager::GameObj_Manager(){

	//printf("***** GameObj Manager Created *****\n");

	GameObjsList_.reserve(MAX_OBJS);

	hierarchyComponentList_.reserve(MAX_OBJS); // Hierarchy
	transformComponentList_.reserve(MAX_TRANSFORM_COMPONENTS); // Transforms
	renderComponentList_.reserve(MAX_RENDER_COMPONENTS); // Render
	//colliderComponentList_.reserve(MAX_COLLIDER_COMPONENTS); // Colliders

	TransCompIndex_ = 0;
	RenderCompIndex_ = 0;
	ColliderCompIndex_ = 0;
	HierarchyCompIndex_ = 0;

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

/*ST::ComponentId ST::GameObj_Manager::createTransformComponent() {
	if (TransCompIndex_ >= MAX_TRANSFORM_COMPONENTS) {
		return ST::TransformComponentId();
	}

	ST::TransformComponentId result;
	result.value = TransCompIndex_;
	result.type = ST::kComp_Trans;

	transformComponentList_.push_back(ST::TransformComponent());
	TransCompIndex_++;

	return result;
}*/

ST::ComponentId ST::GameObj_Manager::createTransformComponent() {
	if (TransCompIndex_ >= MAX_TRANSFORM_COMPONENTS) {
		return ST::TransformComponentId();
	}

	ST::TransformComponentId result;
	result.value = TransCompIndex_;
	result.type = ST::kComp_Trans;

	transformComponentList_.push_back(ST::TransformComponent());
	TransCompIndex_++;

	return result;
}

ST::ComponentId ST::GameObj_Manager::createRenderComponent(){
	if (RenderCompIndex_ >= MAX_RENDER_COMPONENTS) {
		return ST::RenderComponentId();
	}

	ST::RenderComponentId result;
	result.value = RenderCompIndex_;
	result.type = ST::kComp_Render;

	renderComponentList_.push_back(ST::RenderComponent());
	renderComponentList_[RenderCompIndex_]->material->setProgram(basicProgram);
	RenderCompIndex_++;

	return result;
}

ST::ComponentId ST::GameObj_Manager::createColliderComponent() {
	if (ColliderCompIndex_ >= 0) {
		return ST::ColliderComponentId();
	}

	ST::ColliderComponentId result;
	result.value = ColliderCompIndex_;
	result.type = ST::kComp_Collider;

	//colliderComponentList_.push_back(ST::ColliderComponent());
	ColliderCompIndex_++;

	return result;
}

ST::ComponentId ST::GameObj_Manager::createHierarchyComponent(){
	if (HierarchyCompIndex_ >= MAX_OBJS) {
		return ST::HierarchyComponentId();
	}

	ST::HierarchyComponentId result;
	result.value = HierarchyCompIndex_;
	result.type = ST::kComp_Hierarchy;

	hierarchyComponentList_.push_back(ST::HierarchyComponent());
	HierarchyCompIndex_++;

	return result;
}

/*std::unique_ptr<ST::GameObj> ST::GameObj_Manager::createGameObj(const std::vector<ComponentId> c) {

	auto go = std::make_unique<ST::GameObj>();
	if (go) {
		//printf("\n***** Obj Created *****\n");
		//go->components = c;
		go->addComponents(c);
		go->gm_ = this;		

		go->setID((int)GameObjsList_.size());

		GameObjsList_.push_back(go.get());
	}

	//numGameObjs++;

	return go;
}*/

/*std::unique_ptr<ST::GameObj> ST::GameObj_Manager::createGameObj() {

	auto go = std::make_unique<ST::GameObj>();
	if (go) {
		//printf("\n***** Obj Created *****\n");
		//go->components = c;

		std::vector<ST::ComponentId> comps;
		comps.push_back(createHierarchyComponent());
		comps.push_back(createTransformComponent());
		comps.push_back(createRenderComponent());
		comps.push_back(createColliderComponent());
		go->addComponents(comps);
		go->gm_ = this;

		go->setID((int)GameObjsList_.size());

		//char provisionalName[20];
		//sprintf(provisionalName, "GameObj %d", (int)GameObjsList_.size());
		//go->setName(provisionalName);

		GameObjsList_.push_back(go.get());
	}
	return go;
}*/

std::unique_ptr<ST::GameObj> ST::GameObj_Manager::createGameObj() {

	auto go = std::make_unique<ST::GameObj>();
	if (go) {
		//printf("\n***** Obj Created *****\n");
		//go->components = c;

		std::vector<ST::ComponentId> comps;
		comps.push_back(createHierarchyComponent());
		comps.push_back(createTransformComponent());
		comps.push_back(createRenderComponent());
		//comps.push_back(createColliderComponent());
		go->addComponents(comps);
		go->gm_ = this;

		go->setID((int)GameObjsList_.size());

		//char provisionalName[20];
		//sprintf(provisionalName, "GameObj %d", (int)GameObjsList_.size());
		//go->setName(provisionalName);

		GameObjsList_.push_back(go.get());
	}
	return go;
}

const int ST::GameObj_Manager::getGameObjNum(){
	return (int)GameObjsList_.size();
}

ST::GameObj_Manager::GameObj_Manager(const GameObj_Manager& o){}

ST::GameObj_Manager::~GameObj_Manager(){
	transformComponentList_.clear();
	renderComponentList_.clear();
	hierarchyComponentList_.clear();
	colliderComponentList_.clear();
}
