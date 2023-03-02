#include "st_system_hud.h"

#include <imgui.h>

#include <st_engine.h>

#include <components/st_render.h>
#include <components/st_name.h>
#include <components/st_light.h>
#include <components/st_hierarchy.h>
#include <st_gameobj_manager.h>
#include <st_gameobj.h>

void ST::SystemHUD::NavBar(ST::GameObj_Manager& gm){
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("Edit")) {
		if (ImGui::BeginMenu("Create...")) {
			// Empty
			if (ImGui::MenuItem("Empty")) {
				ST::Engine::createEmptyObj(gm);
			}

			// Geometrys
			if (ImGui::BeginMenu("Geometry...")) {
				if (ImGui::MenuItem("Triangle", NULL, false)) {
					ST::Engine::createTriangle(gm);
				}
				if (ImGui::MenuItem("Quad", NULL, false)) {
					ST::Engine::createQuad(gm);
				}
				if (ImGui::MenuItem("Circle", NULL, false)) {
					ST::Engine::createCircle(gm);
				}
				if (ImGui::MenuItem("Cube", NULL, false)) {
					ST::Engine::createCube(gm);
				}
				ImGui::EndMenu();
			}

			//Lights
			if (ImGui::BeginMenu("Lights...")) {
				if (ImGui::MenuItem("Directional Light", NULL, false)) {
					ST::Engine::createDirectLight(gm);
				}
				if (ImGui::MenuItem("Point Light", NULL, false)) {
					ST::Engine::createPointLight(gm);
				}
				if (ImGui::MenuItem("Spot Light", NULL, false)) {
					ST::Engine::createSpotLight(gm);
				}
				ImGui::EndMenu();
			}

			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();
}

void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 0.0f){
	ImGuiIO& io = ImGui::GetIO();
	auto boldFont = io.Fonts->Fonts[0];

	ImGui::PushID(label.c_str());

	float cells_size = 60.0f;
	float button_size = 20.0f;
	
	ImGui::PushItemWidth(cells_size); // Tamaño de las casillas
	
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
	
	float lineHeight = button_size; // Tamaño del boton
	ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
	ImGui::PushFont(boldFont);
	if (ImGui::Button("X", buttonSize))
		values.x = resetValue;
	ImGui::PopFont();
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
	//ImGui::PopItemWidth();
	ImGui::SameLine(buttonSize.x + cells_size + 35.0f);

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
	ImGui::PushFont(boldFont);
	if (ImGui::Button("Y", buttonSize))
		values.y = resetValue;
	ImGui::PopFont();
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
	//ImGui::PopItemWidth();
	ImGui::SameLine((buttonSize.x + cells_size) * 2 + 40.0f);

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
	ImGui::PushFont(boldFont);
	if (ImGui::Button("Z", buttonSize))
		values.z = resetValue;
	ImGui::PopFont();
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();

	ImGui::PopStyleVar();

	//ImGui::Columns(1);

	ImGui::PopID();
}

const char* lightEnumToString(ST::LightType t) {
	switch (t){
	case ST::Directional:
		return "Directional";
		break;
	case ST::Point:
		return "Point";
		break;
	case ST::Spot:
		return "Spot";
		break;
	default:
		return "None";
		break;
	}
}

ST::LightType lightStringToEnum(const char* c) {
	if (c == "Directional") {
		return ST::Directional;
	}
	if (c == "Point") {
		return ST::Point;
	}
	if (c == "Spot") {
		return ST::Spot;
	}
}

#include <imgui_internal.h>
#include <ImGuizmo.h>

void ST::SystemHUD::Inspector(ST::GameObj_Manager& gm){

	size_t objSeletected = gm.objectSelected;

	// ImGuizmo <----------------------------------------
	static ImGuizmo::OPERATION GuizmoOperation(ImGuizmo::TRANSLATE);
	static ImGuizmo::MODE GuizmoMode(ImGuizmo::WORLD);

	ImGui::Begin("ControllersTransform");
	ImVec2 sizeButton(30, 30);
	if (ImGui::Button("T", sizeButton)) {
		GuizmoOperation = ImGuizmo::TRANSLATE;
	} ImGui::SameLine();
	if (ImGui::Button("R", sizeButton)) {
		GuizmoOperation = ImGuizmo::ROTATE;
	} ImGui::SameLine();
	if (ImGui::Button("S", sizeButton)) {
		GuizmoOperation = ImGuizmo::SCALE;
	}
	if (GuizmoOperation != ImGuizmo::SCALE) {
		if (ImGui::RadioButton("Local", GuizmoMode == ImGuizmo::LOCAL)) {
			GuizmoMode = ImGuizmo::LOCAL;
		} ImGui::SameLine();
		if (ImGui::RadioButton("World", GuizmoMode == ImGuizmo::WORLD)) {
			GuizmoMode = ImGuizmo::WORLD;
		}
	}
	ImGui::End();
	// ImGuizmo <----------------------------------------

	ImGui::Begin("Inspector");
	if (objSeletected >= 0 && objSeletected < gm.size() ) {
		ImGui::Text("Obj ID -> %d ", objSeletected);
	
		if (gm.getComponentVector<ST::TransformComponent>()->at(objSeletected).has_value()) {
			ImGui::Spacing(); ImGui::Spacing();
			ST::TransformComponent* trans = &gm.getComponentVector<ST::TransformComponent>()->at(objSeletected).value();
			if (ImGui::TreeNodeEx("Transform")) {
					
				// Position
				glm::vec3 pos = trans->getPosition();
				//ImGui::DragFloat3("##Pos", &pos.x, 0.5f);
				DrawVec3Control("Pos", pos);
				trans->setPosition(pos);
				// Rotation
				glm::vec3 rot = trans->getRotation();
				//ImGui::DragFloat3("##Rot", &rot.x, 0.05f);
				DrawVec3Control("Rot", rot);
				trans->setRotateX(rot.x);
				trans->setRotateY(rot.y);
				trans->setRotateZ(rot.z);
				// Scale
				glm::vec3 sca = trans->getScale();
				//ImGui::DragFloat3("##Scale", &sca.x, 0.5f);
				DrawVec3Control("Sca", sca, 1.0f);
				trans->setScale(sca);

				ImGui::TreePop();
			}

			// ---- Guizmos ----
			if (gm.mainCameraID() != -1) {
				ImGuizmo::BeginFrame();
				const ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGuiIO& io = ImGui::GetIO();
				ImGuizmo::SetRect(viewport->Pos.x, viewport->Pos.y, viewport->Size.x, viewport->Size.y);
				
				float tempMatrixGuizmo[16];
				glm::vec3 pos = trans->getPosition();
				glm::vec3 rot = trans->getRotation();
				glm::vec3 sca = trans->getScale();

				if (gm.getComponentVector<ST::CameraComponent>()->at(gm.mainCameraID()).has_value()) {
					ST::CameraComponent* tempCam = &gm.getComponentVector<ST::CameraComponent>()->at(gm.mainCameraID()).value();
					if (tempCam) {
						ImGuizmo::RecomposeMatrixFromComponents(&pos.x, &rot.x, &sca.x, tempMatrixGuizmo);
						ImGuizmo::Manipulate((const float*)&tempCam->view, (const float*)&tempCam->projection,
							GuizmoOperation, GuizmoMode, tempMatrixGuizmo);
						ImGuizmo::DecomposeMatrixToComponents(tempMatrixGuizmo, &pos.x, &rot.x, &sca.x);
					}
				}
				trans->setPosition(pos);
				trans->setRotateX(rot.x);
				trans->setRotateY(rot.y);
				trans->setRotateZ(rot.z);
				trans->setScale(sca);
			}
			// --------
		}
			
		

		if (gm.getComponentVector<ST::RenderComponent>()->at(objSeletected).has_value()) {
			ImGui::Spacing(); ImGui::Spacing();
			if (ImGui::TreeNodeEx("Render")) {

				ST::RenderComponent* render = &gm.getComponentVector<ST::RenderComponent>()->at(objSeletected).value();

				ImGui::Checkbox("Visible", &render->visible_);
				ImGui::Checkbox("Translucent", &render->material.translucent);
				ImGui::Spacing();
				ImGui::Text("- Color -");
				glm::vec4 c = render->material.getColor();
				if (render->material.translucent) {
					ImGui::ColorEdit4("Color", &c.x);
				}
				else {
					ImGui::ColorEdit3("Color", &c.x);
				}
				render->material.setColor(c);
				ImGui::DragFloat("Shiness", &render->material.shininess, 1.0f, 1.0f);
				ImGui::Text("- Texture -");
				if (render->material.haveAlbedo) {
					ImGui::Image((void*)(intptr_t)render->material.getAlbedo()->getID(), ImVec2(144, 144));
				}
				else {
					ImGui::Text("Albedo: None");
				}
				if (render->material.haveNormal) {
					ImGui::Image((void*)(intptr_t)render->material.getNormal()->getID(), ImVec2(144, 144));
				}
				else {
					ImGui::Text("Normal: None");
				}
				if (render->material.haveSpecular) {
					ImGui::Image((void*)(intptr_t)render->material.getSpecular()->getID(), ImVec2(144, 144));
				}
				else {
					ImGui::Text("Specular: None");
				}

				glm::ivec2 textIndex = render->material.getTexIndex();
				ImGui::SetNextItemWidth(50);
				ImGui::InputInt2("TextIndex", &textIndex.x);
				render->material.setTexIndex(textIndex);

				ImGui::Text("---- Mesh ----");
				ImGui::Text("Mesh: ");
				ImGui::SameLine();
				if (render->mesh) {
					ImGui::Text(render->mesh->getName());
				}
				else {
					ImGui::Text("None");
				}

				// ---------- Remove Button ----------
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.0f, 0.0f, 1.0f));
				if (ImGui::Button("Remove", ImVec2(60.0f, 0.0f))) {
					gm.removeComponent<ST::RenderComponent>(objSeletected);
				}
				ImGui::PopStyleColor();

				ImGui::TreePop();
			}
		}
		//else {
		//	if (ImGui::Button("Add Render Component")) {
		//		gm.addComponent<ST::RenderComponent>(objSeletected);
		//		//gm.getComponent<ST::RenderComponent>(objSeletected)->material.setProgram(gm.basicProgram);
		//	}
		//}

		if (gm.getComponentVector<ST::ColliderComponent>()->at(objSeletected).has_value()) {
			ImGui::Spacing(); ImGui::Spacing();
			if (ImGui::TreeNodeEx("Collider")) {
				ST::ColliderComponent* collider = &gm.getComponentVector<ST::ColliderComponent>()->at(objSeletected).value();

				ImGui::Checkbox("Active", &collider->active_);

				glm::vec3 min = collider->getMinPoint();
				ImGui::InputFloat3("MinPoint", &min.x);
				collider->setMinPoint(min);

				glm::vec3 max = collider->getMaxPoint();
				ImGui::InputFloat3("MaxPoint", &max.x);
				collider->setMaxPoint(max);

				//collider->draw(); // <<----- ????
				ImGui::TreePop();
			}
		}

		const char* typeLightsChar[] = { "Directional", "Point", "Spot"};
		const char* typeLightSelected = NULL;

		if (gm.getComponentVector<ST::LightComponent>()->at(objSeletected).has_value()) {
			ImGui::Spacing(); ImGui::Spacing();
			if (ImGui::TreeNodeEx("Light")) {

				ST::LightComponent* light = &gm.getComponentVector<ST::LightComponent>()->at(objSeletected).value();

				// ---------- Selector de Typo de luz ----------
				typeLightSelected = lightEnumToString(light->type_);
				ImGui::SetNextItemWidth(120);
				if (ImGui::BeginCombo("##combo", typeLightSelected)){
					for (int n = 0; n < IM_ARRAYSIZE(typeLightsChar); n++){
						bool is_selected = (typeLightSelected == typeLightsChar[n]);
						if (ImGui::Selectable(typeLightsChar[n], is_selected)){
							typeLightSelected = typeLightsChar[n];
							light->type_ = lightStringToEnum(typeLightSelected);
						}
						if (is_selected) {
							ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndCombo();
				}
				

				ImGui::Spacing(); ImGui::Spacing();

				switch (light->type_){
				case ST::Directional:
					ImGui::ColorPicker3("Ambient", &light->ambient_.x);
					ImGui::ColorEdit3("Diffuse", &light->diffuse_.x);
					ImGui::ColorEdit3("Specular", &light->specular_.x);
					break;
				case ST::Point:
					ImGui::ColorPicker3("Color", &light->color_.x);

					ImGui::Spacing();
					ImGui::SetNextItemWidth(70);
					ImGui::DragFloat("Constant", &light->constant_, 0.01f, 0.001f, 5.00f, "%.3f");
					ImGui::SetNextItemWidth(70);
					ImGui::DragFloat("Linear", &light->linear_, 0.01f, 0.001f, 10.00f, "%.3f");
					ImGui::SetNextItemWidth(70);
					ImGui::DragFloat("Quadratic", &light->quadratic_, 0.001f, 0.0001f, 0.01f, "%.4f");
					break;
				case ST::Spot:
					ImGui::ColorPicker3("Color", &light->color_.x);

					ImGui::Spacing();

					ImGui::SetNextItemWidth(70);
					ImGui::DragFloat("Constant", &light->constant_, 0.01f, 0.001f, 5.00f, "%.3f");
					ImGui::SetNextItemWidth(70);
					ImGui::DragFloat("Linear", &light->linear_, 0.01f, 0.001f, 10.00f, "%.3f");
					ImGui::SetNextItemWidth(70);
					ImGui::DragFloat("Quadratic", &light->quadratic_, 0.001f, 0.0001f, 0.01f, "%.4f");

					ImGui::Spacing();

					ImGui::SetNextItemWidth(70);
					ImGui::DragFloat("Cut Off", &light->cutOff_, 0.01f, light->outerCutOff_ + 0.01f, 0.99f, "%.2f");
					ImGui::SetNextItemWidth(70);
					ImGui::DragFloat("Outer Cut Off", &light->outerCutOff_, 0.01f, 0.0f, light->cutOff_ - 0.01f, "%.2f");
					break;
				}

				ImGui::Spacing(); ImGui::Spacing();

				// ---------- Remove Button ----------
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f,0.0f,0.0f,1.0f));
				if (ImGui::Button("Remove", ImVec2(60.0f, 0.0f) )) {
					gm.removeComponent<ST::LightComponent>(objSeletected);
				}
				ImGui::PopStyleColor();

				ImGui::TreePop();
			}
		}

		ImGui::Spacing(); ImGui::Spacing();
		ImGui::BeginChild("Footer Zone");
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.0f, 0.0f, 1.0f));
		if (ImGui::Button("Delete")) {
			gm.deleteGameObj(gm.objectSelected);
			gm.objectSelected = -1;
		}
		ImGui::PopStyleColor();
		ImGui::EndChild();
	}
	ImGui::End();
}

void ShowChilds(ST::GameObj_Manager& gm, const ST::HierarchyComponent& parent) {
	std::vector<std::optional<ST::NameComponent>>* nameComponents = gm.getComponentVector<ST::NameComponent>();

	char buffer[50];
	for (int i = 0; i < parent.childSize(); i++) {
		if (nameComponents->at(parent.getChildID(i)).has_value()) {
			//snprintf(buffer, 50, "%s %d", nameComponents->at(parent.getChildID(i)).value().getName(), parent.getChildID(i));
			snprintf(buffer, 50, "%s", nameComponents->at(parent.getChildID(i)).value().getName());

			ImGuiTreeNodeFlags node_flags = (gm.objectSelected == parent.getChildID(i) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnDoubleClick;
			bool opened = ImGui::TreeNodeEx(buffer, node_flags);
			if (ImGui::IsItemClicked()) {
				gm.objectSelected = parent.getChildID(i);
			}
		
			if (opened) {
				if (gm.getComponentVector<ST::HierarchyComponent>()->at(parent.getChildID(i)).has_value()) {
					ShowChilds(gm, gm.getComponentVector<ST::HierarchyComponent>()->at(parent.getChildID(i)).value());
				}
				ImGui::TreePop();
			}
		}
	}
}

void ST::SystemHUD::Hierarchy(ST::GameObj_Manager& gm){
	ImGui::Begin("Hierarchy");
		ST::HierarchyComponent* rootHierarchy = gm.root.getComponent<ST::HierarchyComponent>();
		if (rootHierarchy) {
			ShowChilds(gm, *rootHierarchy);
		}
	ImGui::End();
}

void ST::SystemHUD::Stats(const ST::Window& w, const ST::GameObj_Manager& gm){
	ImGui::Begin("Stats");

	ImGui::Text("FPS: "); ImGui::SameLine();
	if (w.FPS(w.DeltaTime()) >= 50) {
		ImGui::PushStyleColor(ImGuiCol_Text, { 0, 1, 0, 1 });
	}else if (w.FPS(w.DeltaTime()) < 50 && w.FPS(w.DeltaTime()) >= 30) {
		ImGui::PushStyleColor(ImGuiCol_Text, { 1, 0.5f, 0, 1 });
	}else {
		ImGui::PushStyleColor(ImGuiCol_Text, { 1, 0, 0, 1 });
	}
	ImGui::Text("%d", (int)w.FPS(w.DeltaTime()));
	ImGui::PopStyleColor();
	
	ImGui::Text("GameObjects: %d", gm.size());

	ImGui::End();
}

//#include <imgui_internal.h>
//#include <ImGuizmo.h>

/*void ST::SystemHUD::EditTransform(const ST::Camera& c, ST::GameObj* objSeletected, bool editTransformDecomposition) {

    //ImGuiIO& io = ImGui::GetIO();
    //float viewManipulateRight = io.DisplaySize.x;
    //float viewManipulateTop = 0;
    //static ImGuiWindowFlags gizmoWindowFlags = 0;

    //if (useWindow)
    //{
    //    ImGui::SetNextWindowSize(ImVec2(800, 400), ImGuiCond_Appearing);
    //    ImGui::SetNextWindowPos(ImVec2(400, 20), ImGuiCond_Appearing);
    //    ImGui::PushStyleColor(ImGuiCol_WindowBg, (ImVec4)ImColor(0.35f, 0.3f, 0.3f));
    //    ImGui::Begin("Gizmo", 0, gizmoWindowFlags);
    //    ImGuizmo::SetDrawlist();
    //    float windowWidth = (float)ImGui::GetWindowWidth();
    //    float windowHeight = (float)ImGui::GetWindowHeight();
    //    ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);
    //    viewManipulateRight = ImGui::GetWindowPos().x + windowWidth;
    //    viewManipulateTop = ImGui::GetWindowPos().y;
    //    ImGuiWindow* window = ImGui::GetCurrentWindow();
    //    gizmoWindowFlags = ImGui::IsWindowHovered() && ImGui::IsMouseHoveringRect(window->InnerRect.Min, window->InnerRect.Max) ? ImGuiWindowFlags_NoMove : 0;
    //}
    //else
    //{
    //    ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
    //}
    //glm::mat4 identityMat(1.0f);
    ////ImGuizmo::DrawGrid((const float*)&c.view, (const float*)&c.projection, (const float*)&identityMat, 100.f);
    //if (objSeletected) {
    //    ImGuizmo::DrawCubes((const float*)&c.view, (const float*)&c.projection, (const float*)&objSeletected->getComponentTransform()->m_transform_[0][0], gizmoCount);
    //    ImGuizmo::Manipulate((const float*)&c.view, (const float*)&c.projection, mCurrentGizmoOperation, mCurrentGizmoMode, (float*)&objSeletected->getComponentTransform()->m_transform_[0][0], NULL, useSnap ? &snap[0] : NULL, boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL);

    //    ImGuizmo::ViewManipulate((float*)&c.view, camDistance, ImVec2(viewManipulateRight - 128, viewManipulateTop), ImVec2(128, 128), 0x10101010);
    //}

    //if (useWindow)
    //{
    //    ImGui::End();
    //    ImGui::PopStyleColor(1);
    //}

    if (objSeletected) {
        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();

        float windowWidth = (float)ImGui::GetWindowWidth();
        float windowHeight = (float)ImGui::GetWindowHeight();

        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

        ImGuizmo::Manipulate((const float*)&c.view, (const float*)&c.projection,
            ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::LOCAL, (float*)&objSeletected->getComponentTransform()->m_transform_[0][0]);
    }
}*/
