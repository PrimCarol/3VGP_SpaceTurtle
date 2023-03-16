#include <st_engine.h>

#include <imgui.h>
#include <st_shader.h>

int main() {
	ST::Window w(1600, 840);
	w.ColorBg(0.2f, 0.2f, 0.2f); // Optional

	// ----------------------------------------------------------------

	ST::GameObj_Manager gm;

	ST::GameObj camera = gm.createGameObj(ST::TransformComponent{}, ST::CameraComponent{});
	camera.getComponent<ST::NameComponent>()->setName("Camera 01");
	camera.getComponent<ST::TransformComponent>()->setPosition(0.0f, 10.0f, 0.0f);
	camera.getComponent<ST::TransformComponent>()->setRotateX(-1.58f);

	ST::GameObj camera2 = gm.createGameObj(ST::TransformComponent{}, ST::CameraComponent{});
	camera2.getComponent<ST::NameComponent>()->setName("Camera 02");
	camera2.getComponent<ST::TransformComponent>()->setPosition(0.0f, 0.0f, -5.0f);

	// --------------
	ST::Texture textureTest;
	//textureTest.generateMipmap = true;
	//textureTest.set_mag_filter(ST::Texture::F_NEAREST);
	//textureTest.set_min_filter(ST::Texture::F_LINEAR);
	textureTest.loadSource("../others/icon.png");
	//textureTest.setCols(71);
	//textureTest.setRows(19);

	ST::Cube test_mesh;
	ST::Quad quad_mesh;
	//test_mesh.loadFromFile("../others/cat_petit.obj");
	
	//int HOWMANY = 10000;

	//std::vector<ST::GameObj> objects;
	//for (int i = 0; i < HOWMANY; i++){
	//	objects.push_back(gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{}));
	//	objects.back().getComponent<ST::RenderComponent>()->setMesh(&quad_mesh);
	//	objects.back().getComponent<ST::ColliderComponent>()->setMaxPoint(objects.back().getComponent<ST::RenderComponent>()->mesh->getMaxPoint());
	//	objects.back().getComponent<ST::ColliderComponent>()->setMinPoint(objects.back().getComponent<ST::RenderComponent>()->mesh->getMinPoint());
	//	//objects.back().getComponent<ST::RenderComponent>()->material.translucent = true;
	//	objects.back().getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&textureTest);
	//	//objects.back().getComponent<ST::RenderComponent>()->material.setTexIndex({ 9,15 });
	//	objects.back().getComponent<ST::RenderComponent>()->material.setTexIndex({ST::Engine::getRandom(0.0f,71.0f),ST::Engine::getRandom(0.0f,19.0f) });
	//	//objects.back().getComponent<ST::RenderComponent>()->material.setColor(ST::Engine::getRandom(0.0f,1.0f),ST::Engine::getRandom(0.0f,1.0f), ST::Engine::getRandom(0.0f, 1.0f), 0.5f);
	//	//objects.back().getComponent<ST::RenderComponent>()->material.shininess = ST::Engine::getRandom(1.0f, 999.0f);
	//	objects.back().getComponent<ST::RenderComponent>()->material.setProgram(gm.basicProgram);
	//	objects.back().getComponent<ST::TransformComponent>()->setPosition(glm::vec3(ST::Engine::getRandom(-300.0f,300.0f), ST::Engine::getRandom(-300.0f, 300.0f), ST::Engine::getRandom(0.0f, 600.0f)));
	//	objects.back().getComponent<ST::TransformComponent>()->setScale(0.5f, 0.5f, 1.0f);
	//	
	//}

	ST::GameObj ground = gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{});
	ground.getComponent<ST::NameComponent>()->setName("Ground");
	ground.getComponent<ST::TransformComponent>()->setScale({ 10.0f,0.2f,10.0f });
	ground.getComponent<ST::TransformComponent>()->setPosition({0.0f,-5.0f,0.0f});
	ground.getComponent<ST::RenderComponent>()->material.setProgram(gm.basicProgram);
	ground.getComponent<ST::RenderComponent>()->setMesh(&test_mesh);
	ST::GameObj testObj = gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{});
	testObj.getComponent<ST::NameComponent>()->setName("testObj");
	testObj.getComponent<ST::RenderComponent>()->material.setProgram(gm.basicProgram);
	testObj.getComponent<ST::RenderComponent>()->setMesh(&test_mesh);
	testObj.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&textureTest);
	ST::GameObj DirLight = gm.createGameObj(ST::TransformComponent{}, ST::LightComponent{});
	DirLight.getComponent<ST::NameComponent>()->setName("DirLight");
	DirLight.getComponent<ST::TransformComponent>()->setPosition(0.0f,5.0f,0.0f);
	DirLight.getComponent<ST::TransformComponent>()->setRotateY(1.63f);
	//DirLight.getComponent<ST::TransformComponent>()->setRotateZ(0.5f);
	DirLight.getComponent<ST::LightComponent>()->type_ = ST::Directional;
	DirLight.getComponent<ST::LightComponent>()->ambient_ = glm::vec3(0.4f);
	DirLight.getComponent<ST::LightComponent>()->diffuse_ = glm::vec3(0.4f);
	DirLight.getComponent<ST::LightComponent>()->specular_ = glm::vec3(0.4f);


	ST::GameObj ShadowMap = gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{});
	ShadowMap.getComponent<ST::NameComponent>()->setName("ShadowMap");
	ShadowMap.getComponent<ST::TransformComponent>()->setScale({ 10.0f,10.0f,1.0f });
	ShadowMap.getComponent<ST::TransformComponent>()->setPosition({ 0.0f,5.0f,10.0f });
	ShadowMap.getComponent<ST::RenderComponent>()->material.setProgram(gm.unliteProgram);
	ShadowMap.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&gm.shadowMap.textureToRender_);
	ShadowMap.getComponent<ST::RenderComponent>()->setMesh(&quad_mesh);


	// --------------------------
	// **************** TEST *****************
	//ST::RenderTarget renderTargetTest;
	//renderTargetTest.setUp(w.getWindowsWidth(), w.getWindowsHeight()/*, ST::Texture::F_DEPTH*/);

	/*ST::GameObj quadTarget = gm.createGameObj(ST::TransformComponent{},ST::RenderComponent{});
	quadTarget.getComponent<ST::NameComponent>()->setName("Pantalla");
	quadTarget.getComponent<ST::TransformComponent>()->setScale(10.0f, 10.0f, 1.0f);
	quadTarget.getComponent<ST::TransformComponent>()->setPosition(0.0f, 5.0f, 10.0f);
	quadTarget.getComponent<ST::TransformComponent>()->setRotateZ(3.14f);
	quadTarget.getComponent<ST::RenderComponent>()->setMesh(&quad_mesh);
	quadTarget.getComponent<ST::RenderComponent>()->material.setProgram(gm.unliteProgram);
	quadTarget.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&renderTargetTest.textureToRender_);*/

	// **************** TEST *****************

	while (w.isOpen() && !w.inputPressed(ST::ST_INPUT_ESCAPE)) {
		w.Clear();

		// ---- Camera ----
		ST::SystemCamera::Movemment(gm, w);
		ST::SystemCamera::UpdateCamera(gm);

		ST::SystemTransform::UpdateTransforms(gm);
		ST::SystemLight::CompileLights(gm, *gm.basicProgram);
		ST::SystemLight::CompileShadows(gm); // <---- Testing
		
		//renderTargetTest.start();
		//ST::SystemRender::Render(gm);
		//renderTargetTest.end();
		
		ST::SystemRender::Render(gm);


		//ImGui::Begin("View", 0, ImGuiWindowFlags_NoInputs);
		//ImGui::Image((void*)(intptr_t)renderTargetTest.textureID(), ImGui::GetWindowSize());
		//ImGui::End();

		if (w.inputPressed(ST::ST_INPUT_FIRE)) {
			gm.objectSelected = ST::SystemPicking::tryPickObj(w, gm);
		}
		if (w.inputPressed(ST::ST_INPUT_DELETE) && gm.objectSelected != -1) {
			gm.deleteGameObj(gm.objectSelected);
			gm.objectSelected = -1;
		}

		ST::SystemHUD::NavBar(gm);
		ST::SystemHUD::Hierarchy(gm);
		ST::SystemHUD::Inspector(gm);
		ST::SystemHUD::Stats(w, gm);

		// ----------------------------

		w.Render();
	}
	return 0;
}