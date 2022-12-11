#include <st_gameobj_manager.h>

//template<typename ...Component>
//inline ST::GameObj& ST::GameObj_Manager::createGameObj(Component ...comp){
//	static_assert(true && ... && std::is_base_of<Component, Component>::value);
//	Entity e{ std::fordware<Patata>(patata)... };
//	return e;
//}

#include <st_engine.h>

#include <st_raycast.h>

#define MAX_OBJS 1000000
#define MAX_TRANSFORM_COMPONENTS 1000000
#define MAX_RENDER_COMPONENTS 1000000

ST::GameObj_Manager::GameObj_Manager(){

	//printf("***** GameObj Manager Created *****\n");

	GameObjsList_.reserve(MAX_OBJS);

	transformComponentList_.reserve(MAX_TRANSFORM_COMPONENTS);
	renderComponentList_.reserve(MAX_RENDER_COMPONENTS);

	TransCompIndex_ = 0;
	RenderCompIndex_ = 0;

	// ------- Create Basic Program -------
	ST::Shader vertex(E_VERTEX_SHADER);
	GLchar* textVertex = (GLchar*)ST::Engine::readFile("../shaders/vertex.vert");
	vertex.loadSource(textVertex);
	//vertex.loadSource(basic_vShader_text);

	ST::Shader fragment(E_FRAGMENT_SHADER);
	GLchar* textFragment = (GLchar*)ST::Engine::readFile("../shaders/fragment.frag");
	fragment.loadSource(textFragment);
	//fragment.loadSource(basic_fShader_text);

	basicProgram = new ST::Program();
	basicProgram->attach(vertex);
	basicProgram->attach(fragment);
	basicProgram->link();

	// Cam
	cam_ = new ST::Camera();
	//cam_->setOrthographic(20.0f,20.0f, 0.05f, 10000.0f);
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

void ST::GameObj_Manager::UpdateRender(){
	ST::Material* mat = nullptr;
	const ST::Program* p = nullptr;

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	cam_->update();

	for (size_t i = 0; i < renderComponentList_.size(); i++) {
		
		// Material
		mat = renderComponentList_[i].material;
		if (mat) {

			p = renderComponentList_[i].material->getProgram();

			p->use();

			// ------ Camara -------
			GLuint camPos = p->getUniform("u_view_pos");
			glm::vec3 camTransPos = cam_->transform_.getPosition();
			glUniform3fv(camPos, 1, &camTransPos.x);
			GLuint camView = p->getUniform("u_view_matrix");
			glUniformMatrix4fv(camView, 1, GL_FALSE, &cam_->view[0][0]);
			GLuint camProjection = p->getUniform("u_projection_matrix");
			glUniformMatrix4fv(camProjection, 1, GL_FALSE, &cam_->projection[0][0]);
			GLuint camVP = p->getUniform("u_vp_matrix");
			glm::mat4 cam_m_vp = cam_->projection * cam_->view;
			glUniformMatrix4fv(camVP, 1, GL_FALSE, &cam_m_vp[0][0]);
			// ------ Camara -------

			// De momento esta mal, funciona 1:1.
			GLuint u_m_trans = p->getUniform("u_m_trans");
			glUniformMatrix4fv(u_m_trans, 1, GL_FALSE, &transformComponentList_[i].m_transform_[0][0]);

			// Material 
			GLuint u_color = p->getUniform("u_color");
			glm::vec3 c = mat->getColor();
			glUniform3fv(u_color, 1, &c[0]);

			GLuint u_haveAlbedo = p->getUniform("u_haveAlbedo");
			glUniform1i(u_haveAlbedo, mat->haveAlbedo);
			
			if (mat->haveAlbedo) {
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, mat->getAlbedo()->getID());
			}
		}
		if (renderComponentList_[i].mesh) {
			renderComponentList_[i].mesh->render();
		}

		glUseProgram(0);
	}
}

ST::GameObj* ST::GameObj_Manager::tryPickObj(){

	//printf("Camera Forward: %f / %f / %f \n", cam_->transform_.getForward().x, cam_->transform_.getForward().y, cam_->transform_.getForward().z);

	//ST::Raycast ray;
	//ray.drawRay(glm::vec3(100.0f,0.0f,100.0f), glm::vec3(0.0f,0.0f,0.0f));

	float objClose = 100000.0f;
	int objIndexClose = -1;

	for (int i = 0; i < GameObjsList_.size(); i++) {

		ST::TransformComponent* t = (ST::TransformComponent*)GameObjsList_[i]->getComponent(ST::kComp_Trans);

		if (t) {

			ST::Raycast ray;

			glm::vec3 colliderPoint_min(-1.0f, -1.0f, -1.0f); // Collider
			glm::vec3 colliderPoint_max(1.0f, 1.0f, 1.0f);

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
		//printf("Detecto el objeto -> %d \n", objIndexClose);
		//printf("Esta a %f de distancia. \n", objClose);

		return GameObjsList_[objIndexClose];
		//return nullptr;
	}

	return nullptr;
}

ST::GameObj_Manager::GameObj_Manager(const GameObj_Manager& o){}

ST::GameObj_Manager::~GameObj_Manager(){}
