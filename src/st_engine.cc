#include "st_engine.h"

const float ST::Engine::getRandom(float min, float max){
	return min + (rand() / (RAND_MAX / (max - min)));
}

const unsigned char* ST::Engine::readFile(const char* filename){
	FILE* in_file = 0;
	int err = fopen_s(&in_file, filename, "rb");
	//assert(in_file);
	if (!in_file) { return nullptr; }
	struct stat sb;
	if (stat(filename, &sb) == -1) { return nullptr; }
	//assert(stat(filename, &sb) != -1);
	unsigned char* file_contents = (unsigned char*)malloc(sb.st_size + 1);
	if (file_contents) {
		fread(file_contents, sb.st_size, 1, in_file);
		file_contents[sb.st_size] = 0;
		fclose(in_file);
	}
	return file_contents;
}

void ST::Engine::createEmptyObj(ST::GameObj_Manager& gm){
	gm.createGameObj(ST::TransformComponent{});
}

void ST::Engine::createTriangle(ST::GameObj_Manager& gm){
	static ST::Triangle mesh_Triangle_;
	ST::GameObj temp = gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{});
	temp.getComponent<ST::RenderComponent>()->setMesh(&mesh_Triangle_);
	temp.getComponent<ST::RenderComponent>()->material.setProgram(gm.basicProgram);
}

void ST::Engine::createQuad(ST::GameObj_Manager& gm) {
	static ST::Quad mesh_Quad_;
	ST::GameObj temp = gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{});
	temp.getComponent<ST::RenderComponent>()->setMesh(&mesh_Quad_);
	temp.getComponent<ST::RenderComponent>()->material.setProgram(gm.basicProgram);
}

void ST::Engine::createCircle(ST::GameObj_Manager& gm) {
	static ST::Circle mesh_Circle_;
	ST::GameObj temp = gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{});
	temp.getComponent<ST::RenderComponent>()->setMesh(&mesh_Circle_);
	temp.getComponent<ST::RenderComponent>()->material.setProgram(gm.basicProgram);
}

void ST::Engine::createCube(ST::GameObj_Manager& gm) {
	static ST::Cube mesh_Cube_;
	ST::GameObj temp = gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{});
	temp.getComponent<ST::RenderComponent>()->setMesh(&mesh_Cube_);
	temp.getComponent<ST::RenderComponent>()->material.setProgram(gm.basicProgram);
}

void ST::Engine::createDirectLight(ST::GameObj_Manager& gm){
	ST::GameObj temp = gm.createGameObj(ST::TransformComponent{}, ST::LightComponent{});

	temp.getComponent<ST::NameComponent>()->setName("Directional Light");
	temp.getComponent<ST::TransformComponent>()->setRotateY(-0.5f);
	temp.getComponent<ST::TransformComponent>()->setRotateX(1.0f);
	temp.getComponent<ST::LightComponent>()->type_ = ST::Directional;
	temp.getComponent<ST::LightComponent>()->ambient_ = glm::vec3(0.3f, 0.3f, 0.3f);
}

void ST::Engine::createPointLight(ST::GameObj_Manager& gm) {
	ST::GameObj temp = gm.createGameObj(ST::TransformComponent{}, ST::LightComponent{}, ST::RenderComponent{}, ST::ColliderComponent{});

	temp.getComponent<ST::NameComponent>()->setName("Point Light");
	temp.getComponent<ST::LightComponent>()->type_ = ST::Point;

	static ST::Quad mesh_Quad_;
	static ST::Texture halo_Light;
	halo_Light.loadSource("../others/halo_light.png");
	temp.getComponent<ST::RenderComponent>()->material.setProgram(gm.basicProgram);
	temp.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&halo_Light);
	temp.getComponent<ST::RenderComponent>()->material.translucent = true;
	temp.getComponent<ST::RenderComponent>()->setMesh(&mesh_Quad_);
}

void ST::Engine::createSpotLight(ST::GameObj_Manager& gm) {
	ST::GameObj temp = gm.createGameObj(ST::TransformComponent{}, ST::LightComponent{});

	temp.getComponent<ST::NameComponent>()->setName("Spot Light");
	temp.getComponent<ST::LightComponent>()->type_ = ST::Spot;
	temp.getComponent<ST::TransformComponent>()->setRotateY(-1.0f);
}
