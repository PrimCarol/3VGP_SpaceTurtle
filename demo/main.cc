#include <st_engine.h>

int main() {
	ST::Window w;
	w.ColorBg(0.2f, 0.2f, 0.2f); // Optional

	// ----------------------------------------------------------------

	ST::GameObj_Manager gm;

	ST::Camera myCam;
	gm.mainCamera = &myCam; // <--- Esto deberia hacerlo solo.

	// --------------
	ST::Texture textureTest;
	//textureTest.generateMipmap = true;
	textureTest.set_mag_filter(ST::Texture::F_NEAREST);
	textureTest.set_min_filter(ST::Texture::F_NEAREST);
	textureTest.loadSource("../others/tilesheet.png");
	textureTest.setCols(71);
	textureTest.setRows(19);

	ST::Quad test_mesh;
	
	int HOWMANY = 10000;


	std::vector<ST::GameObj> objects;
	for (int i = 0; i < HOWMANY; i++){
		objects.push_back(gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{}));
		objects.back().getComponent<ST::RenderComponent>()->setMesh(&test_mesh);
		//objects.back().getComponent<ST::RenderComponent>()->material.translucent = false;
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

		myCam.fpsMovement(w, cameraSpeed);
		cameraSpeed += w.mouseWheelY();
		//printf("%f\n",w.mouseWheelY());

		ST::SystemTransform::UpdateTransforms(gm);
		ST::SystemLight::CompileLights(gm, *gm.basicProgram);
		ST::SystemRender::Render(gm, &myCam);

		if (w.inputPressed(ST::ST_INPUT_FIRE)) {
			gm.objectSelected = ST::SystemPicking::tryPickObj(w, gm, &myCam);
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