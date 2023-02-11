#include <st_engine.h>

int main() {
	ST::Window w;
	w.ColorBg(0.2f, 0.2f, 0.2f); // Optional

	// ----------------------------------------------------------------

	ST::GameObj_Manager gm;

	//size_t objSelected = -1;

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
	for (int i = 0; i < 5; i++){
		int random = ST::Engine::getRandom(0.0f,100.0f);

		objects.push_back(gm.createGameObj(ST::TransformComponent{}, ST::HierarchyComponent{}, ST::RenderComponent{}));
			
		objects.back().getComponent<ST::RenderComponent>()->setMesh(&mesh_cube);
		objects.back().getComponent<ST::RenderComponent>()->material.setProgram(gm.basicProgram);
		
		if (ST::Engine::getRandom(0.0f, 100.0f) > 50.0f) {
			objects.back().getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&translucentTexture);
			objects.back().getComponent<ST::RenderComponent>()->material.translucent = true;
		}else {
			objects.back().getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&textureTest);
		}
		objects.back().getComponent<ST::RenderComponent>()->material.setColor(ST::Engine::getRandom(0.0f, 1.0f), ST::Engine::getRandom(0.0f, 1.0f), ST::Engine::getRandom(0.0f, 1.0f), ST::Engine::getRandom(0.2f, 1.0f));
		

		objects.back().getComponent<ST::TransformComponent>()->setPosition(ST::Engine::getRandom(-20.0f, 20.0f), ST::Engine::getRandom(-20.0f, 20.0f), ST::Engine::getRandom(0.0f, 40.0f));
	}

	// ----- Hacemos un "SOL" -----
	objects.at(1).getComponent<ST::TransformComponent>()->setPosition(0.0f,0.0f,0.0f);
	objects.at(1).getComponent<ST::TransformComponent>()->setRotateY(-0.5f);
	objects.at(1).getComponent<ST::TransformComponent>()->setRotateX(1.0f);
	objects.at(1).addComponent<ST::LightComponent>();
	objects.at(1).getComponent<ST::LightComponent>()->type_ = ST::Directional;
	objects.at(1).getComponent<ST::LightComponent>()->ambient_ = glm::vec3(0.1f, 0.1f, 0.1f);
	objects.at(1).removeComponent<ST::RenderComponent>();

	// --------------------------

	while (w.isOpen() && !w.inputPressed(ST::ST_INPUT_ESCAPE)) {
		w.Clear();

		myCam.fpsMovement(w, 10.0f);

		ST::SystemTransform::UpdateTransforms(gm);
		
		ST::SystemLight::CompileLights(gm);

		ST::SystemRender::Render(*gm.getComponentVector<ST::RenderComponent>(),
								 *gm.getComponentVector<ST::TransformComponent>(), false, &myCam);

		if (w.inputPressed(ST::ST_INPUT_FIRE)) {
			gm.objectSelected = ST::SystemPicking::tryPickObj(w, gm, &myCam);
		}

		ST::SystemHUD::Hierarchy(gm);
		ST::SystemHUD::Inspector(gm);
		ST::SystemHUD::Stats(w, gm);

		// ----------------------------

		w.Render();
	}
	return 0;
}