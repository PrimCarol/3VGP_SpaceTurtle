#include <st_engine.h>

int main() {
	ST::Window w;
	w.ColorBg(0.2f, 0.2f, 0.2f); // Optional

	// ----------------------------------------------------------------

	ST::GameObj_Manager gm;
	ST::GameObj* objSelected = nullptr;

	ST::Camera myCam;

	ST::Cube mesh_cube;
	ST::Quad mesh_quad;

	ST::Texture textureTest;
	textureTest.loadSource("../others/checker_texture.jpg");
	ST::Texture translucentTexture;
	translucentTexture.loadSource("../others/icon_nobg.png");

	std::unique_ptr<ST::GameObj> Sun = gm.createGameObj();
	Sun->getComponentRender()->setMesh(&mesh_cube);
	Sun->getComponentRender()->material->setTexture_Albedo(&textureTest);
	Sun->getComponentRender()->material->translucent = true;

	std::unique_ptr<ST::GameObj> Earth = gm.createGameObj();
	Earth->getComponentRender()->setMesh(&mesh_cube);
	Earth->getComponentRender()->material->setTexture_Albedo(&translucentTexture);
	Earth->getComponentRender()->material->translucent = true;
	Earth->getComponentTransform()->setPosition(glm::vec3(0.0f, 0.0f, -3.0f));
	Earth->getComponentTransform()->setScale(glm::vec3(0.4f,0.4f,0.4f));
	Earth->getComponentHierarchy()->setParent(*Sun);

	std::unique_ptr<ST::GameObj> Moon = gm.createGameObj();
	Moon->getComponentTransform()->setPosition(glm::vec3(3.0f, 0.0f, 0.0f));
	Moon->getComponentTransform()->setScale(glm::vec3(0.4f, 0.4f, 0.4f));
	Moon->getComponentRender()->setMesh(&mesh_cube);
	Moon->getComponentRender()->material->setColor(ST::Engine::getRandom(0.0f, 1.0f), ST::Engine::getRandom(0.0f, 1.0f), ST::Engine::getRandom(0.0f, 1.0f));
	Moon->getComponentRender()->material->setTexture_Albedo(&translucentTexture);
	//Moon->getComponentHierarchy()->setParent(*Earth);

	// --------------------------

	while (w.isOpen() && !w.inputPressed(ST::ST_INPUT_ESCAPE)) {
		w.Clear();

		myCam.fpsMovement(w, 10.0f);

		Sun->getComponentTransform()->RotateY(0.5f * w.DeltaTime());

		ST::SystemTransform::UpdateTransforms(gm);
		ST::SystemRender::Render(gm.renderComponentList_, gm.transformComponentList_, false, &myCam );

		if (w.inputPressed(ST::ST_INPUT_FIRE)) {
			ST::GameObj* g = ST::SystemPicking::tryPickObj(w, gm , &myCam );
			if (g) {
				objSelected = g;
			}
		}

		ST::SystemHUD::DrawHud(w, gm, objSelected);
		// ----------------------------

		w.Render();
	}
	return 0;
}