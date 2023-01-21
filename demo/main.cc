#include <st_engine.h>

#include <systems/st_system_render.h>
#include <systems/st_system_transform.h>
#include <systems/st_system_picking.h>

int main() {
	ST::Window w;
	w.ColorBg(0.2f, 0.2f, 0.2f); // Optional

	// ----------------------------------------------------------------

	ST::GameObj_Manager gm;

	ST::Camera myCam;

	ST::Cube mesh_cube;

	ST::Texture textureTest;
	textureTest.loadSource("../others/icon.png");
	ST::Texture textureChecker;
	textureChecker.loadSource("../others/checker_texture.jpg");

	std::unique_ptr<ST::GameObj> Sun = gm.createGameObj();
	Sun->getComponentRender()->setMesh(&mesh_cube);
	Sun->getComponentRender()->material->setTexture_Albedo(&textureTest);

	std::unique_ptr<ST::GameObj> Earth = gm.createGameObj();
	Earth->getComponentRender()->setMesh(&mesh_cube);
	Earth->getComponentRender()->material->setTexture_Albedo(&textureChecker);
	Earth->getComponentTransform()->setPosition(glm::vec3(0.0f, 3.0f, 0.0f));
	//Earth->getComponentTransform()->setScale(glm::vec3(0.4f,0.4f,0.4f));

	std::unique_ptr<ST::GameObj> Moon = gm.createGameObj();
	Moon->getComponentTransform()->setPosition(glm::vec3(3.0f, 0.0f, 0.0f));
	//Moon->getComponentTransform()->setScale(glm::vec3(0.4f, 0.4f, 0.4f));
	Moon->getComponentRender()->setMesh(&mesh_cube);
	Moon->getComponentRender()->material->setTexture_Albedo(&textureChecker);

	Earth->getComponentHierarchy()->setParent(*Sun);
	Moon->getComponentHierarchy()->setParent(*Earth);

	// --------------------------

	while (w.isOpen() && !w.inputPressed(ST::ST_INPUT_ESCAPE)) {
		w.Clear();

		myCam.fpsMovement(w);

		Sun->getComponentTransform()->RotateZ(1.0f * w.DeltaTime());
		Earth->getComponentTransform()->RotateY(-2.0f * w.DeltaTime());

		ST::SystemTransform::UpdateTransforms(gm);
		ST::SystemRender::Render(gm.renderComponentList_, gm.transformComponentList_ , &myCam );

		if (w.inputPressed(ST::ST_INPUT_FIRE)) {
			ST::GameObj* g = ST::SystemPicking::tryPickObj(w, gm , &myCam );
			if (g) {
				printf("Detecto un objeto  ->  %d \n", g->getID());
			}
		}

		// ----------------------------

		w.Render();
	}
	return 0;
}