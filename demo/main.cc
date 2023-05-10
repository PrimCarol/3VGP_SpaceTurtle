#include <st_engine.h>

#include <imgui.h>
#include <st_shader.h>

int main() {
	ST::Window w(1600, 900);
	w.ColorBg(0.0f, 0.0f, 0.0f); // Optional
	
	// ----------------------------------------------------------------

	ST::GameObj_Manager gm;

	ST::GameObj camera = gm.createGameObj(ST::TransformComponent{}, ST::CameraComponent{});
	camera.getComponent<ST::NameComponent>()->setName("Camera 02");
	camera.getComponent<ST::TransformComponent>()->setPosition(0.0f, 0.0f, -5.0f);
	camera.getComponent<ST::CameraComponent>()->setPerspective(90.0f,1600.0f/900.0f, 1.0f, 1000.0f);


	ST::Texture textureSkybox;
	textureSkybox.init(0,0,ST::Texture::T_CUBEMAP, ST::Texture::DataType::DT_U_BYTE, ST::Texture::F_RGB, ST::Texture::F_RGB);
	textureSkybox.set_mag_filter(ST::Texture::F_LINEAR);
	textureSkybox.set_min_filter(ST::Texture::F_LINEAR);
	textureSkybox.loadCubemap("../others/skybox/right.jpg", ST::Texture::F_RGBA, 0);
	textureSkybox.loadCubemap("../others/skybox/left.jpg", ST::Texture::F_RGBA, 1);
	textureSkybox.loadCubemap("../others/skybox/top.jpg", ST::Texture::F_RGBA, 2);
	textureSkybox.loadCubemap("../others/skybox/bottom.jpg", ST::Texture::F_RGBA, 3);
	textureSkybox.loadCubemap("../others/skybox/front.jpg", ST::Texture::F_RGBA, 4);
	textureSkybox.loadCubemap("../others/skybox/back.jpg", ST::Texture::F_RGBA, 5);

	// --------------
	ST::Texture textureTest;
	textureTest.generateMipmap = true;
	//textureTest.set_mag_filter(ST::Texture::F_NEAREST);
	//textureTest.set_min_filter(ST::Texture::F_LINEAR);
	textureTest.loadSource("../others/checker_texture.jpg");
	//textureTest.setCols(71);
	//textureTest.setRows(19);

	ST::Texture textureCat;
	textureCat.loadSource("../others/Cat_diffuse.jpg");
	ST::Texture textureCatSpecular;
	textureCatSpecular.loadSource("../others/Cat_specular.png");

	ST::Texture otherTexture;
	otherTexture.loadSource("../others/icon.png");
	
	ST::Cube test_mesh;
	ST::Quad quad_mesh;

	ST::Geometry cat_mesh;
	cat_mesh.loadFromFile("../others/cat_petit.obj");
	
	// --- SKYBOX ----
	ST::GameObj skybox = gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{});
	skybox.getComponent<ST::NameComponent>()->setName("Skybox");
	skybox.getComponent<ST::TransformComponent>()->setScale({ 1000.0f,1000.0f,1000.0f });
	skybox.getComponent<ST::RenderComponent>()->material.setProgram(gm.skybox);
	skybox.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&textureSkybox);
	skybox.getComponent<ST::RenderComponent>()->setMesh(&test_mesh);
	skybox.getComponent<ST::RenderComponent>()->thiscullmode_ = ST::kCull_Front;
	//skybox.getComponent<ST::RenderComponent>()->thisdepthmode_ = ST::kDepth_Greater;

	ST::GameObj ground = gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{});
	ground.getComponent<ST::NameComponent>()->setName("Ground");
	ground.getComponent<ST::TransformComponent>()->setScale({ 100.0f,0.2f,100.0f });
	ground.getComponent<ST::TransformComponent>()->setPosition({0.0f,-5.0f,0.0f});
	ground.getComponent<ST::RenderComponent>()->material.setProgram(gm.g_buffer);
	//ground.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&textureTest);
	ground.getComponent<ST::RenderComponent>()->setMesh(&test_mesh);

	ST::GameObj testObj = gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{});
	testObj.getComponent<ST::NameComponent>()->setName("testObj");
	testObj.getComponent<ST::RenderComponent>()->setMesh(&cat_mesh);
	testObj.getComponent<ST::ColliderComponent>()->setMaxPoint(testObj.getComponent<ST::RenderComponent>()->mesh->getMaxPoint());
	testObj.getComponent<ST::ColliderComponent>()->setMinPoint(testObj.getComponent<ST::RenderComponent>()->mesh->getMinPoint());
	testObj.getComponent<ST::RenderComponent>()->material.setProgram(gm.g_buffer);
	testObj.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&textureCat);
	testObj.getComponent<ST::RenderComponent>()->material.setTexture_Specular(&textureCatSpecular);

	//ST::GameObj DirLight = gm.createGameObj(ST::TransformComponent{}, ST::LightComponent{});
	//DirLight.getComponent<ST::NameComponent>()->setName("DirLight");
	////DirLight.getComponent<ST::RenderComponent>()->setMesh(&test_mesh);
	////DirLight.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&textureTest);
	////DirLight.getComponent<ST::RenderComponent>()->material.setProgram(gm.g_buffer);
	////DirLight.getComponent<ST::RenderComponent>()->castShadow_ = false;
	//DirLight.getComponent<ST::TransformComponent>()->setPosition(0.000001f,10.0f,0.000001f);
	////DirLight.getComponent<ST::TransformComponent>()->setRotateY(1.63f);
	//DirLight.getComponent<ST::LightComponent>()->type_ = ST::Directional;
	//DirLight.getComponent<ST::LightComponent>()->ambient_ = glm::vec3(0.4f);
	//DirLight.getComponent<ST::LightComponent>()->diffuse_ = glm::vec3(0.7f);
	//DirLight.getComponent<ST::LightComponent>()->specular_ = glm::vec3(0.4f);

	//ST::Engine::createSpotLight(gm);

	int HOWMANY = 500;

	std::vector<ST::GameObj> objects;
	for (int i = 0; i < HOWMANY; i++){
		objects.push_back(gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{}));

		objects.back().getComponent<ST::RenderComponent>()->setMesh(&cat_mesh);
		objects.back().getComponent<ST::ColliderComponent>()->setMaxPoint(objects.back().getComponent<ST::RenderComponent>()->mesh->getMaxPoint());
		objects.back().getComponent<ST::ColliderComponent>()->setMinPoint(objects.back().getComponent<ST::RenderComponent>()->mesh->getMinPoint());
		//objects.back().getComponent<ST::RenderComponent>()->material.translucent = true;
		objects.back().getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&textureCat);
		//objects.back().getComponent<ST::RenderComponent>()->material.setTexIndex({ 9,15 });
		//objects.back().getComponent<ST::RenderComponent>()->material.setTexIndex({ST::Engine::getRandom(0.0f,71.0f),ST::Engine::getRandom(0.0f,19.0f) });
		//objects.back().getComponent<ST::RenderComponent>()->material.setColor(ST::Engine::getRandom(0.0f,1.0f),ST::Engine::getRandom(0.0f,1.0f), ST::Engine::getRandom(0.0f, 1.0f), 0.5f);
		//objects.back().getComponent<ST::RenderComponent>()->material.shininess = ST::Engine::getRandom(1.0f, 999.0f);
		objects.back().getComponent<ST::RenderComponent>()->material.setProgram(gm.g_buffer);
		//objects.back().getComponent<ST::TransformComponent>()->setPosition(glm::vec3(ST::Engine::getRandom(-50.0f, 50.0f), ST::Engine::getRandom(0.0f, 50.0f), ST::Engine::getRandom(-50.0f, 50.0f)));
		objects.back().getComponent<ST::TransformComponent>()->setPosition(glm::vec3(ST::Engine::getRandom(-50.0f, 50.0f), ST::Engine::getRandom(0.0f, 50.0f), ST::Engine::getRandom(-50.0f, 50.0f)));
		objects.back().getComponent<ST::TransformComponent>()->setRotateX(ST::Engine::getRandom(0.0f, 360.0f));
		objects.back().getComponent<ST::TransformComponent>()->setRotateY(ST::Engine::getRandom(0.0f, 360.0f));
		objects.back().getComponent<ST::TransformComponent>()->setRotateZ(ST::Engine::getRandom(0.0f, 360.0f));
		objects.back().getComponent<ST::TransformComponent>()->setScale(0.5f, 0.5f, 0.5f);		
	}

	//ST::Texture halo_Light;
	//halo_Light.loadSource("../others/halo_light.png");
	//for (int i = 0; i < 20; i++){
	//	ST::GameObj a = gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{}, ST::LightComponent{});

	//	a.getComponent<ST::TransformComponent>()->setPosition(glm::vec3(ST::Engine::getRandom(-50.0f, 50.0f), ST::Engine::getRandom(0.0f, 10.0f), ST::Engine::getRandom(-50.0f, 50.0f)));
	//	a.getComponent<ST::RenderComponent>()->material.setProgram(gm.unliteProgram);
	//	a.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&halo_Light);
	//	a.getComponent<ST::RenderComponent>()->setMesh(&quad_mesh);
	//	a.getComponent<ST::RenderComponent>()->material.translucent = true;
	//	a.getComponent<ST::RenderComponent>()->castShadow_ = false;
	//	a.getComponent<ST::LightComponent>()->color_ = { ST::Engine::getRandom(0.0f,1.0f),ST::Engine::getRandom(0.0f,1.0f), ST::Engine::getRandom(0.0f, 1.0f) };
	//	a.getComponent<ST::LightComponent>()->type_ = ST::Point;
	//}

	// --------------------------
	// **************** TEST *****************
	ST::SystemLight lightSystem;

	ST::RenderTarget myRenderTarget;
	myRenderTarget.addTexture(w.getWindowsWidth(), w.getWindowsHeight(), "gAlbedoSpec", ST::Texture::F_RGBA, ST::Texture::F_RGBA, ST::Texture::DT_U_BYTE); // Albedo
	myRenderTarget.addTexture(w.getWindowsWidth(), w.getWindowsHeight(), "gPosition", ST::Texture::F_RGBA, ST::Texture::F_RGBA16, ST::Texture::DT_FLOAT); // Position
	myRenderTarget.addTexture(w.getWindowsWidth(), w.getWindowsHeight(), "gNormal", ST::Texture::F_RGBA, ST::Texture::F_RGBA16, ST::Texture::DT_FLOAT); // Normal
	myRenderTarget.addTexture(w.getWindowsWidth(), w.getWindowsHeight(), "gDepth", ST::Texture::F_DEPTH, ST::Texture::F_DEPTH, ST::Texture::DT_FLOAT); // Depth
	myRenderTarget.createQuadToRender(); // que lo haga solo?
	
	bool changeMode = false;
	// **************** TEST *****************

	while (w.isOpen() && !w.inputPressed(ST::ST_INPUT_ESCAPE)) {
		w.Clear();



		// ---- Update ----
		skybox.getComponent<ST::TransformComponent>()->setPosition(camera.getComponent<ST::TransformComponent>()->getPosition());





		// ---- Camera ----
		ST::SystemCamera::Movemment(gm, w);
		ST::SystemCamera::UpdateCamera(gm);

		ST::SystemTransform::UpdateTransforms(gm);

		lightSystem.CompileLights(gm);

		myRenderTarget.start();
		ST::SystemRender::Render(gm, *gm.g_buffer);
		myRenderTarget.end();
		myRenderTarget.renderOnScreen(gm, *gm.framebufferProgram, &lightSystem.lights_);
		
		//ST::SystemRender::Render(gm, *gm.skybox);
		ST::SystemRender::Render(gm, *gm.unliteProgram);


		if (w.inputPressed(ST::ST_INPUT_JUMP) && !changeMode) {
			myRenderTarget.nextVisualMode();
			changeMode = true;
		}
		if (w.inputReleased(ST::ST_INPUT_JUMP)) {
			changeMode = false;
		}







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