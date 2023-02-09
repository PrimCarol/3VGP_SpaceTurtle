#include <st_engine.h>

int main() {
	ST::Window w;
	w.ColorBg(0.2f, 0.2f, 0.2f); // Optional

	// ----------------------------------------------------------------

	ST::GameObj_Manager gm;
	//gm.addComponentClass<ST::RenderComponent>();
	//gm.addComponentClass<ST::TransformComponent>();
	//gm.addComponentClass<ST::HierarchyComponent>();
	//ST::GameObj* objSelected = nullptr;

	ST::Camera myCam;

	ST::Cube mesh_cube;
	ST::Quad mesh_quad;

	ST::Texture textureTest;
	textureTest.loadSource("../others/checker_texture.jpg");
	ST::Texture translucentTexture;
	translucentTexture.loadSource("../others/icon_nobg.png");


	// --------------------------

	while (w.isOpen() && !w.inputPressed(ST::ST_INPUT_ESCAPE)) {
		w.Clear();

		myCam.fpsMovement(w, 10.0f);

		ST::SystemTransform::UpdateTransforms(gm);
		/*ST::SystemRender::Render(*gm.getComponentVector<ST::RenderComponent>(),
								 *gm.getComponentVector<ST::TransformComponent>());*/

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