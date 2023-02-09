#include <st_engine.h>

int main() {
	ST::Window w;
	w.ColorBg(0.2f, 0.2f, 0.2f); // Optional

	// ----------------------------------------------------------------

	ST::GameObj_Manager gm;

	//ST::GameObj* objSelected = nullptr;

	ST::Camera myCam;

	ST::Cube mesh_cube;
	ST::Quad mesh_quad;

	ST::Texture textureTest;
	textureTest.loadSource("../others/checker_texture.jpg");
	ST::Texture translucentTexture;
	translucentTexture.loadSource("../others/icon_nobg.png");

	std::vector<ST::GameObj> objects;
	for (int i = 0; i < 500; i++){
		int random = ST::Engine::getRandom(0.0f,100.0f);
		if (random > 20.0f) {
			objects.push_back(gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{}));
			objects.back().getComponent<ST::RenderComponent>()->setMesh(&mesh_cube);
			objects.back().getComponent<ST::RenderComponent>()->material.setProgram(gm.basicProgram);
			objects.back().getComponent<ST::RenderComponent>()->material.setColor(ST::Engine::getRandom(0.0f, 1.0f), ST::Engine::getRandom(0.0f, 1.0f), ST::Engine::getRandom(0.0f, 1.0f), ST::Engine::getRandom(0.0f, 1.0f));
			objects.back().getComponent<ST::RenderComponent>()->material.translucent = true;
		}else {
			objects.push_back(gm.createGameObj(ST::TransformComponent{}));
		}
		objects.back().getComponent<ST::TransformComponent>()->setPosition(ST::Engine::getRandom(-20.0f, 20.0f), ST::Engine::getRandom(-20.0f, 20.0f), ST::Engine::getRandom(0.0f, 40.0f));
	}

	// --------------------------

	while (w.isOpen() && !w.inputPressed(ST::ST_INPUT_ESCAPE)) {
		w.Clear();

		myCam.fpsMovement(w, 10.0f);

		ST::SystemTransform::UpdateTransforms(gm);
		ST::SystemRender::Render(*gm.getComponentVector<ST::RenderComponent>(),
								 *gm.getComponentVector<ST::TransformComponent>(), false, &myCam);

		//if (w.inputPressed(ST::ST_INPUT_FIRE)) {
		//	ST::GameObj* g = ST::SystemPicking::tryPickObj(w, gm);
		//	if (g) {
		//		objSelected = g;
		//	}
		//}

		//ST::SystemHUD::DrawHud(w, gm, objSelected);
		// ----------------------------

		w.Render();
	}
	return 0;
}