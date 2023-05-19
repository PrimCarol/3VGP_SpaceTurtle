#include "st_system_assets.h"

#include <st_mesh.h>
#include <st_material.h>
#include <imgui.h>


ST::SytemAssets::SytemAssets(){
	ttc_ = TextureToChange::TTC_None;
	materialToChangeTexture = nullptr;
	itsTextureSelectorOpened = false;

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

void ST::SytemAssets::openTextureSelector(ST::Material& mat, TextureToChange ttc){
	itsTextureSelectorOpened = true;
	ttc_ = ttc;
	materialToChangeTexture = &mat;
}

void ST::SytemAssets::closeTextureSelector(){
	itsTextureSelectorOpened = false;
	ttc_ = TextureToChange::TTC_None;
	materialToChangeTexture = nullptr;
}

void ST::SytemAssets::popUpTextureSelector() {

	if (itsTextureSelectorOpened){
		ImGui::Begin("TextureSelector");

		float padding = 10.0f;
		float thumbnailSize = 64.0f;
		float cellSize = thumbnailSize + padding;

		ImVec2 panel_size = ImGui::GetContentRegionAvail();
		int columnCount = (int)(panel_size.x / cellSize);
		ImGui::Columns(columnCount, 0, false);

		// ---- None Case -----
		ImGui::PushID("Internal_None_Texture");
		if (ImGui::ImageButton(0, ImVec2(thumbnailSize, thumbnailSize))) {
			switch (ttc_) {
			case TextureToChange::TTC_Albedo:
				materialToChangeTexture->removeAlbedo();
				break;
			case TextureToChange::TTC_Normal:
				materialToChangeTexture->removeNormal();
				break;
			case TextureToChange::TTC_Specular:
				materialToChangeTexture->removeSpecular();
				break;
			case TextureToChange::TTC_Roughness:
				materialToChangeTexture->removeRoughness();
				break;
			case TextureToChange::TTC_Metallic:
				materialToChangeTexture->removeMetallic();
				break;
			}

			closeTextureSelector();
		}
		ImGui::Text("None"); ImGui::PopID();
		ImGui::NextColumn();

		for (const auto& tex : textures) {
			ImGui::PushID(tex.first.c_str());
			if (ImGui::ImageButton((void*)(intptr_t)tex.second->getID(), ImVec2(thumbnailSize, thumbnailSize))) {
				// UWU
				switch (ttc_){
				case TextureToChange::TTC_Albedo:
					materialToChangeTexture->setTexture_Albedo(tex.second.get());
					break;
				case TextureToChange::TTC_Normal:
					materialToChangeTexture->setTexture_Normal(tex.second.get());
					break;
				case TextureToChange::TTC_Specular:
					materialToChangeTexture->setTexture_Specular(tex.second.get());
					break;
				case TextureToChange::TTC_Roughness:
					materialToChangeTexture->setTexture_Roughness(tex.second.get());
					break;
				case TextureToChange::TTC_Metallic:
					materialToChangeTexture->setTexture_Metallic(tex.second.get());
					break;
				}
				
				closeTextureSelector();
			}
			// Añade texto debajo del botón
			ImGui::Text(tex.first.c_str());

			ImGui::PopID();
			ImGui::NextColumn();
		}

		ImGui::End();
	}
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
