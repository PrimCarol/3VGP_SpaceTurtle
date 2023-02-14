#include <st_engine.h>

int main() {
	ST::Window w;
	w.ColorBg(0.2f, 0.2f, 0.2f); // Optional

	// ----------------------------------------------------------------

	ST::GameObj_Manager gm;

	ST::Camera myCam;

	//// ----- Hacemos un "SOL" -----
	ST::GameObj Sun = gm.createGameObj(ST::TransformComponent{}, ST::LightComponent{});
	Sun.getComponent<ST::NameComponent>()->setName("Sun");
	Sun.getComponent<ST::TransformComponent>()->setPosition(0.0f,0.0f,0.0f);
	Sun.getComponent<ST::TransformComponent>()->setRotateY(-0.5f);
	Sun.getComponent<ST::TransformComponent>()->setRotateX(1.0f);
	Sun.getComponent<ST::LightComponent>()->type_ = ST::Directional;
	Sun.getComponent<ST::LightComponent>()->ambient_ = glm::vec3(0.5f, 0.5f, 0.5f);

	// --------------
	ST::Texture textureTest;
	textureTest.loadSource("../others/test_animation.png");
	textureTest.setRows(1);
	textureTest.setCols(8);

	ST::Quad mesh_quad;

	std::vector<ST::GameObj> objects;
	for (int i = 0; i < 100; i++){
		objects.push_back(gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{}));
		objects.back().getComponent<ST::RenderComponent>()->setMesh(&mesh_quad);
		objects.back().getComponent<ST::RenderComponent>()->material.translucent = true;
		objects.back().getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&textureTest);
		objects.back().getComponent<ST::RenderComponent>()->material.setProgram(gm.basicProgram);
		objects.back().getComponent<ST::TransformComponent>()->setPosition(glm::vec3(ST::Engine::getRandom(-20.0f,20.0f), ST::Engine::getRandom(-20.0f, 20.0f), ST::Engine::getRandom(0.0f, 40.0f)));
	}
	//ST::GameObj obj = gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{});
	//obj.getComponent<ST::RenderComponent>()->setMesh(&mesh_quad);
	//obj.getComponent<ST::RenderComponent>()->material.translucent = true;
	//obj.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&textureTest);
	//obj.getComponent<ST::RenderComponent>()->material.setProgram(gm.basicProgram);

	// --------------------------

	int contadorAnimation = 0;
	float contadorCadaCuantosFrames = 0;

	while (w.isOpen() && !w.inputPressed(ST::ST_INPUT_ESCAPE)) {
		w.Clear();

		myCam.fpsMovement(w, 10.0f);

		// --------- Animation --------
		for (int i = 0; i < 100; i++){
			objects.at(i).getComponent<ST::RenderComponent>()->material.setTexIndex({ contadorAnimation, 6 });
		}

		if (contadorCadaCuantosFrames >= 0.2f) {
			contadorCadaCuantosFrames = 0;
			contadorAnimation++;
		}
		contadorCadaCuantosFrames += w.DeltaTime();
		

		ST::SystemTransform::UpdateTransforms(gm);
		ST::SystemLight::CompileLights(gm);
		ST::SystemRender::Render(gm, &myCam);

		if (w.inputPressed(ST::ST_INPUT_FIRE)) {
			gm.objectSelected = ST::SystemPicking::tryPickObj(w, gm, &myCam);
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