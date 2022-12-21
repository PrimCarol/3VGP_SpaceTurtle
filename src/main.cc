#include <stdio.h>
#include <stdlib.h>

#include <imgui.h>

#include <st_engine.h>

#include <systems/st_system_render.h>

#define ACTUAL_OBJECTS 5000

int main() {
	ST::Window w;
	w.ColorBg(0.2f, 0.2f, 0.2f);

	srand((unsigned int)time(0));
	// ----------------------------------------------------------------
	
	// ************** Temporal ****************
	bool firtsMouse = true; 
	float lastX = 0.0f;
	float lastY = 0.0f;

	ST::GameObj* objSelected = nullptr;
	// ************** Temporal ****************

	ST::GameObj_Manager gm;

	ST::Triangle triangle;
	ST::Quad quad;
	ST::Circle circle;
	ST::Cube cube;

	ST::Texture textureCat;
	textureCat.loadSource("../others/Cat_diffuse.jpg");

	ST::Texture textureChecker;
	textureChecker.loadSource("../others/checker_texture.jpg");

	ST::Texture textureTurtle;
	textureTurtle.loadSource("../others/icon.png");
	
	// *************************** Test ***********************
	ST::Geometry cat;
	cat.loadFromFile("../others/cat_petit.obj");
	ST::Geometry sanic;
	sanic.loadFromFile("../others/skull_petit.obj");
	// *************************** Test ***********************

	const int numObjs = ACTUAL_OBJECTS;

	std::unique_ptr<ST::GameObj> obj1[numObjs];

	auto customProgram = std::make_shared<ST::Program>();
	if (!customProgram->setUp("../shaders/basicShader.vert", "../shaders/basicShader.frag")) {
		printf("Error Program Loading...\n");
	}

	for (size_t i = 0; i < numObjs; i++){
		std::vector<ST::ComponentId> c1;
		c1.push_back(gm.createTransformComponent());
		c1.push_back(gm.createRenderComponent());
		c1.push_back(gm.createColliderComponent());

		obj1[i] = gm.createGameObj(c1);
		ST::TransformComponent* t = (ST::TransformComponent*)obj1[i]->getComponent(ST::kComp_Trans);
		if (t) {
			//float randomScale = ST::Engine::getRandom(0.f, 1.0f);
			//t->setScale(glm::vec3(randomScale, randomScale, randomScale));
		
			float randomPosX = ST::Engine::getRandom(-70.0f, 70.0f);
			float randomPosY = ST::Engine::getRandom(-70.0f, 70.0f);
			float randomPosZ = ST::Engine::getRandom(30.0f, 150.0f);
			t->setPosition(glm::vec3(randomPosX, randomPosY, randomPosZ));
		
		
			float randomRotX = ST::Engine::getRandom(-3.14f, 3.14f);
			t->RotateX(randomRotX);
			float randomRotY = ST::Engine::getRandom(-3.14f, 3.14f);
			t->RotateY(randomRotY);
			float randomRotZ = ST::Engine::getRandom(-3.14f, 3.14f);
			t->RotateZ(randomRotZ);
		
			//float randomVelY = getRandom(0.1f, 0.7f);
			//t->setVelocity(glm::vec3(0.0f, -randomVelY, 0.0f));
		}

		ST::RenderComponent* r = (ST::RenderComponent*)obj1[i]->getComponent(ST::kComp_Render);
		if (r) {

			int randomGeometry = rand() % 6;
			switch (randomGeometry){
			case 0:
				
				r->setMesh(&triangle);

				if ((rand() % 2) == 0) {
					r->material->setTexture_Albedo(&textureTurtle);
				}
				else
				{
					float randomR = ST::Engine::getRandom(0.0f, 1.0f);
					float randomG = ST::Engine::getRandom(0.0f, 1.0f);
					float randomB = ST::Engine::getRandom(0.0f, 1.0f);
					r->material->setColor(glm::vec3(randomR, randomG, randomB));
				}
				break;
			case 1:

				r->setMesh(&quad);

				if ((rand() % 2) == 0) {
					r->material->setTexture_Albedo(&textureTurtle);
				}
				else
				{
					float randomR = ST::Engine::getRandom(0.0f, 1.0f);
					float randomG = ST::Engine::getRandom(0.0f, 1.0f);
					float randomB = ST::Engine::getRandom(0.0f, 1.0f);
					r->material->setColor(glm::vec3(randomR, randomG, randomB));
				}
				break;
			case 2:

				r->setMesh(&circle);

				if ((rand() % 2) == 0) {
					r->material->setTexture_Albedo(&textureTurtle);
				}
				else
				{
					float randomR = ST::Engine::getRandom(0.0f, 1.0f);
					float randomG = ST::Engine::getRandom(0.0f, 1.0f);
					float randomB = ST::Engine::getRandom(0.0f, 1.0f);
					r->material->setColor(glm::vec3(randomR, randomG, randomB));
				}
				break;
			case 3:

				r->setMesh(&cube);

				if ((rand() % 2) == 0) {
					r->material->setTexture_Albedo(&textureTurtle);
				}
				else
				{
					float randomR = ST::Engine::getRandom(0.0f, 1.0f);
					float randomG = ST::Engine::getRandom(0.0f, 1.0f);
					float randomB = ST::Engine::getRandom(0.0f, 1.0f);
					r->material->setColor(glm::vec3(randomR, randomG, randomB));
				}
				break;
			case 4:
				r->setMesh(&cat);
				r->material->setTexture_Albedo(&textureCat);
				r->material->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
				break;
			case 5:
				r->setMesh(&sanic);
				r->material->setTexture_Albedo(&textureChecker);
				r->material->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
				break;
			}

			int randomProgram = rand()%2;
			if (randomProgram == 0) {
				r->material->setProgram(customProgram);
			}
		}
	}

	// --------------------------

	float timerForInput = 0.0f;
	float timerForSomething = 0.0f;
	while (w.isOpen() && !w.inputPressed(ST::ST_INPUT_ESCAPE)) {
		
		w.Clear();

		// ----------------------------------------------------------------
		timerForInput += w.DeltaTime();
		if (timerForInput >= 1.0f/60) {

			glm::vec2 mousePos = {w.mousePosX(), w.mousePosY()};

			float extra_speed = 1.0f;
			if (w.inputPressed(ST::ST_INPUT_SHIFT)) {
				extra_speed = 5.0f;
			}

			if (w.inputPressed(ST::ST_INPUT_UP)) {
				gm.cam_->transform_.Move(gm.cam_->transform_.getForward() * (30.0f * extra_speed * w.DeltaTime()));
			}
			if (w.inputPressed(ST::ST_INPUT_DOWN)) {
				gm.cam_->transform_.Move(-gm.cam_->transform_.getForward() * (30.0f * extra_speed * w.DeltaTime()));
			}
			if (w.inputPressed(ST::ST_INPUT_LEFT) ){
				gm.cam_->transform_.Move(-gm.cam_->transform_.getRight() * (-30.0f * extra_speed * w.DeltaTime()));
			}
			if (w.inputPressed(ST::ST_INPUT_RIGHT)) {
				gm.cam_->transform_.Move(gm.cam_->transform_.getRight() * (-30.0f * extra_speed * w.DeltaTime()));
			}
		
			if (firtsMouse) {
				lastX = mousePos.x;
				lastY = mousePos.y;
				firtsMouse = false;
			}

			float yoffset = mousePos.x - lastX;
			float xoffset = mousePos.y - lastY;
			lastX = mousePos.x;
			lastY = mousePos.y;

			if (w.inputPressed(ST::ST_INPUT_FIRE_SECOND)) {
				gm.cam_->transform_.RotateX(gm.cam_->transform_.getRotation().x + -xoffset * 0.5f * w.DeltaTime());
				gm.cam_->transform_.RotateY(gm.cam_->transform_.getRotation().y +  yoffset * 0.5f * w.DeltaTime());
			}
			
			
			// ---- Picking ---
			if (w.inputPressed(ST::ST_INPUT_FIRE)) {
				objSelected = gm.tryPickObj();
			}

			timerForInput = 0.0f;
		} // End Input Tick

		gm.UpdateTransforms();
		//gm.UpdateRender();

		ST::SystemRender::Render(gm.cam_.get(), gm.renderComponentList_, gm.transformComponentList_);

		//timerForSomething += w.DeltaTime();
		//if (timerForSomething >= 1.0f/10) {
		//	//printf("Something\n");
		//
		//
		//	timerForSomething = 0.0f;
		//}


		// ---------------------------- ImGui -------------------------------
		// --------------------- NavBar ---------------------
		ImGui::BeginMainMenuBar();
		ImGui::PushStyleColor(ImGuiCol_Text, { 1.0f, 0.8f, 0.9f, 1.0f });
		ImGui::Text("| Space Turtle | by: Pere Prim / ESAT");
		ImGui::PopStyleColor();
		ImGui::SameLine(525);
		if (w.FPS(w.DeltaTime()) >= 50) {
			ImGui::PushStyleColor(ImGuiCol_Text, { 0, 1, 0, 1 });
		}else if (w.FPS(w.DeltaTime()) < 50 && w.FPS(w.DeltaTime()) >= 30) {
			ImGui::PushStyleColor(ImGuiCol_Text, { 1, 0.5f, 0, 1 });
		}else {
			ImGui::PushStyleColor(ImGuiCol_Text, { 1, 0, 0, 1 });
		}
		ImGui::Text("%d", (int)w.FPS(w.DeltaTime()));
		ImGui::PopStyleColor();
		ImGui::EndMainMenuBar();

		// --------------------- General ---------------------
		ImGui::Begin("Info");
		ImGui::Text("GameObjects: %d", gm.getGameObjNum() );
		ImGui::End();

		// --------------------- Inspector ---------------------
		ImGui::Begin("Object Seleected");
		if (objSelected) {
			ImGui::Text("Obj ID -> %d ", objSelected->getID());
			ST::TransformComponent* trans = (ST::TransformComponent*)objSelected->getComponent(ST::kComp_Trans);
			if (trans) {
				ImGui::Text("---- Transform ----");
				// Position
				glm::vec3 pos = trans->getPosition();
				ImGui::DragFloat3("##Pos", &pos.x, 0.5f);
				trans->setPosition(pos);
				// Rotation
				glm::vec3 rot = trans->getRotation();
				ImGui::DragFloat3("##Rot", &rot.x, 0.05f);
				trans->RotateX(rot.x);
				trans->RotateY(rot.y);
				trans->RotateZ(rot.z);
				// Scale
				glm::vec3 sca = trans->scale_;
				ImGui::DragFloat3("##Scale", &sca.x, 0.5f);
				trans->setScale(sca);
			}

			ST::RenderComponent* render = (ST::RenderComponent*)objSelected->getComponent(ST::kComp_Render);
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

				if (ImGui::TreeNode("Change Mesh")) {
					if (ImGui::Button("Change Mesh to -> Triangle")) {
						render->setMesh(&triangle);
					}
					if (ImGui::Button("Change Mesh to -> Quad")) {
						render->setMesh(&quad);
					}
					if (ImGui::Button("Change Mesh to -> Circle")) {
						render->setMesh(&circle);
					}
					if (ImGui::Button("Change Mesh to -> Cube")) {
						render->setMesh(&cube);
					}
					if (ImGui::Button("Change Mesh to -> Cat")) {
						render->setMesh(&cat);
					}
					if (ImGui::Button("Change Mesh to -> Skull")) {
						render->setMesh(&sanic);
					}
					ImGui::TreePop();
				}
			}
		}
		ImGui::End();

		// ----------------------------

		w.Render();	

	}

	return 0;
}