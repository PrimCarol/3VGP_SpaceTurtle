#include "st_system_assets.h"

#include <st_mesh.h>
#include <st_render.h>
#include <st_material.h>
#include <st_gameobj_manager.h>
#include <imgui.h>

#include <string>

void TextCentered(const std::string& text) {

	float win_width = ImGui::GetWindowSize().x;
	float text_width = ImGui::CalcTextSize(text.c_str()).x;

	float text_indentation = (win_width - text_width) * 0.5f;

	float min_indentation = 20.0f;
	if (text_indentation <= min_indentation) {
		text_indentation = min_indentation;
	}

	ImGui::Spacing();
	ImGui::SameLine(text_indentation);
	ImGui::PushTextWrapPos(win_width - text_indentation);
	ImGui::TextWrapped(text.c_str());
	ImGui::PopTextWrapPos();
	ImGui::Spacing();
	ImGui::Spacing();
}

ST::SytemAssets::SytemAssets(){
	ttc_ = TextureToChange::TTC_None;
	materialToChangeTexture = nullptr;
	itsTextureSelectorOpened = false;
	itsCubeMapSelectorOpened = false;
	itsMeshSelectorOpened = false;
	renderToChangeMesh = nullptr;

	std::shared_ptr<ST::Triangle> triangle = std::make_shared<ST::Triangle>();
	meshes["triangle"] = triangle;
	triangle->setName("triangle");
	std::shared_ptr<ST::Quad> quad = std::make_shared<ST::Quad>();
	meshes["quad"] = quad;
	quad->setName("quad");
	std::shared_ptr<ST::Circle> circle = std::make_shared<ST::Circle>();
	meshes["circle"] = circle;
	circle->setName("circle");
	std::shared_ptr<ST::Cube> cube = std::make_shared<ST::Cube>();
	meshes["cube"] = cube;
	cube->setName("cube");
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
	cubeMaps[toLower(name)] = thisTex;
}

ST::Texture* ST::SytemAssets::getTexture(std::string name){
	//return textures[toLower(name)].get();
	auto& iter = textures.find(toLower(name));
	if (iter != textures.end()) {
		return iter->second.get();
	}
	return nullptr;
}

ST::Texture* ST::SytemAssets::getCubeMap(std::string name){
	//return cubeMaps[toLower(name)].get();
	auto& iter = cubeMaps.find(toLower(name));
	if (iter != cubeMaps.end()) {
		return iter->second.get();
	}
	return nullptr;
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

		ImGui::OpenPopup("TextureSelectorPopUp");

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove
									| ImGuiWindowFlags_NoResize
									| ImGuiWindowFlags_NoCollapse
									| ImGuiWindowFlags_NoTitleBar
									| ImGuiWindowFlags_NoDocking;

		ImVec2 windowSize = { ImGui::GetMainViewport()->Size.x * 0.8f, ImGui::GetMainViewport()->Size.y * 0.8f };
		ImVec2 center = ImGui::GetMainViewport()->GetCenter();
		ImGui::SetNextWindowSize({ windowSize }, ImGuiCond_Appearing);

		if (ImGui::BeginPopupModal("TextureSelectorPopUp", NULL, window_flags)){
			
			ImVec2 getwindowSize = { ImGui::GetWindowSize().x, ImGui::GetWindowSize().y};
			
			ImGui::SetWindowPos({ center.x - getwindowSize.x * 0.5f, center.y - getwindowSize.y * 0.5f });

			float padding = 10.0f;
			float thumbnailSize = 128.0f;
			float cellSize = thumbnailSize + padding * 2.0f;

			switch (ttc_) {
			case TextureToChange::TTC_Albedo:
				TextCentered("TEXTURE SELECTOR: ALBEDO");
				break;
			case TextureToChange::TTC_Normal:
				TextCentered("TEXTURE SELECTOR: NORMAL");
				break;
			case TextureToChange::TTC_Specular:
				TextCentered("TEXTURE SELECTOR: SPECULAR");
				break;
			case TextureToChange::TTC_Roughness:
				TextCentered("TEXTURE SELECTOR: ROUGHNESS");
				break;
			case TextureToChange::TTC_Metallic:
				TextCentered("TEXTURE SELECTOR: METALLIC");
				break;
			}


			ImVec2 panel_size = ImGui::GetContentRegionAvail();
			int columnCount = (int)(panel_size.x / cellSize);
			if (columnCount <= 0) { columnCount = 1; }
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

				ImGui::CloseCurrentPopup();
				closeTextureSelector();
			}
			ImGui::Text("None");
			ImGui::PopID();
			ImGui::NextColumn();

			for (const auto& tex : textures) {
				ImGui::PushID(tex.first.c_str());

				bool colorChanged = false;

				switch (ttc_) {
				case TextureToChange::TTC_Albedo:
					if (materialToChangeTexture->haveAlbedo && tex.second->getID() == materialToChangeTexture->getAlbedo()->getID()) {
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0,1.0,1.0,1.0));
						colorChanged = true;
					}
					break;
				case TextureToChange::TTC_Normal:
					if (materialToChangeTexture->haveNormal && tex.second->getID() == materialToChangeTexture->getNormal()->getID()) {
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0, 1.0, 1.0, 1.0));
						colorChanged = true;
					}
					break;
				case TextureToChange::TTC_Specular:
					if (materialToChangeTexture->haveSpecular && tex.second->getID() == materialToChangeTexture->getSpecular()->getID()) {
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0, 1.0, 1.0, 1.0));
						colorChanged = true;
					}
					break;
				case TextureToChange::TTC_Roughness:
					if (materialToChangeTexture->haveRoughness && tex.second->getID() == materialToChangeTexture->getRoughness()->getID()) {
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0, 1.0, 1.0, 1.0));
						colorChanged = true;
					}
					break;
				case TextureToChange::TTC_Metallic:
					if (materialToChangeTexture->haveMetallic && tex.second->getID() == materialToChangeTexture->getMetallic()->getID()) {
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0, 1.0, 1.0, 1.0));
						colorChanged = true;
					}
					break;
				}

				if (ImGui::ImageButton((void*)(intptr_t)tex.second->getID(), ImVec2(thumbnailSize, thumbnailSize))) {
					// UWU
					switch (ttc_) {
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
					ImGui::CloseCurrentPopup();
					closeTextureSelector();
				}
				
				if(colorChanged)
					ImGui::PopStyleColor(1);

				ImGui::Text(tex.first.c_str());

				ImGui::PopID();
				ImGui::NextColumn();
			}

			ImGui::EndPopup();
		}
	}
}

void ST::SytemAssets::openCubeMapSelector(){
	itsCubeMapSelectorOpened = true;
}

void ST::SytemAssets::closeCubeMapSelector(){
	itsCubeMapSelectorOpened = false;
}

void ST::SytemAssets::popUpCubeMapSelector(ST::GameObj_Manager& gm) {

	if (itsCubeMapSelectorOpened) {

		ImGui::OpenPopup("CubeMapSelectorPopUp");

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoDocking;

		ImVec2 windowSize = { ImGui::GetMainViewport()->Size.x * 0.8f, ImGui::GetMainViewport()->Size.y * 0.8f };
		ImVec2 center = ImGui::GetMainViewport()->GetCenter();
		ImGui::SetNextWindowSize({ windowSize }, ImGuiCond_Appearing);

		if (ImGui::BeginPopupModal("CubeMapSelectorPopUp", NULL, window_flags)) {

			ImVec2 getwindowSize = { ImGui::GetWindowSize().x, ImGui::GetWindowSize().y };

			ImGui::SetWindowPos({ center.x - getwindowSize.x * 0.5f, center.y - getwindowSize.y * 0.5f });

			float padding = 10.0f;
			float thumbnailSize = 128.0f;
			float cellSize = thumbnailSize + padding * 2.0f;

			TextCentered("TEXTURE SELECTOR: CUBEMAP");

			ImVec2 panel_size = ImGui::GetContentRegionAvail();
			int columnCount = (int)(panel_size.x / cellSize);
			if (columnCount <= 0) { columnCount = 1; }
			ImGui::Columns(columnCount, 0, false);

			bool removeTexture = false;;

			// ---- None Case -----
			ImGui::PushID("Internal_None_CubeMap");
			if (ImGui::ImageButton(0, ImVec2(thumbnailSize, thumbnailSize))) {
				removeTexture = true;
			}
			ImGui::Text("None");
			ImGui::PopID();
			ImGui::NextColumn();

			auto& matSkybox = gm.skybox_->getComponent<ST::RenderComponent>()->material;

			for (const auto& tex : cubeMaps) {
				ImGui::PushID(tex.first.c_str());

				bool colorChanged = false;

				if (matSkybox.haveAlbedo && tex.second->getID() == matSkybox.getAlbedo()->getID()) {
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0, 1.0, 1.0, 1.0));
					colorChanged = true;
				}

				if (ImGui::ImageButton(0, ImVec2(thumbnailSize, thumbnailSize))) {

					//materialToChangeTexture->setTexture_Albedo(tex.second.get());
					gm.setSkyboxTexture(getCubeMap(tex.first.c_str()));

					ImGui::CloseCurrentPopup();
					closeCubeMapSelector();
				}

				if (colorChanged)
					ImGui::PopStyleColor(1);

				ImGui::Text(tex.first.c_str());

				ImGui::PopID();
				ImGui::NextColumn();
			}
			
			if (removeTexture) {
				//materialToChangeTexture->removeAlbedo();

				gm.setSkyboxTexture(nullptr);

				ImGui::CloseCurrentPopup();
				closeCubeMapSelector();
			}

			ImGui::EndPopup();
		}
	}
}

void ST::SytemAssets::saveMesh(std::string path){
	std::shared_ptr<ST::Geometry> thisMesh = std::make_shared<ST::Geometry>();
	thisMesh->setName((char*)toLower(getFileName(path, false)).c_str());
	thisMesh->loadFromFile(path.data());
	meshes[toLower(getFileName(path, false))] = thisMesh;
}

ST::Mesh* ST::SytemAssets::getMesh(std::string name){
	//return meshes[toLower(name)].get();
	auto& iter = meshes.find(toLower(name));
	if (iter != meshes.end()) {
		return iter->second.get();
	}
	return nullptr;
}

void ST::SytemAssets::openMeshSelector(ST::RenderComponent& render) {
	itsMeshSelectorOpened = true;
	renderToChangeMesh = &render;
}

void ST::SytemAssets::closeMeshSelector() {
	itsMeshSelectorOpened = false;
	renderToChangeMesh = nullptr;
}

void ST::SytemAssets::popUpMeshSelector() {

	if (itsMeshSelectorOpened) {

		ImGui::OpenPopup("MeshSelectorPopUp");

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove
									| ImGuiWindowFlags_NoResize
									| ImGuiWindowFlags_NoCollapse
									| ImGuiWindowFlags_NoTitleBar
									| ImGuiWindowFlags_NoDocking;

		ImVec2 windowSize = { ImGui::GetMainViewport()->Size.x * 0.8f, ImGui::GetMainViewport()->Size.y * 0.8f };
		ImVec2 center = ImGui::GetMainViewport()->GetCenter();
		ImGui::SetNextWindowSize({ windowSize }, ImGuiCond_Appearing);

		if (ImGui::BeginPopupModal("MeshSelectorPopUp", NULL, window_flags)) {

			ImVec2 getwindowSize = { ImGui::GetWindowSize().x, ImGui::GetWindowSize().y };

			ImGui::SetWindowPos({ center.x - getwindowSize.x * 0.5f, center.y - getwindowSize.y * 0.5f });

			float padding = 10.0f;
			float thumbnailSize = 128.0f;
			float cellSize = thumbnailSize + padding * 2.0f;

			TextCentered("MESH SELECTOR");

			ImVec2 panel_size = ImGui::GetContentRegionAvail();
			int columnCount = (int)(panel_size.x / cellSize);
			if (columnCount <= 0) { columnCount = 1; }
			ImGui::Columns(columnCount, 0, false);

			// ---- None Case -----
			ImGui::PushID("Internal_None_Mesh");
			if (ImGui::ImageButton(0, ImVec2(thumbnailSize, thumbnailSize))) {		
				renderToChangeMesh->setMesh(nullptr);
				ImGui::CloseCurrentPopup();
				closeMeshSelector();
			}
			ImGui::Text("None");
			ImGui::PopID();
			ImGui::NextColumn();

			for (const auto& mes : meshes) {
				ImGui::PushID(mes.first.c_str());
				if (ImGui::ImageButton(0, ImVec2(thumbnailSize, thumbnailSize))) {
					renderToChangeMesh->setMesh(mes.second.get());
					closeMeshSelector();
					ImGui::CloseCurrentPopup();
				}
				// Añade texto debajo del botón
				ImGui::Text(mes.first.c_str());

				ImGui::PopID();
				ImGui::NextColumn();
			}

			ImGui::EndPopup();
		}
	}
}

ST::SytemAssets::~SytemAssets(){

}
