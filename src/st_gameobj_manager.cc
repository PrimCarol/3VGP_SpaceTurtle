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
}

const int ST::GameObj_Manager::getGameObjNum(){
	return (int)GameObjsList_.size();
}

/*

* Recordar que nuestra pantalla empieza des de arriba a la izquierda y no des de abajo a la izquierda


void ScreenPosToWorldRay(
	int mouseX, int mouseY,             // Mouse position, in pixels, from bottom-left corner of the window
	int screenWidth, int screenHeight,  // Window size, in pixels
	glm::mat4 ViewMatrix,               // Camera position and orientation
	glm::mat4 ProjectionMatrix,         // Camera parameters (ratio, field of view, near and far planes)
	glm::vec3& out_origin,              // Ouput : Origin of the ray. /!\ Starts at the near plane, so if you want the ray to start at the camera's position instead, ignore this.
	glm::vec3& out_direction            // Ouput : Direction, in world space, of the ray that goes "through" the mouse.
){

	// The ray Start and End positions, in Normalized Device Coordinates (Have you read Tutorial 4 ?)
	glm::vec4 lRayStart_NDC(
		((float)mouseX/(float)screenWidth  - 0.5f) * 2.0f, // [0,1024] -> [-1,1]
		((float)mouseY/(float)screenHeight - 0.5f) * 2.0f, // [0, 768] -> [-1,1]
		-1.0, // The near plane maps to Z=-1 in Normalized Device Coordinates
		1.0f
	);
	glm::vec4 lRayEnd_NDC(
		((float)mouseX/(float)screenWidth  - 0.5f) * 2.0f,
		((float)mouseY/(float)screenHeight - 0.5f) * 2.0f,
		0.0,
		1.0f
	);


	// The Projection matrix goes from Camera Space to NDC.
	// So inverse(ProjectionMatrix) goes from NDC to Camera Space.
	glm::mat4 InverseProjectionMatrix = glm::inverse(ProjectionMatrix);

	// The View Matrix goes from World Space to Camera Space.
	// So inverse(ViewMatrix) goes from Camera Space to World Space.
	glm::mat4 InverseViewMatrix = glm::inverse(ViewMatrix);

	glm::vec4 lRayStart_camera = InverseProjectionMatrix * lRayStart_NDC;    lRayStart_camera/=lRayStart_camera.w;
	glm::vec4 lRayStart_world  = InverseViewMatrix       * lRayStart_camera; lRayStart_world /=lRayStart_world .w;
	glm::vec4 lRayEnd_camera   = InverseProjectionMatrix * lRayEnd_NDC;      lRayEnd_camera  /=lRayEnd_camera  .w;
	glm::vec4 lRayEnd_world    = InverseViewMatrix       * lRayEnd_camera;   lRayEnd_world   /=lRayEnd_world   .w;


	// Faster way (just one inverse)
	//glm::mat4 M = glm::inverse(ProjectionMatrix * ViewMatrix);
	//glm::vec4 lRayStart_world = M * lRayStart_NDC; lRayStart_world/=lRayStart_world.w;
	//glm::vec4 lRayEnd_world   = M * lRayEnd_NDC  ; lRayEnd_world  /=lRayEnd_world.w;


	glm::vec3 lRayDir_world(lRayEnd_world - lRayStart_world);
	lRayDir_world = glm::normalize(lRayDir_world);


	out_origin = glm::vec3(lRayStart_world);
	out_direction = glm::normalize(lRayDir_world);
}
*/

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
	hierarchyComponentList_.clear();
	colliderComponentList_.clear();
}
