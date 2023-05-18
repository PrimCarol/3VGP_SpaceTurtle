#include "st_system_assets.h"

#include <st_mesh.h>

ST::SytemAssets::SytemAssets(){
	std::shared_ptr<ST::Triangle> triangle = std::make_shared<ST::Triangle>();
	meshes["triangle"] = triangle;
	std::shared_ptr<ST::Quad> quad = std::make_shared<ST::Quad>();
	meshes["quad"] = quad;
	std::shared_ptr<ST::Circle> circle = std::make_shared<ST::Circle>();
	meshes["circle"] = circle;
	std::shared_ptr<ST::Cube> cube = std::make_shared<ST::Cube>();
	meshes["cube"] = cube;
	// Sphere
	saveMesh("../others/sphere.obj");
	// Light Halo
	saveTexture("../others/halo_light.png");
}

std::string getFileName(std::string path, bool whatType = true) {
	bool startChecking = false;
	std::string texName;
	bool end = false;
	for (int i = 0; i < path.size() && end == false; i++) {
		char l = path.at(i);
		if (l == '/' && !startChecking) {
			startChecking = true;
		}
		if (startChecking) {

			if (l == '.' && !whatType) {
				end = true;
			}

			if (l != '/') {
				if (!end) { texName.insert(texName.end(), tolower(l)); }
			}
			else {
				texName.clear();
			}

		}
	}
	printf("%s\n", texName.data());
	return texName;
}

std::string toLower(std::string t) {
	std::string tempText;
	for (int i = 0; i < t.size(); i++){
		tempText.push_back(tolower(t.at(i)));
	}
	return tempText;
}

void ST::SytemAssets::saveTexture(std::string path, bool fliped, ST::Texture::TextType t) {
	std::shared_ptr<ST::Texture> thisTex = std::make_shared<ST::Texture>();
	thisTex->loadSource(path.data(), fliped);
	textures[getFileName(path)] = thisTex;
}

void ST::SytemAssets::saveTextureCubeMap(std::string name, std::vector<std::string> paths){
	std::shared_ptr<ST::Texture> thisTex = std::make_shared<ST::Texture>();
	for (int i = 0; i < paths.size(); i++){
		thisTex->loadCubemap(paths.at(i).data(), i);
	}
	textures[toLower(name)] = thisTex;
}

ST::Texture* ST::SytemAssets::getTexture(std::string name){
	return textures[toLower(name)].get();
}

void ST::SytemAssets::saveMesh(std::string path){
	std::shared_ptr<ST::Geometry> thisMesh = std::make_shared<ST::Geometry>();

	thisMesh->loadFromFile(path.data());
	meshes[getFileName(path, false)] = thisMesh;
}

ST::Mesh* ST::SytemAssets::getMesh(std::string name){
	return meshes[toLower(name)].get();
}

ST::SytemAssets::~SytemAssets(){

}
