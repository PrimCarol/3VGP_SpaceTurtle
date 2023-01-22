#include "st_system_hud.h"

#include <imgui.h>

void ST::SystemHUD::DrawHud(const ST::Window& w, ST::GameObj_Manager& gm, ST::GameObj* objSeletected){
	// ---------------------------- ImGui -------------------------------
	// --------------------- NavBar ---------------------
	ImGui::BeginMainMenuBar();
	ImGui::PushStyleColor(ImGuiCol_Text, { 1.0f, 0.8f, 0.9f, 1.0f });
	ImGui::Text("| Space Turtle | by: Pere Prim / ESAT");
	ImGui::PopStyleColor();
	ImGui::SameLine(525);
	if (w.FPS(w.DeltaTime()) >= 50) {
		ImGui::PushStyleColor(ImGuiCol_Text, { 0, 1, 0, 1 });
	}
	else if (w.FPS(w.DeltaTime()) < 50 && w.FPS(w.DeltaTime()) >= 30) {
		ImGui::PushStyleColor(ImGuiCol_Text, { 1, 0.5f, 0, 1 });
	}
	else {
		ImGui::PushStyleColor(ImGuiCol_Text, { 1, 0, 0, 1 });
	}
	ImGui::Text("%d", (int)w.FPS(w.DeltaTime()));
	ImGui::PopStyleColor();
	ImGui::EndMainMenuBar();

	// --------------------- General ---------------------
	ImGui::Begin("Info");
	ImGui::Text("GameObjects: %d", gm.getGameObjNum());
	ImGui::End();

	// --------------------- Inspector ---------------------
	ImGui::Begin("Object Seleected");
	if (objSeletected) {
		ImGui::Text("Obj ID -> %d ", objSeletected->getID());
		ImGui::Spacing();ImGui::Spacing();

		ST::TransformComponent* trans = objSeletected->getComponentTransform();
		if (trans) {
			ImGui::Text("---- Transform ----");
			// Position
			glm::vec3 pos = trans->getPosition();
			ImGui::DragFloat3("##Pos", &pos.x, 0.5f);
			trans->setPosition(pos);
			// Rotation
			glm::vec3 rot = trans->getRotation();
			ImGui::DragFloat3("##Rot", &rot.x, 0.05f);
			trans->setRotateX(rot.x);
			trans->setRotateY(rot.y);
			trans->setRotateZ(rot.z);
			// Scale
			glm::vec3 sca = trans->getScale();
			ImGui::DragFloat3("##Scale", &sca.x, 0.5f);
			trans->setScale(sca);
		}
		ImGui::Spacing(); ImGui::Spacing();
		ST::RenderComponent* render = objSeletected->getComponentRender();
		if (render) {
			ImGui::Text("---- Render ----");

			ImGui::Text("- Color -");
			glm::vec3 c = render->material->getColor();
			ImGui::ColorEdit3("Color", &c.x);
			render->material->setColor(c);
			ImGui::Text("- Texture -");
			if (render->material->haveAlbedo) {
				ImGui::Image((void*)(intptr_t)render->material->getAlbedo()->getID(), ImVec2(144, 144));
			}
			else {
				ImGui::Text("None");
			}
			ImGui::Text("---- Mesh ----");
			ImGui::Text("Mesh: ");
			ImGui::SameLine();
			ImGui::Text(render->mesh->getName());
		}
	}
	ImGui::End();
}
