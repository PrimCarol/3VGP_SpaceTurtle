#include <st_gameobj_manager.h>

//template<typename ...Component>
//inline ST::GameObj& ST::GameObj_Manager::createGameObj(Component ...comp){
//	static_assert(true && ... && std::is_base_of<Component, Component>::value);
//	Entity e{ std::fordware<Patata>(patata)... };
//	return e;
//}

#include <st_engine.h>

#define MAX_TRANSFORM_COMPONENTS 1000000
#define MAX_RENDER_COMPONENTS 1000000

ST::GameObj_Manager::GameObj_Manager(){

	//printf("***** GameObj Manager Created *****\n");

	numGameObjs = 0;

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
	cam_ = new ST::Camera(1080, 720, glm::vec3(0.0f,0.0f,0.0f));
	
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
	}

	numGameObjs++;

	return go;
}

const int ST::GameObj_Manager::getGameObjNum(){
	return numGameObjs;
}

void ST::GameObj_Manager::UpdateTransforms(){
	for (int i = 0; i < transformComponentList_.size(); i++){
		transformComponentList_[i].RotateY(0.07f);
	}
}

void ST::GameObj_Manager::UpdateRender(){
	ST::Material* mat = nullptr;
	const ST::Program* p = nullptr;

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	cam_->updateMatrix(90.0f, 0.03f, 500.0f);

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
	}
}

ST::GameObj_Manager::GameObj_Manager(const GameObj_Manager& o){}

ST::GameObj_Manager::~GameObj_Manager(){}
