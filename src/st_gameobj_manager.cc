#include <st_gameobj_manager.h>

//template<typename ...Component>
//inline ST::GameObj& ST::GameObj_Manager::createGameObj(Component ...comp){
//	static_assert(true && ... && std::is_base_of<Component, Component>::value);
//	Entity e{ std::fordware<Patata>(patata)... };
//	return e;
//}

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
	//GLchar* textVertex = (GLchar*)readFile("../shaders/vertex.vert");
	//vertex.loadSource(textVertex);
	vertex.loadSource(basic_vShader_text);

	ST::Shader fragment(E_FRAGMENT_SHADER);
	//GLchar* textFragment = (GLchar*)readFile("../shaders/fragment.frag");
	//fragment.loadSource(textFragment);
	fragment.loadSource(basic_fShader_text);

	basicProgram = new ST::Program();
	basicProgram->attach(vertex);
	basicProgram->attach(fragment);
	basicProgram->link();
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
	renderComponentList_[RenderCompIndex_ - 1].material->setProgram(basicProgram);
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
		transformComponentList_[i].Move(transformComponentList_[i].getVelocity());
		if (transformComponentList_[i].getPosition().y < -1.0f) {
			
			float randomPosX = -1.5f + (rand() / (RAND_MAX / (1.0f - -1.5f)));
			transformComponentList_[i].setPosition(glm::vec3(randomPosX, 1.0f, 1.0f));

			//transformComponentList_[i].Move(glm::vec3(0.0f, 20.0f, 0.0f));
		}
	}
}

//********** Test *************
#include <thread>
void ST::GameObj_Manager::UpdateRenderMultiThread(){
	int mitad = numGameObjs / 2;
	std::thread t1(&ST::GameObj_Manager::UpdateRender, this, 0, mitad);
	std::thread t2(&ST::GameObj_Manager::UpdateRender, this, mitad+1, numGameObjs);
	t1.join();
	t2.join();
}
//********** Test *************


void ST::GameObj_Manager::UpdateRender(int offset, int to){
	ST::Material* mat = nullptr;
	const ST::Program* p = nullptr;

	int toInside = renderComponentList_.size();
	if (to > 0) {
		toInside = to;
	}

	for (size_t i = offset; i < toInside; i++){
		
		mat = renderComponentList_[i].material;

		if (mat) {

			p = renderComponentList_[i].material->getProgram();

			p->use();

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
