#include <st_engine.h>

#include <imgui.h>
#include <st_shader.h>
#include <st_system_assets.h>

int main() {
	ST::Window w(1600, 900);
	w.ColorBg(0.0f, 0.0f, 0.0f); // Optional
	
	// ----------------------------------------------------------------

	ST::GameObj_Manager gm;
	std::shared_ptr<ST::SytemAssets> assets = std::make_shared<ST::SytemAssets>();
	gm.assets_ = assets;

	std::vector<std::string> skyboxCityPaths;
	skyboxCityPaths.push_back("../others/skybox/city/right.jpg");
	skyboxCityPaths.push_back("../others/skybox/city/left.jpg");
	skyboxCityPaths.push_back("../others/skybox/city/top.jpg");
	skyboxCityPaths.push_back("../others/skybox/city/bottom.jpg");
	skyboxCityPaths.push_back("../others/skybox/city/front.jpg");
	skyboxCityPaths.push_back("../others/skybox/city/back.jpg");
	assets->saveTextureCubeMap("Skybox City", skyboxCityPaths);

	std::vector<std::string> skyboxSnowPaths;
	skyboxSnowPaths.push_back("../others/skybox/snow/right.jpg");
	skyboxSnowPaths.push_back("../others/skybox/snow/left.jpg");
	skyboxSnowPaths.push_back("../others/skybox/snow/top.jpg");
	skyboxSnowPaths.push_back("../others/skybox/snow/bottom.jpg");
	skyboxSnowPaths.push_back("../others/skybox/snow/front.jpg");
	skyboxSnowPaths.push_back("../others/skybox/snow/back.jpg");
	assets->saveTextureCubeMap("Skybox Snow", skyboxSnowPaths);

	// --------------
	assets->saveTexture("../others/checker_texture.jpg");
	assets->getTexture("checker_texture.jpg")->setCols(8);
	assets->getTexture("checker_texture.jpg")->setRows(8);

	assets->saveTexture("../others/Cat_diffuse.jpg", true);
	assets->saveTexture("../others/Cat_specular.png", true);

	assets->saveMesh("../others/cat_petit.obj");

	assets->saveMesh("../others/pbr/helmet/helmet.obj");
	assets->saveTexture("../others/pbr/helmet/helmet_basecolor.tga", true);
	assets->saveTexture("../others/pbr/helmet/helmet_roughness.tga", true);
	assets->saveTexture("../others/pbr/helmet/helmet_metalness.tga", true);

	assets->saveTexture("../others/pbr/basecolor_01.png");
	assets->saveTexture("../others/pbr/basecolor_02.png");
	assets->saveTexture("../others/pbr/basecolor_03.png");
	assets->saveTexture("../others/pbr/basecolor_04.png");

	assets->saveTexture("../others/pbr/metallic_01.png");
	assets->saveTexture("../others/pbr/metallic_02.png");
	assets->saveTexture("../others/pbr/metallic_03.png");
	assets->saveTexture("../others/pbr/metallic_04.png");

	assets->saveTexture("../others/pbr/normal_01.png");
	assets->saveTexture("../others/pbr/normal_02.png");
	assets->saveTexture("../others/pbr/normal_03.png");
	assets->saveTexture("../others/pbr/normal_04.png");

	assets->saveTexture("../others/pbr/roughness_01.png");
	assets->saveTexture("../others/pbr/roughness_02.png");
	assets->saveTexture("../others/pbr/roughness_03.png");
	assets->saveTexture("../others/pbr/roughness_04.png");
	
	// ----- Camera ------
	ST::GameObj camera = gm.createGameObj(ST::TransformComponent{}, ST::CameraComponent{});
	camera.getComponent<ST::NameComponent>()->setName("Camera 02");
	camera.getComponent<ST::TransformComponent>()->setPosition(0.0f, 0.0f, -5.0f);
	camera.getComponent<ST::CameraComponent>()->setPerspective(90.0f, 1600.0f / 900.0f, 1.0f, 1000.0f);

	// --- SKYBOX ----
	//gm.setSkyboxTexture(assets->getCubeMap("Skybox Snow"));

	ST::GameObj ground = gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{});
	ground.getComponent<ST::NameComponent>()->setName("Ground");
	ground.getComponent<ST::TransformComponent>()->setScale({ 100.0f,0.2f,100.0f });
	ground.getComponent<ST::TransformComponent>()->setPosition({0.0f,-5.0f,0.0f});
	ground.getComponent<ST::RenderComponent>()->setMesh(assets->getMesh("Cube"));

	ST::GameObj wall01 = gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{});
	wall01.getComponent<ST::NameComponent>()->setName("Wall01");
	wall01.getComponent<ST::TransformComponent>()->setScale({ 10.0f,10.0f,1.0f });
	wall01.getComponent<ST::TransformComponent>()->setPosition({ 0.0f,0.0f,-20.0f });
	wall01.getComponent<ST::RenderComponent>()->setMesh(assets->getMesh("Cube"));

	ST::GameObj testObj = gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{});
	testObj.getComponent<ST::NameComponent>()->setName("CoreOBJ");
	testObj.getComponent<ST::RenderComponent>()->setMesh(assets->getMesh("helmet"));
	testObj.getComponent<ST::ColliderComponent>()->setMaxPoint(testObj.getComponent<ST::RenderComponent>()->mesh->getMaxPoint());
	testObj.getComponent<ST::ColliderComponent>()->setMinPoint(testObj.getComponent<ST::RenderComponent>()->mesh->getMinPoint());
	testObj.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(assets->getTexture("helmet_basecolor.tga"));
	testObj.getComponent<ST::RenderComponent>()->material.setTexture_Roughness(assets->getTexture("helmet_roughness.tga"));
	testObj.getComponent<ST::RenderComponent>()->material.setTexture_Metallic(assets->getTexture("helmet_metalness.tga"));
	testObj.getComponent<ST::TransformComponent>()->setScale({ 5.0f,5.0f,5.0f });
	testObj.getComponent<ST::TransformComponent>()->RotateX(90.0f);

	ST::Engine::createDirectLight(gm);
	gm.objectSelected = -1;

	//int HOWMANY = 500;
	//std::vector<ST::GameObj> objects;
	//for (int i = 0; i < HOWMANY; i++){
	//	objects.push_back(gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{}));

	//	objects.back().getComponent<ST::RenderComponent>()->setMesh(assets->getMesh("cat_petit"));
	//	objects.back().getComponent<ST::ColliderComponent>()->setMaxPoint(objects.back().getComponent<ST::RenderComponent>()->mesh->getMaxPoint());
	//	objects.back().getComponent<ST::ColliderComponent>()->setMinPoint(objects.back().getComponent<ST::RenderComponent>()->mesh->getMinPoint());
	//	//objects.back().getComponent<ST::RenderComponent>()->material.setTexture_Albedo(assets->getTexture("Cat_diffuse.jpg"));
	//	objects.back().getComponent<ST::RenderComponent>()->material.setTexIndex({ (int)ST::Engine::getRandom(0.0,8.0f),(int)ST::Engine::getRandom(0.0,8.0f) });
	//	objects.back().getComponent<ST::RenderComponent>()->material.roughness_ = ST::Engine::getRandom(0.1f, 1.0f);
	//	objects.back().getComponent<ST::RenderComponent>()->material.metallic_ = ST::Engine::getRandom(0.0f, 1.0f);
	//	objects.back().getComponent<ST::RenderComponent>()->material.setColor(ST::Engine::getRandom(0.0f, 1.0f), ST::Engine::getRandom(0.0f, 1.0f), ST::Engine::getRandom(0.0f, 1.0f));
	//	objects.back().getComponent<ST::TransformComponent>()->setPosition(glm::vec3(ST::Engine::getRandom(-100.0f, 100.0f), ST::Engine::getRandom(0.0f, 100.0f), ST::Engine::getRandom(-100.0f, 100.0f)));
	//	objects.back().getComponent<ST::TransformComponent>()->setRotateX(ST::Engine::getRandom(0.0f, 360.0f));
	//	objects.back().getComponent<ST::TransformComponent>()->setRotateY(ST::Engine::getRandom(0.0f, 360.0f));
	//	objects.back().getComponent<ST::TransformComponent>()->setRotateZ(ST::Engine::getRandom(0.0f, 360.0f));
	//	objects.back().getComponent<ST::TransformComponent>()->setScale(0.5f, 0.5f, 0.5f);
	//	//objects.back().getComponent<ST::TransformComponent>()->setScale(1.0f, 1.0f, 1.0f);
	//}
	
	//int countX = 7;
	//int countY = 7;
	//float offset = 2.0f;
	//for (int y = 0; y < countY; y++){
	//	float posY = (y - (countY-1) * 0.5f) * offset;
	//	for (int x = 0; x < countX; x++) {
	//		float posX = (x - (countY - 1) * 0.5f) * offset;
	//		ST::GameObj sphere = gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{});
	//		sphere.getComponent<ST::RenderComponent>()->setMesh(assets->getMesh("sphere"));
	//		sphere.getComponent<ST::TransformComponent>()->setPosition(posX, posY, 20.0f);
	//		sphere.getComponent<ST::RenderComponent>()->material.setColor(1.0f,0.0f,0.0f);
	//		sphere.getComponent<ST::RenderComponent>()->material.roughness_ = (float)(x + 1) / countX;
	//		sphere.getComponent<ST::RenderComponent>()->material.metallic_ = (float)(y + 1) / countY;
	//	}
	//}

	//for (int i = 0; i < 100; i++){
	//	ST::GameObj a = gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{}, ST::LightComponent{});

	//	a.getComponent<ST::TransformComponent>()->setPosition(glm::vec3(ST::Engine::getRandom(-50.0f, 50.0f), ST::Engine::getRandom(0.0f, 5.0f), ST::Engine::getRandom(-50.0f, 50.0f)));
	//	a.getComponent<ST::TransformComponent>()->setScale(glm::vec3(0.2f, 0.2f, 0.2f));
	//	//a.getComponent<ST::RenderComponent>()->material.setProgram(gm.unliteProgram);
	//	//a.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(assets->getTexture("halo_light.png"));
	//	//a.getComponent<ST::RenderComponent>()->setMesh(assets->getMesh("quad"));
	//	//a.getComponent<ST::RenderComponent>()->material.translucent = true;
	//	//a.getComponent<ST::RenderComponent>()->castShadow_ = false;
	//	a.getComponent<ST::LightComponent>()->color_ = { ST::Engine::getRandom(0.0f,1.0f),ST::Engine::getRandom(0.0f,1.0f), ST::Engine::getRandom(0.0f, 1.0f) };
	//	a.getComponent<ST::LightComponent>()->type_ = ST::Point;
	//	//a.getComponent<ST::LightComponent>()->linear_ = 0.7f;
	//	//a.getComponent<ST::LightComponent>()->quadratic_ = 1.0f;
	//}

	// --------------------------
	// **************** TEST *****************
	ST::SystemLight lightSystem;

	ST::RenderTarget myRenderTarget;
	myRenderTarget.addTexture(w.getWindowsWidth(), w.getWindowsHeight(), "gAlbedoSpec", ST::Texture::F_RGBA, ST::Texture::F_RGBA, ST::Texture::DT_U_BYTE); // Albedo / Specular
	myRenderTarget.addTexture(w.getWindowsWidth(), w.getWindowsHeight(), "gMetalRough", ST::Texture::F_RG, ST::Texture::F_RG, ST::Texture::DT_U_BYTE); // Metal / Roughness
	myRenderTarget.addTexture(w.getWindowsWidth(), w.getWindowsHeight(), "gPosition", ST::Texture::F_RGBA, ST::Texture::F_RGBA16, ST::Texture::DT_FLOAT); // Position
	myRenderTarget.addTexture(w.getWindowsWidth(), w.getWindowsHeight(), "gNormal", ST::Texture::F_RGBA, ST::Texture::F_RGBA16, ST::Texture::DT_FLOAT); // Normal
	myRenderTarget.addTexture(w.getWindowsWidth(), w.getWindowsHeight(), "gDepth", ST::Texture::F_DEPTH, ST::Texture::F_DEPTH, ST::Texture::DT_FLOAT); // Depth
	myRenderTarget.createQuadToRender(); // que lo haga solo?
	
	bool changeMode = false;
	bool hideHud = false;
	bool hideHudPress = false;
	// **************** TEST *****************

	while (w.isOpen() && !w.inputPressed(ST::ST_INPUT_ESCAPE)) {
		w.Clear();
		gm.drawcalls_ = 0;


		// ---- Update ----
		testObj.getComponent<ST::TransformComponent>()->setRotateZ(testObj.getComponent<ST::TransformComponent>()->getRotation().z + (w.DeltaTime() * 20.0f));	

		// ---- Camera ----
		ST::SystemCamera::Movemment(gm, w);
		ST::SystemCamera::UpdateCamera(gm);

		// ---- Update Transforms ----
		ST::SystemTransform::UpdateTransforms(gm);

		// ---- Lights ----
		lightSystem.CompileLights(gm);

		// ---- Render ----
		myRenderTarget.start();
		ST::SystemRender::Render(gm, *gm.g_buffer);
		myRenderTarget.end();
		myRenderTarget.renderOnScreen(gm, *gm.framebufferProgram, &lightSystem.lights_);
		
		ST::SystemRender::Render(gm, *gm.skyboxProgram);
		ST::SystemRender::Render(gm, *gm.unliteProgram);

		// ---------------- Change Deffered Mode ----------------
		if (w.inputPressed(ST::ST_INPUT_JUMP) && !changeMode) {
			myRenderTarget.nextVisualMode();
			changeMode = true;
		}
		if (w.inputReleased(ST::ST_INPUT_JUMP)) {
			changeMode = false;
		}

		// ---------------- Hide HUD ----------------
		if (w.inputPressed('P') && !hideHudPress) {
			hideHud = hideHud != true ? true : false;
			hideHudPress = true;
		}
		if (w.inputReleased('P')) {
			hideHudPress = false;
		}



		// ---------------- Picking ----------------
		if (w.inputPressed(ST::ST_INPUT_FIRE)) {
			gm.objectSelected = ST::SystemPicking::tryPickObj(w, gm);
		}
		if (w.inputPressed(ST::ST_INPUT_DELETE) && gm.objectSelected != -1) {
			if (gm.objectSelected == gm.mainCameraID()) {
				gm.deleteMainCamera();
			}
			gm.deleteGameObj(gm.objectSelected);
			gm.objectSelected = -1;
		}

		// ---------------- HUD ----------------
		if (!hideHud) {
			ST::SystemHUD::NavBar(gm);
			ST::SystemHUD::Hierarchy(gm);
			ST::SystemHUD::Inspector(gm);
			ST::SystemHUD::Stats(w, gm);
		}

		// ----------------------------

		w.Render();
	}
	return 0;
}