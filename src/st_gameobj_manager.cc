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

#include <st_raycast.h>

#define MAX_OBJS 10000
#define MAX_TRANSFORM_COMPONENTS MAX_OBJS
#define MAX_RENDER_COMPONENTS MAX_OBJS
#define MAX_COLLIDER_COMPONENTS MAX_OBJS

ST::GameObj_Manager::GameObj_Manager(){

	//printf("***** GameObj Manager Created *****\n");

	GameObjsList_.reserve(MAX_OBJS);

	hierarchyComponentList_.reserve(MAX_OBJS); // Hierarchy
	transformComponentList_.reserve(MAX_TRANSFORM_COMPONENTS); // Transforms
	renderComponentList_.reserve(MAX_RENDER_COMPONENTS); // Render
	colliderComponentList_.reserve(MAX_COLLIDER_COMPONENTS); // Colliders

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

	// ------- Cam -------
	cam_ = std::make_unique<ST::Camera>();
}

ST::ComponentId ST::GameObj_Manager::createTransformComponent(){
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
	renderComponentList_[RenderCompIndex_].material->setProgram(basicProgram);
	RenderCompIndex_++;

	return result;
}

ST::ComponentId ST::GameObj_Manager::createColliderComponent() {
	if (ColliderCompIndex_ >= MAX_COLLIDER_COMPONENTS) {
		return ST::ColliderComponentId();
	}

	ST::ColliderComponentId result;
	result.value = ColliderCompIndex_;
	result.type = ST::kComp_Collider;

	colliderComponentList_.push_back(ST::ColliderComponent());
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

std::unique_ptr<ST::GameObj> ST::GameObj_Manager::createGameObj() {

	auto go = std::make_unique<ST::GameObj>();
	if (go) {
		//printf("\n***** Obj Created *****\n");
		//go->components = c;

		std::vector<ST::ComponentId> comps;
		comps.push_back(createHierarchyComponent());
		comps.push_back(createTransformComponent());
		comps.push_back(createRenderComponent());
		go->addComponents(comps);
		go->gm_ = this;

		go->setID((int)GameObjsList_.size());

		GameObjsList_.push_back(go.get());
	}
	return go;
}

const int ST::GameObj_Manager::getGameObjNum(){
	return (int)GameObjsList_.size();
}

//void ST::GameObj_Manager::UpdateTransforms(){
//
//	for (int i = 0; i < transformComponentList_.size(); i++){
//		//transformComponentList_[i].RotateY(transformComponentList_[i].getRotation().y + 0.03f);
//		if (hierarchyComponentList_[i].parentID != -1) {
//			ST::TransformComponent* transPa = (ST::TransformComponent*)GameObjsList_[hierarchyComponentList_[i].parentID]->getComponent(ST::kComp_Trans);
//			transformComponentList_[i].m_transform_ = transPa->m_transform_ * transformComponentList_[i].m_transform_;
//		}
//		//transformComponentList_[i].Update();
//	}
//}

/*ST::GameObj* ST::GameObj_Manager::tryPickObj() {

	float objClose = 100000.0f;
	int objIndexClose = -1;

	for (int i = 0; i < GameObjsList_.size(); i++) {

		ST::TransformComponent* t = (ST::TransformComponent*)GameObjsList_[i]->getComponent(ST::kComp_Trans);

		if (t) {

			ST::Raycast ray;

			//glm::vec3 colliderPoint_min(-1.0f, -1.0f, -1.0f); // Collider
			//glm::vec3 colliderPoint_max(1.0f, 1.0f, 1.0f);

			glm::vec3 colliderPoint_min(-colliderComponentList_[i].size_);
			glm::vec3 colliderPoint_max(colliderComponentList_[i].size_);

			float outputDistance = 100000.0f;

			// Enfrente de la camara.
			if (ray.TraceRay(cam_->transform_.getPosition(), cam_->transform_.getForward(), colliderPoint_min, colliderPoint_max,
				t->m_transform_, outputDistance)) {

				if (outputDistance < objClose) {
					objClose = outputDistance;
					objIndexClose = i;
				}
			}
		}

	}
	
	if (objIndexClose != -1) {
		return GameObjsList_[objIndexClose];
	}

	return nullptr;
}*/

ST::GameObj_Manager::GameObj_Manager(const GameObj_Manager& o){}

ST::GameObj_Manager::~GameObj_Manager(){
	transformComponentList_.clear();
	renderComponentList_.clear();
	colliderComponentList_.clear();
}
