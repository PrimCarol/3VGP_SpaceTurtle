#include "st_system_assets.h"

#include <st_mesh.h>

ST::SytemAssets::SytemAssets(){
	std::shared_ptr<ST::Cube> cube = std::make_shared<ST::Cube>();
	meshes["Cube"] = cube;
	std::shared_ptr<ST::Quad> quad = std::make_shared<ST::Quad>();
	meshes["Quad"] = quad;
}

std::string getFileName(std::string path, bool type = true) {
	bool startChecking = false;
	std::string texName;
	for (int i = 0; i < path.size(); i++) {
		char l = path.at(i);
		if (l == '/' && !startChecking) {
			startChecking = true;
		}
		if (startChecking) {

			if (l == '.' && !type) {
				exit;
			}

			if (l != '/') {
				texName.insert(texName.end(), l);
			}
			else {
				texName.clear();
			}

		}
	}
	printf("%s\n", texName.data());
	return texName;
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
	textures[name] = thisTex;
}

ST::Texture* ST::SytemAssets::getTexture(std::string name){
	return textures[name].get();
}

void ST::SytemAssets::saveMesh(std::string path){
	std::shared_ptr<ST::Geometry> thisMesh = std::make_shared<ST::Geometry>();

	thisMesh->loadFromFile(path.data());
	meshes[getFileName(path)] = thisMesh;
}

ST::Mesh* ST::SytemAssets::getMesh(std::string name){
	return meshes[name].get();
}

ST::SytemAssets::~SytemAssets(){

}
