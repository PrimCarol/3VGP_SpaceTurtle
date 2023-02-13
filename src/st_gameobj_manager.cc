#include <st_gameobj_manager.h>

#include <st_engine.h>
#include <st_gameobj.h>

#include <components/st_transform.h>
#include <components/st_hierarchy.h>
#include <components/st_name.h>
#include <components/st_render.h>
#include <components/st_collider.h>
#include <components/st_light.h>

ST::GameObj_Manager::GameObj_Manager(){

	addComponentClass<ST::TransformComponent>();
	addComponentClass<ST::HierarchyComponent>();
	addComponentClass<ST::NameComponent>();
	addComponentClass<ST::RenderComponent>();
	addComponentClass<ST::ColliderComponent>();
	addComponentClass<ST::LightComponent>();
	
	objectSelected = ST::GameObj::null_id;
	root.addComponent<ST::HierarchyComponent>();

	// ------- Create Basic Program -------
	basicProgram = std::make_unique<ST::Program>();

	bool shaderError = false;
	ST::Shader vertex(E_VERTEX_SHADER);
	GLchar* textVertex = (GLchar*)ST::Engine::readFile("../shaders/shader01.vert");
	if (!textVertex) {
		shaderError = true;
		printf("Error load Vertex Shader");
	}

	ST::Shader fragment(E_FRAGMENT_SHADER);
	GLchar* textFragment = (GLchar*)ST::Engine::readFile("../shaders/shader01.frag");
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
}

void ST::GameObj_Manager::deleteGameObj(int ObjID){
	for (auto& [type, components_vector_] : component_map_) {

	}
}

size_t ST::GameObj_Manager::size() const{
	return last_gameObj_;
}

ST::GameObj_Manager::GameObj_Manager(const GameObj_Manager& o){

}

ST::GameObj_Manager::~GameObj_Manager(){

}
