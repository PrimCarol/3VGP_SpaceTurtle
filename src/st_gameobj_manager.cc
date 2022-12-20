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

#define MAX_OBJS 1000000
#define MAX_TRANSFORM_COMPONENTS 1000000
#define MAX_RENDER_COMPONENTS 1000000
#define MAX_COLLIDER_COMPONENTS 1000000

ST::GameObj_Manager::GameObj_Manager(){

	//printf("***** GameObj Manager Created *****\n");

	GameObjsList_.reserve(MAX_OBJS);

	transformComponentList_.reserve(MAX_TRANSFORM_COMPONENTS); // Transforms
	renderComponentList_.reserve(MAX_RENDER_COMPONENTS); // Render
	colliderComponentList_.reserve(MAX_COLLIDER_COMPONENTS); // Colliders

	TransCompIndex_ = 0;
	RenderCompIndex_ = 0;
	ColliderCompIndex_ = 0;

	// ------- Create Basic Program -------
	basicProgram = new ST::Program();
	if (!basicProgram->setUp("../shaders/vertex.vert", "../shaders/fragment.frag")) {
		printf("*Error* Creating Basic Program.");
	}

	// ------- Cam -------
	cam_ = new ST::Camera();
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

std::unique_ptr<ST::GameObj> ST::GameObj_Manager::createGameObj(const std::vector<ComponentId> c){

	auto go = std::make_unique<ST::GameObj>();
	if (go) {
		//printf("\n***** Obj Created *****\n");
		go->components = c;
		go->gm_ = this;		

		go->setID(GameObjsList_.size());

		GameObjsList_.push_back(go.get());
	}

	//numGameObjs++;

	return go;
}

const int ST::GameObj_Manager::getGameObjNum(){
	return GameObjsList_.size();
}

void ST::GameObj_Manager::UpdateTransforms(){

	for (int i = 0; i < transformComponentList_.size(); i++){
		transformComponentList_[i].RotateY(transformComponentList_[i].getRotation().y + 0.03f);

		transformComponentList_[i].Update();
	}
}

ST::GameObj* ST::GameObj_Manager::tryPickObj(){

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
}

ST::GameObj_Manager::GameObj_Manager(const GameObj_Manager& o){}

ST::GameObj_Manager::~GameObj_Manager(){
	transformComponentList_.clear();
	renderComponentList_.clear();
	colliderComponentList_.clear();

	delete basicProgram;
	delete cam_;
}
