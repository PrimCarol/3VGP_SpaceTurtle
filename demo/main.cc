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
	textureTest.loadSource("../others/icon_nobg_big.png");
	//textureTest.setRows(8);
	//textureTest.setCols(8);

	ST::Cube test_mesh;
	
	int HOWMANY = 50000;

	std::vector<ST::GameObj> objects;
	for (int i = 0; i < HOWMANY; i++){
		objects.push_back(gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{}));
		objects.back().getComponent<ST::RenderComponent>()->setMesh(&test_mesh);
		//objects.back().getComponent<ST::RenderComponent>()->material.translucent = true;
		//objects.back().getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&textureTest);
		//objects.back().getComponent<ST::RenderComponent>()->material.setTexIndex({ST::Engine::getRandom(0.0f,8.0f),ST::Engine::getRandom(0.0f,8.0f) });
		objects.back().getComponent<ST::RenderComponent>()->material.setColor(ST::Engine::getRandom(0.0f,1.0f),ST::Engine::getRandom(0.0f,1.0f), ST::Engine::getRandom(0.0f, 1.0f));
		//objects.back().getComponent<ST::RenderComponent>()->material.shininess = ST::Engine::getRandom(1.0f, 999.0f);
		objects.back().getComponent<ST::RenderComponent>()->material.setProgram(gm.basicProgram);
		objects.back().getComponent<ST::TransformComponent>()->setPosition(glm::vec3(ST::Engine::getRandom(-300.0f,300.0f), ST::Engine::getRandom(-300.0f, 300.0f), ST::Engine::getRandom(0.0f, 600.0f)));
	}

	// --------------------------

	while (w.isOpen() && !w.inputPressed(ST::ST_INPUT_ESCAPE)) {
		w.Clear();

		myCam.fpsMovement(w, 10.0f);

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