#include <st_gameobj_manager.h>

#include <st_engine.h>
#include <st_gameobj.h>

#include <components/st_transform.h>
#include <components/st_hierarchy.h>
#include <components/st_name.h>
#include <components/st_render.h>
#include <components/st_collider.h>
#include <components/st_light.h>
#include <components/st_camera.h>

ST::GameObj_Manager::GameObj_Manager(){

	addComponentClass<ST::TransformComponent>();
	addComponentClass<ST::HierarchyComponent>();
	addComponentClass<ST::NameComponent>();
	addComponentClass<ST::RenderComponent>();
	addComponentClass<ST::ColliderComponent>();
	addComponentClass<ST::LightComponent>();
	addComponentClass<ST::CameraComponent>();
	
	objectSelected = ST::GameObj::null_id;
	root.addComponent<ST::HierarchyComponent>();

	mainCameraID_ = -1;


	// ------- Create Basic Program -------
	basicProgram = std::make_unique<ST::Program>();
	bool shaderError = false;

	ST::Shader vertex(E_VERTEX_SHADER);
	GLchar* textVertex = (GLchar*)ST::Engine::readFile("../shaders/shader_instancing.vert");
	if (!textVertex) {
		shaderError = true;
		printf("Error load Vertex Shader");
	}

	ST::Shader fragment(E_FRAGMENT_SHADER);
	GLchar* textFragment = (GLchar*)ST::Engine::readFile("../shaders/shader_instancing.frag");
	if (!textFragment) {
		shaderError = true;
		printf("Error load Fragment Shader");
	}

	if (shaderError) {
		textVertex = (GLchar*)ST::basic_vShader_text;
		textFragment = (GLchar*)ST::basic_fShader_text;
	}

	vertex.loadSource(textVertex);
	fragment.loadSource(textFragment);

	basicProgram->attach(vertex);
	basicProgram->attach(fragment);
	basicProgram->link();

	// ------- Create Unlite Program -------
	unliteProgram = std::make_unique<ST::Program>();
	shaderError = false;

	ST::Shader vertexUnlite(E_VERTEX_SHADER);
	GLchar* textVertexUnlite = (GLchar*)ST::Engine::readFile("../shaders/shader_unlite.vert");
	if (!textVertexUnlite) {
		shaderError = true;
		printf("Error load Vertex Shader Unlite");
	}

	ST::Shader fragmentUnlite(E_FRAGMENT_SHADER);
	GLchar* textFragmentUnlite = (GLchar*)ST::Engine::readFile("../shaders/shader_unlite.frag");
	if (!textFragmentUnlite) {
		shaderError = true;
		printf("Error load Fragment Shader Unlite");
	}

	if (shaderError) {
		textVertexUnlite = (GLchar*)ST::basic_vShader_text;
		textFragmentUnlite = (GLchar*)ST::basic_fShader_text;
	}

	vertexUnlite.loadSource(textVertexUnlite);
	fragmentUnlite.loadSource(textFragmentUnlite);

	unliteProgram->attach(vertexUnlite);
	unliteProgram->attach(fragmentUnlite);
	unliteProgram->link();

	// ------- Create Shadow Mapping Program -------
	shadowMapping = std::make_unique<ST::Program>();
	shaderError = false;

	ST::Shader vertexShadowMapping(E_VERTEX_SHADER);
	GLchar* textVertexShadowMapping = (GLchar*)ST::Engine::readFile("../shaders/shadowMapping.vert");
	if (!textVertexShadowMapping) {
		shaderError = true;
		printf("Error load Vertex Shader ShadowMapping");
	}

	ST::Shader fragmentShadowMapping(E_FRAGMENT_SHADER);
	GLchar* textFragmentShadowMapping = (GLchar*)ST::Engine::readFile("../shaders/shadowMapping.frag");
	if (!textFragmentShadowMapping) {
		shaderError = true;
		printf("Error load Fragment Shader ShadowMapping");
	}

	if (shaderError) {
		textVertexShadowMapping = (GLchar*)ST::basic_vShader_text;
		textFragmentShadowMapping = (GLchar*)ST::basic_fShader_text;
	}

	vertexShadowMapping.loadSource(textVertexShadowMapping);
	fragmentShadowMapping.loadSource(textFragmentShadowMapping);

	shadowMapping->attach(vertexShadowMapping);
	shadowMapping->attach(fragmentShadowMapping);
	shadowMapping->link();

	haveShadowMap_ = false;
	shadowMap.setUp(2560, 2560, ST::Texture::F_DEPTH, ST::Texture::DT_FLOAT);
	//shadowMap.setUp(16, 16, ST::Texture::F_DEPTH, ST::Texture::DT_FLOAT);
	windowSize_ = glm::vec2(0.0f);
}

void ST::GameObj_Manager::deleteGameObj(int ObjID){
	for (auto& [type, components_vector_] : component_map_) {
		components_vector_->deleteOn(ObjID);
	}
}

size_t ST::GameObj_Manager::size() const{
	return last_gameObj_;
}

void ST::GameObj_Manager::setMainCamera(const ST::GameObj& cam){
	if (cam.getComponent<ST::CameraComponent>()) {
		mainCameraID_ = cam.getID();
	}else {
		mainCameraID_ = -1;
	}
}

int ST::GameObj_Manager::mainCameraID() const{
	return mainCameraID_;
}

ST::GameObj_Manager::GameObj_Manager(const GameObj_Manager& o){
	printf("Copia GameObj_Manager -> No deberia de estar haciendo esto.");
}

ST::GameObj_Manager::~GameObj_Manager(){

}
