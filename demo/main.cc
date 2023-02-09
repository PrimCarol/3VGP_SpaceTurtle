#include <st_engine.h>

int main() {
	ST::Window w;
	w.ColorBg(0.2f, 0.2f, 0.2f); // Optional

	// ----------------------------------------------------------------

	ST::GameObj_Manager gm;

	size_t objSelected = -1;

	ST::Camera myCam;

	ST::Cube mesh_cube;
	ST::Quad mesh_quad;
	ST::Geometry mesh_cat;
	mesh_cat.loadFromFile("../others/cat_petit.obj");

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
		
			if (ST::Engine::getRandom(0.0f, 100.0f) > 50.0f) {
				objects.back().getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&translucentTexture);
			}else {
				objects.back().getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&textureTest);
			}
			objects.back().getComponent<ST::RenderComponent>()->material.setColor(ST::Engine::getRandom(0.0f, 1.0f), ST::Engine::getRandom(0.0f, 1.0f), ST::Engine::getRandom(0.0f, 1.0f), ST::Engine::getRandom(0.2f, 1.0f));
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
		//	//if (g) {
		//	//	objSelected = g;
		//	//}
		//	if (g) {
		//		printf("[%d]\n", g->getID());
		//	}
		//}

		if (w.inputPressed(ST::ST_INPUT_FIRE)) {
			objSelected = ST::SystemPicking::tryPickObj(w, gm);
			//printf("[%d]\n", objSelected);
		}

		ST::SystemHUD::Inspector(gm, objSelected);


		//ST::SystemHUD::DrawHud(w, gm, objSelected);
		// ----------------------------

		w.Render();
	}
	return 0;
}