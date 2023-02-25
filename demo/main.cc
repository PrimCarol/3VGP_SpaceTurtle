#include <st_engine.h>

int main() {
	ST::Window w;
	w.ColorBg(0.2f, 0.2f, 0.2f); // Optional

	// ----------------------------------------------------------------

	ST::GameObj_Manager gm;

	//ST::Camera myCam;
	ST::GameObj camera = gm.createGameObj(ST::TransformComponent{}, ST::CameraComponent{});
	gm.mainCameraID = camera.getID(); // <--- Esto deberia hacerlo solo.

	// --------------
	ST::Texture textureTest;
	//textureTest.generateMipmap = true;
	textureTest.set_mag_filter(ST::Texture::F_NEAREST);
	textureTest.set_min_filter(ST::Texture::F_LINEAR);
	textureTest.loadSource("../others/tilesheet.png");
	textureTest.setCols(71);
	textureTest.setRows(19);

	ST::Quad test_mesh;
	//test_mesh.loadFromFile("../others/cat_petit.obj");
	
	int HOWMANY = 10000;

	std::vector<ST::GameObj> objects;
	for (int i = 0; i < HOWMANY; i++){
		objects.push_back(gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{}));
		objects.back().getComponent<ST::RenderComponent>()->setMesh(&test_mesh);
		objects.back().getComponent<ST::ColliderComponent>()->setMaxPoint(objects.back().getComponent<ST::RenderComponent>()->mesh->getMaxPoint());
		objects.back().getComponent<ST::ColliderComponent>()->setMinPoint(objects.back().getComponent<ST::RenderComponent>()->mesh->getMinPoint());
		//objects.back().getComponent<ST::RenderComponent>()->material.translucent = true;
		objects.back().getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&textureTest);
		//objects.back().getComponent<ST::RenderComponent>()->material.setTexIndex({ 9,15 });
		objects.back().getComponent<ST::RenderComponent>()->material.setTexIndex({ST::Engine::getRandom(0.0f,71.0f),ST::Engine::getRandom(0.0f,19.0f) });
		//objects.back().getComponent<ST::RenderComponent>()->material.setColor(ST::Engine::getRandom(0.0f,1.0f),ST::Engine::getRandom(0.0f,1.0f), ST::Engine::getRandom(0.0f, 1.0f), 0.5f);
		//objects.back().getComponent<ST::RenderComponent>()->material.shininess = ST::Engine::getRandom(1.0f, 999.0f);
		objects.back().getComponent<ST::RenderComponent>()->material.setProgram(gm.basicProgram);
		objects.back().getComponent<ST::TransformComponent>()->setPosition(glm::vec3(ST::Engine::getRandom(-300.0f,300.0f), ST::Engine::getRandom(-300.0f, 300.0f), ST::Engine::getRandom(0.0f, 600.0f)));
		objects.back().getComponent<ST::TransformComponent>()->setScale(0.5f, 0.5f, 1.0f);
		
	}

	// --------------------------
	float cameraSpeed = 10.0f;
	while (w.isOpen() && !w.inputPressed(ST::ST_INPUT_ESCAPE)) {
		w.Clear();

		//myCam.fpsMovement(w, cameraSpeed);
		cameraSpeed += w.mouseWheelY();

		ST::SystemCamera::UpdateCamera(gm);

		ST::SystemTransform::UpdateTransforms(gm);
		ST::SystemLight::CompileLights(gm, *gm.basicProgram);
		ST::SystemRender::Render(gm);

		if (w.inputPressed(ST::ST_INPUT_FIRE)) {
			gm.objectSelected = ST::SystemPicking::tryPickObj(w, gm/*, &myCam*/);
		}

		ST::SystemHUD::NavBar(gm);
		//ST::SystemHUD::Hierarchy(gm);
		ST::SystemHUD::Inspector(gm);
		ST::SystemHUD::Stats(w, gm);

		// ----------------------------

		w.Render();
	}
	return 0;
}