#include <st_engine.h>

#include <imgui.h>
#include <st_shader.h>
#include <st_system_assets.h>

int main() {
	ST::Window w(1600, 900);
	w.ColorBg(0.0f, 0.0f, 0.0f);
	
	// ------------------------- ASSETS ---------------------------------

	std::shared_ptr<ST::SytemAssets> assets = std::make_shared<ST::SytemAssets>();
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
	assets->saveTexture("../others/pbr/basecolor_05_01.png");
	assets->saveTexture("../others/pbr/basecolor_05_02.png");
	assets->saveTexture("../others/pbr/basecolor_05_03.png");
	assets->saveTexture("../others/pbr/basecolor_05_04.png");
	assets->saveTexture("../others/pbr/basecolor_05_05.png");
	assets->saveTexture("../others/pbr/basecolor_05_06.png");
	assets->saveTexture("../others/pbr/basecolor_06.png");
	assets->saveTexture("../others/pbr/basecolor_07.png");
	assets->saveTexture("../others/pbr/basecolor_08.png");

	assets->saveTexture("../others/pbr/metallic_01.png");
	assets->saveTexture("../others/pbr/metallic_02.png");
	assets->saveTexture("../others/pbr/metallic_03.png");
	assets->saveTexture("../others/pbr/metallic_04.png");
	assets->saveTexture("../others/pbr/metallic_05.png");
	assets->saveTexture("../others/pbr/metallic_06.png");
	assets->saveTexture("../others/pbr/metallic_07.png");
	assets->saveTexture("../others/pbr/metallic_08.png");

	assets->saveTexture("../others/pbr/normal_01.png");
	assets->saveTexture("../others/pbr/normal_02.png");
	assets->saveTexture("../others/pbr/normal_03.png");
	assets->saveTexture("../others/pbr/normal_04.png");

	assets->saveTexture("../others/pbr/roughness_01.png");
	assets->saveTexture("../others/pbr/roughness_02.png");
	assets->saveTexture("../others/pbr/roughness_03.png");
	assets->saveTexture("../others/pbr/roughness_04.png");
	assets->saveTexture("../others/pbr/roughness_05.png");
	assets->saveTexture("../others/pbr/roughness_06.png");
	assets->saveTexture("../others/pbr/roughness_07.png");
	assets->saveTexture("../others/pbr/roughness_08.png");
	
	// ---------------- Demo 1 -----------------

	std::vector<ST::GameObj_Manager*> gm;
	ST::GameObj_Manager demo1;
	gm.push_back(&demo1);
	gm.back()->assets_ = assets;

	// ----- Camera ------
	ST::GameObj camera = gm.back()->createGameObj(ST::TransformComponent{}, ST::CameraComponent{});
	camera.getComponent<ST::NameComponent>()->setName("Camera");
	camera.getComponent<ST::TransformComponent>()->setPosition(0.0f, 0.0f, -10.0f);
	camera.getComponent<ST::CameraComponent>()->setPerspective(90.0f, 1600.0f / 900.0f, 1.0f, 1000.0f);

	// --- SKYBOX ----
	gm.back()->setSkyboxTexture(assets->getCubeMap("Skybox Snow"));

	ST::GameObj ground = gm.back()->createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{});
	ground.getComponent<ST::NameComponent>()->setName("Ground");
	ground.getComponent<ST::TransformComponent>()->setScale({ 100.0f,0.2f,100.0f });
	ground.getComponent<ST::TransformComponent>()->setPosition({0.0f,-5.0f,0.0f});
	ground.getComponent<ST::RenderComponent>()->setMesh(assets->getMesh("Cube"));

	ST::GameObj wall01 = gm.back()->createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{});
	wall01.getComponent<ST::NameComponent>()->setName("Wall01");
	wall01.getComponent<ST::TransformComponent>()->setScale({ 10.0f,10.0f,1.0f });
	wall01.getComponent<ST::TransformComponent>()->setPosition({ 0.0f,0.0f,-20.0f });
	wall01.getComponent<ST::RenderComponent>()->setMesh(assets->getMesh("Cube"));

	ST::GameObj testObj = gm.back()->createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{});
	testObj.getComponent<ST::NameComponent>()->setName("CoreOBJ");
	testObj.getComponent<ST::RenderComponent>()->setMesh(assets->getMesh("helmet"));
	testObj.getComponent<ST::ColliderComponent>()->setMaxPoint(testObj.getComponent<ST::RenderComponent>()->mesh->getMaxPoint());
	testObj.getComponent<ST::ColliderComponent>()->setMinPoint(testObj.getComponent<ST::RenderComponent>()->mesh->getMinPoint());
	testObj.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(assets->getTexture("helmet_basecolor.tga"));
	testObj.getComponent<ST::RenderComponent>()->material.setTexture_Roughness(assets->getTexture("helmet_roughness.tga"));
	testObj.getComponent<ST::RenderComponent>()->material.setTexture_Metallic(assets->getTexture("helmet_metalness.tga"));
	testObj.getComponent<ST::TransformComponent>()->setScale({ 5.0f,5.0f,5.0f });
	testObj.getComponent<ST::TransformComponent>()->RotateX(90.0f);

	ST::Engine::createDirectLight(*gm.back());
	gm.back()->objectSelected = -1;

	
	// ---------------- Demo 2 -----------------
	ST::GameObj_Manager demo2;
	gm.push_back(&demo2);
	gm.back()->assets_ = assets;

	// ----- Camera ------
	ST::GameObj camera2 = gm.back()->createGameObj(ST::TransformComponent{}, ST::CameraComponent{});
	camera2.getComponent<ST::NameComponent>()->setName("Camera");
	camera2.getComponent<ST::TransformComponent>()->setPosition(glm::vec3(0.0f, 150.0f, -170.0f));
	camera2.getComponent<ST::TransformComponent>()->setRotateX(-30.0);
	camera2.getComponent<ST::CameraComponent>()->setPerspective(90.0f, 1600.0f / 900.0f, 1.0f, 1000.0f);

	//ST::Engine::createDirectLight(*gm.back());
	//gm.back()->objectSelected = -1;

	ST::GameObj sunDemo2 = gm.back()->createGameObj(ST::TransformComponent{}, ST::LightComponent{});
	sunDemo2.getComponent<ST::LightComponent>()->type_ = ST::Directional;

	int HOWMANY = 200000;
	std::vector<ST::GameObj> objects;
	for (int i = 0; i < HOWMANY; i++){
		objects.push_back(gm.back()->createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{}));

		objects.back().getComponent<ST::RenderComponent>()->setMesh(assets->getMesh("cube"));
		objects.back().getComponent<ST::ColliderComponent>()->setMaxPoint(objects.back().getComponent<ST::RenderComponent>()->mesh->getMaxPoint());
		objects.back().getComponent<ST::ColliderComponent>()->setMinPoint(objects.back().getComponent<ST::RenderComponent>()->mesh->getMinPoint());
		//objects.back().getComponent<ST::RenderComponent>()->material.setTexture_Albedo(assets->getTexture("Cat_diffuse.jpg"));
		objects.back().getComponent<ST::RenderComponent>()->material.setTexIndex({ (int)ST::Engine::getRandom(0.0,8.0f),(int)ST::Engine::getRandom(0.0,8.0f) });
		objects.back().getComponent<ST::RenderComponent>()->material.roughness_ = ST::Engine::getRandom(0.1f, 1.0f);
		objects.back().getComponent<ST::RenderComponent>()->material.metallic_ = ST::Engine::getRandom(0.0f, 1.0f);
		objects.back().getComponent<ST::RenderComponent>()->material.setColor(ST::Engine::getRandom(0.0f, 1.0f), ST::Engine::getRandom(0.0f, 1.0f), ST::Engine::getRandom(0.0f, 1.0f));
		objects.back().getComponent<ST::RenderComponent>()->castShadow_ = false;
		objects.back().getComponent<ST::TransformComponent>()->setPosition(glm::vec3(ST::Engine::getRandom(-100.0f, 100.0f), ST::Engine::getRandom(0.0f, 100.0f), ST::Engine::getRandom(-100.0f, 100.0f)));
		objects.back().getComponent<ST::TransformComponent>()->setRotateX(ST::Engine::getRandom(0.0f, 360.0f));
		objects.back().getComponent<ST::TransformComponent>()->setRotateY(ST::Engine::getRandom(0.0f, 360.0f));
		objects.back().getComponent<ST::TransformComponent>()->setRotateZ(ST::Engine::getRandom(0.0f, 360.0f));
		objects.back().getComponent<ST::TransformComponent>()->setScale(0.5f, 0.5f, 0.5f);
		//objects.back().getComponent<ST::TransformComponent>()->setScale(1.0f, 1.0f, 1.0f);
	}
	
	// ---------------- Demo 3 -----------------
	ST::GameObj_Manager demo3;
	gm.push_back(&demo3);
	gm.back()->assets_ = assets;

	// ----- Camera ------
	ST::GameObj camera3 = gm.back()->createGameObj(ST::TransformComponent{}, ST::CameraComponent{});
	camera3.getComponent<ST::NameComponent>()->setName("Camera");
	camera3.getComponent<ST::TransformComponent>()->setPosition(glm::vec3(0.0f, 0.0f, -10.0f));
	camera3.getComponent<ST::CameraComponent>()->setPerspective(90.0f, 1600.0f / 900.0f, 1.0f, 1000.0f);

	ST::GameObj light = gm.back()->createGameObj(ST::TransformComponent{}, ST::LightComponent{});
	light.getComponent<ST::LightComponent>()->quadratic_ = 0.01f;	
	light.getComponent<ST::NameComponent>()->setName("light00");

	ST::GameObj light1 = gm.back()->createGameObj(ST::TransformComponent{}, ST::LightComponent{});
	//light1.getComponent<ST::LightComponent>()->type_ = ST::Spot;
	light1.getComponent<ST::LightComponent>()->quadratic_ = 0.01f;
	light1.getComponent<ST::NameComponent>()->setName("light01");

	ST::GameObj sphere1 = gm.back()->createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{});
	sphere1.getComponent<ST::RenderComponent>()->setMesh(assets->getMesh("sphere"));
	sphere1.getComponent<ST::TransformComponent>()->setPosition(-4.0f, 4.0f, 5.0f);
	sphere1.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(assets->getTexture("basecolor_01.png"));
	sphere1.getComponent<ST::RenderComponent>()->material.setTexture_Roughness(assets->getTexture("roughness_01.png"));
	sphere1.getComponent<ST::RenderComponent>()->material.setTexture_Metallic(assets->getTexture("metallic_01.png"));

	ST::GameObj sphere2 = gm.back()->createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{});
	sphere2.getComponent<ST::RenderComponent>()->setMesh(assets->getMesh("sphere"));
	sphere2.getComponent<ST::TransformComponent>()->setPosition(0.0f, 4.0f, 5.0f);
	sphere2.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(assets->getTexture("basecolor_03.png"));
	sphere2.getComponent<ST::RenderComponent>()->material.setTexture_Roughness(assets->getTexture("roughness_03.png"));
	sphere2.getComponent<ST::RenderComponent>()->material.setTexture_Metallic(assets->getTexture("metallic_03.png"));

	ST::GameObj sphere3 = gm.back()->createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{});
	sphere3.getComponent<ST::RenderComponent>()->setMesh(assets->getMesh("sphere"));
	sphere3.getComponent<ST::TransformComponent>()->setPosition(4.0f, 4.0f, 5.0f);
	sphere3.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(assets->getTexture("basecolor_06.png"));
	sphere3.getComponent<ST::RenderComponent>()->material.setTexture_Roughness(assets->getTexture("roughness_06.png"));
	sphere3.getComponent<ST::RenderComponent>()->material.setTexture_Metallic(assets->getTexture("metallic_06.png"));

	ST::GameObj sphere4 = gm.back()->createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{});
	sphere4.getComponent<ST::RenderComponent>()->setMesh(assets->getMesh("sphere"));
	sphere4.getComponent<ST::TransformComponent>()->setPosition(0.0f, 0.0f, 5.0f);
	sphere4.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(assets->getTexture("basecolor_08.png"));
	sphere4.getComponent<ST::RenderComponent>()->material.setTexture_Roughness(assets->getTexture("roughness_08.png"));
	sphere4.getComponent<ST::RenderComponent>()->material.setTexture_Metallic(assets->getTexture("metallic_08.png"));

	ST::GameObj sphere5 = gm.back()->createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{});
	sphere5.getComponent<ST::RenderComponent>()->setMesh(assets->getMesh("sphere"));
	sphere5.getComponent<ST::TransformComponent>()->setPosition(4.0f, 0.0f, 5.0f);
	sphere5.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(assets->getTexture("basecolor_02.png"));
	sphere5.getComponent<ST::RenderComponent>()->material.setTexture_Roughness(assets->getTexture("roughness_02.png"));
	sphere5.getComponent<ST::RenderComponent>()->material.setTexture_Metallic(assets->getTexture("metallic_02.png"));

	ST::GameObj sphere6 = gm.back()->createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{});
	sphere6.getComponent<ST::RenderComponent>()->setMesh(assets->getMesh("sphere"));
	sphere6.getComponent<ST::TransformComponent>()->setPosition(-4.0f, 0.0f, 5.0f);
	sphere6.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(assets->getTexture("basecolor_07.png"));
	sphere6.getComponent<ST::RenderComponent>()->material.setTexture_Roughness(assets->getTexture("roughness_07.png"));
	sphere6.getComponent<ST::RenderComponent>()->material.setTexture_Metallic(assets->getTexture("metallic_07.png"));

	ST::GameObj sphere_human_01 = gm.back()->createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{});
	sphere_human_01.getComponent<ST::RenderComponent>()->setMesh(assets->getMesh("sphere"));
	sphere_human_01.getComponent<ST::TransformComponent>()->setPosition(4.0f, -4.0f, 5.0f);
	sphere_human_01.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(assets->getTexture("basecolor_05_01.png"));
	sphere_human_01.getComponent<ST::RenderComponent>()->material.setTexture_Roughness(assets->getTexture("roughness_05.png"));
	sphere_human_01.getComponent<ST::RenderComponent>()->material.setTexture_Metallic(assets->getTexture("metallic_05.png"));
	ST::GameObj sphere_human_02 = gm.back()->createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{});
	sphere_human_02.getComponent<ST::RenderComponent>()->setMesh(assets->getMesh("sphere"));
	sphere_human_02.getComponent<ST::TransformComponent>()->setPosition(0.0f, -4.0f, 5.0f);
	sphere_human_02.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(assets->getTexture("basecolor_05_02.png"));
	sphere_human_02.getComponent<ST::RenderComponent>()->material.setTexture_Roughness(assets->getTexture("roughness_05.png"));
	sphere_human_02.getComponent<ST::RenderComponent>()->material.setTexture_Metallic(assets->getTexture("metallic_05.png"));
	ST::GameObj sphere_human_03 = gm.back()->createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{});
	sphere_human_03.getComponent<ST::RenderComponent>()->setMesh(assets->getMesh("sphere"));
	sphere_human_03.getComponent<ST::TransformComponent>()->setPosition(-4.0f, -4.0f, 5.0f);
	sphere_human_03.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(assets->getTexture("basecolor_05_03.png"));
	sphere_human_03.getComponent<ST::RenderComponent>()->material.setTexture_Roughness(assets->getTexture("roughness_05.png"));
	sphere_human_03.getComponent<ST::RenderComponent>()->material.setTexture_Metallic(assets->getTexture("metallic_05.png"));

	int countX = 7;
	int countY = 7;
	float offset = 3.0f;
	for (int y = 0; y < countY; y++){
		float posY = (y - (countY-1) * 0.5f) * offset;
		for (int x = 0; x < countX; x++) {
			float posX = (x - (countY - 1) * 0.5f) * offset;
			ST::GameObj sphere = gm.back()->createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{});
			sphere.getComponent<ST::RenderComponent>()->setMesh(assets->getMesh("sphere"));
			sphere.getComponent<ST::TransformComponent>()->setPosition(posX, posY, 10.0f);
			sphere.getComponent<ST::RenderComponent>()->material.setColor(1.0f,0.0f,0.0f);
			sphere.getComponent<ST::RenderComponent>()->material.roughness_ = (float)(x + 1) / countX;
			sphere.getComponent<ST::RenderComponent>()->material.metallic_ = (float)(y + 1) / countY;
		}
	}

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
	
	int demoIndex = 0;
	bool indexPressed = false;

	bool changeMode = false;
	bool hideHud = false;
	bool hideHudPress = false;
	// **************** TEST *****************

	while (w.isOpen() && !w.inputPressed(ST::ST_INPUT_ESCAPE)) {
		w.Clear();
		gm.at(demoIndex)->drawcalls_ = 0;

		//----- Change Scenes -----
		if (w.inputPressed('I') && !indexPressed) {
			demoIndex++;
			if (demoIndex >= gm.size()) { demoIndex = 0; }
			indexPressed = true;
		}
		if (w.inputReleased('I')) {
			indexPressed = false;
		}

		// ---- Update ----
		testObj.getComponent<ST::TransformComponent>()->setRotateZ(testObj.getComponent<ST::TransformComponent>()->getRotation().z + (w.DeltaTime() * 20.0f));	

		sunDemo2.getComponent<ST::TransformComponent>()->setRotateX(sunDemo2.getComponent<ST::TransformComponent>()->getRotation().x + (w.DeltaTime() * 20.0f));

		light1.getComponent<ST::TransformComponent>()->setPosition({sinf(w.CountTime()/1000) * 10.0f, cosf(w.CountTime()/1000) * 10.0f, 0.0f });

		// ---- Camera ----
		ST::SystemCamera::Movemment(*gm.at(demoIndex), w);
		ST::SystemCamera::UpdateCamera(*gm.at(demoIndex));

		// ---- Update Transforms ----
		ST::SystemTransform::UpdateTransforms(*gm.at(demoIndex));

		// ---- Lights ----
		lightSystem.CompileLights(*gm.at(demoIndex));

		// ---- Render ----
		myRenderTarget.start();
		ST::SystemRender::Render(*gm.at(demoIndex), *gm.at(demoIndex)->g_buffer);
		myRenderTarget.end();
		myRenderTarget.renderOnScreen(*gm.at(demoIndex), *gm.at(demoIndex)->framebufferProgram, &lightSystem.lights_);
		
		ST::SystemRender::Render(*gm.at(demoIndex), *gm.at(demoIndex)->skyboxProgram);
		ST::SystemRender::Render(*gm.at(demoIndex), *gm.at(demoIndex)->unliteProgram);

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
			gm.at(demoIndex)->objectSelected = ST::SystemPicking::tryPickObj(w, *gm.at(demoIndex));
		}
		if (w.inputPressed(ST::ST_INPUT_DELETE) && gm.at(demoIndex)->objectSelected != -1) {
			if (gm.at(demoIndex)->objectSelected == gm.at(demoIndex)->mainCameraID()) {
				gm.at(demoIndex)->deleteMainCamera();
			}
			gm.at(demoIndex)->deleteGameObj(gm.at(demoIndex)->objectSelected);
			gm.at(demoIndex)->objectSelected = -1;
		}

		// ---------------- HUD ----------------
		if (!hideHud) {
			ST::SystemHUD::NavBar(*gm.at(demoIndex));
			ST::SystemHUD::Hierarchy(*gm.at(demoIndex));
			ST::SystemHUD::Inspector(*gm.at(demoIndex));
			ST::SystemHUD::Stats(w, *gm.at(demoIndex));
		}

		// ----------------------------

		w.Render();
	}
	return 0;
}