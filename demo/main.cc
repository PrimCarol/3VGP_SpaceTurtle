#include <st_engine.h>

int main() {
	ST::Window w(1600, 840);
	w.ColorBg(0.2f, 0.2f, 0.2f); // Optional

	// ----------------------------------------------------------------

	ST::GameObj_Manager gm;

	//ST::Camera myCam;
	ST::GameObj camera = gm.createGameObj(ST::TransformComponent{}, ST::CameraComponent{});
	gm.mainCameraID = camera.getID(); // <--- Esto deberia hacerlo solo.
	camera.getComponent<ST::NameComponent>()->setName("Camera");
	camera.getComponent<ST::TransformComponent>()->setPosition(0.0f, 0.0f, -5.0f);

	// --------------
	ST::Texture textureTest;
	//textureTest.generateMipmap = true;
	//textureTest.set_mag_filter(ST::Texture::F_NEAREST);
	//textureTest.set_min_filter(ST::Texture::F_LINEAR);
	textureTest.loadSource("../others/tilesheet.png");
	textureTest.setCols(71);
	textureTest.setRows(19);

	ST::Cube test_mesh;
	//test_mesh.loadFromFile("../others/cat_petit.obj");
	
	//int HOWMANY = 1000;

	//std::vector<ST::GameObj> objects;
	//for (int i = 0; i < HOWMANY; i++){
	//	objects.push_back(gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{}));
	//	objects.back().getComponent<ST::RenderComponent>()->setMesh(&test_mesh);
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
	ST::GameObj DirLight = gm.createGameObj(ST::TransformComponent{}, ST::LightComponent{});
	DirLight.getComponent<ST::NameComponent>()->setName("DirLight");
	DirLight.getComponent<ST::TransformComponent>()->setRotateY(-1.0f);
	DirLight.getComponent<ST::TransformComponent>()->setRotateZ(0.5f);
	DirLight.getComponent<ST::LightComponent>()->type_ = ST::Directional;
	DirLight.getComponent<ST::LightComponent>()->ambient_ = glm::vec3(0.4f);
	DirLight.getComponent<ST::LightComponent>()->diffuse_ = glm::vec3(0.4f);
	DirLight.getComponent<ST::LightComponent>()->specular_ = glm::vec3(0.4f);

	// --------------------------
	float cameraSpeed = 10.0f;
	while (w.isOpen() && !w.inputPressed(ST::ST_INPUT_ESCAPE)) {
		w.Clear();

		//myCam.fpsMovement(w, cameraSpeed);
		cameraSpeed += w.mouseWheelY();

		ST::SystemCamera::Movemment(gm, w);
		ST::SystemCamera::UpdateCamera(gm);

		ST::SystemTransform::UpdateTransforms(gm);
		ST::SystemLight::CompileLights(gm, *gm.basicProgram);
		ST::SystemRender::Render(gm);

		if (w.inputPressed(ST::ST_INPUT_FIRE)) {
			gm.objectSelected = ST::SystemPicking::tryPickObj(w, gm);
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