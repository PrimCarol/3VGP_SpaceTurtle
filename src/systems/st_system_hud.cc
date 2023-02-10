#include "st_system_hud.h"

#include <imgui.h>

#include <components/st_render.h>
#include <st_gameobj_manager.h>
#include <st_gameobj.h>

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

void ST::SystemHUD::Inspector(ST::GameObj_Manager& gm, const size_t objSeletected){
	ImGui::Begin("Inspector");
	if (objSeletected >= 0 && objSeletected < gm.size() ) {
		ImGui::Text("Obj ID -> %d ", objSeletected);
		ImGui::Spacing(); ImGui::Spacing();
	
		if (gm.getComponentVector<ST::TransformComponent>()->at(objSeletected).has_value()) {
			if (ImGui::TreeNodeEx("Transform")) {
				ST::TransformComponent* trans = &gm.getComponentVector<ST::TransformComponent>()->at(objSeletected).value();
					
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
		}
			
		ImGui::Spacing(); ImGui::Spacing();

		if (gm.getComponentVector<ST::RenderComponent>()->at(objSeletected).has_value()) {
			if (ImGui::TreeNodeEx("Render")) {

				ST::RenderComponent* render = &gm.getComponentVector<ST::RenderComponent>()->at(objSeletected).value();

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
				ImGui::Text("- Texture -");
				if (render->material.haveAlbedo) {
					ImGui::Image((void*)(intptr_t)render->material.getAlbedo()->getID(), ImVec2(144, 144));
				}
				else {
					ImGui::Text("None");
				}
				ImGui::Text("---- Mesh ----");
				ImGui::Text("Mesh: ");
				ImGui::SameLine();
				if (render->mesh) {
					ImGui::Text(render->mesh->getName());
				}
				else {
					ImGui::Text("None");
				}

				if (ImGui::Button("Remove Render Component")) {
					gm.removeComponent<ST::RenderComponent>(objSeletected);
				}

				ImGui::TreePop();
			}
		}
		//else {
		//	if (ImGui::Button("Add Render Component")) {
		//		gm.addComponent<ST::RenderComponent>(objSeletected);
		//		//gm.getComponent<ST::RenderComponent>(objSeletected)->material.setProgram(gm.basicProgram);
		//	}
		//}
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
