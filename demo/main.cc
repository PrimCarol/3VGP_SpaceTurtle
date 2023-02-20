#include <st_engine.h>

int main() {
	ST::Window w;
	w.ColorBg(0.2f, 0.2f, 0.2f); // Optional

	// ----------------------------------------------------------------

	ST::GameObj_Manager gm;

	ST::Camera myCam;
	gm.mainCamera = &myCam;

	//// ----- Hacemos un "SOL" -----
	//ST::GameObj Sun = gm.createGameObj(ST::TransformComponent{}, ST::LightComponent{});
	//Sun.getComponent<ST::NameComponent>()->setName("Sun");
	//Sun.getComponent<ST::TransformComponent>()->setPosition(0.0f,0.0f,0.0f);
	//Sun.getComponent<ST::TransformComponent>()->setRotateY(-0.5f);
	//Sun.getComponent<ST::TransformComponent>()->setRotateZ(1.0f);
	//Sun.getComponent<ST::LightComponent>()->type_ = ST::Directional;
	//Sun.getComponent<ST::LightComponent>()->ambient_ = glm::vec3(0.5f, 0.5f, 0.5f);

	// --------------
	ST::Texture textureTest;
	textureTest.loadSource("../others/basic_anim.png");
	textureTest.setRows(1);
	textureTest.setCols(8);

	ST::Texture textureSpecular;
	textureSpecular.loadSource("../others/icon.png");

	//ST::Texture textureNormal;
	//textureNormal.loadSource("../others/NormalMap.png");
	//textureNormal.setRows(1);
	//textureNormal.setCols(8);

	ST::Test test_mesh;

	int HOWMANY = 100000;

	std::vector<ST::GameObj> objects;
	for (int i = 0; i < HOWMANY; i++){
		objects.push_back(gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{}));
		objects.back().getComponent<ST::RenderComponent>()->setMesh(&test_mesh);
		objects.back().getComponent<ST::RenderComponent>()->material.translucent = false;
		objects.back().getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&textureTest);
		objects.back().getComponent<ST::RenderComponent>()->material.setProgram(gm.basicProgram);
		objects.back().getComponent<ST::TransformComponent>()->setPosition(glm::vec3(ST::Engine::getRandom(-300.0f,300.0f), ST::Engine::getRandom(-300.0f, 300.0f), ST::Engine::getRandom(0.0f, 600.0f)));
	}

	for (int i = 0; i < HOWMANY; i++) {
		objects.push_back(gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{}));
		objects.back().getComponent<ST::RenderComponent>()->setMesh(&test_mesh);
		objects.back().getComponent<ST::RenderComponent>()->material.translucent = false;
		objects.back().getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&textureSpecular);
		objects.back().getComponent<ST::RenderComponent>()->material.setProgram(gm.basicProgram);
		objects.back().getComponent<ST::TransformComponent>()->setPosition(glm::vec3(ST::Engine::getRandom(-300.0f, 300.0f), ST::Engine::getRandom(-300.0f, 300.0f), ST::Engine::getRandom(0.0f, 600.0f)));
	}

	//ST::Texture textureTest;
	//textureTest.loadSource("../others/bricks_albedo.png");
	//ST::Texture textureNormal;
	//textureNormal.loadSource("../others/bricks_normal.png");


	//ST::Cube mesh_cube;
	//ST::GameObj obj = gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{});
	//obj.getComponent<ST::RenderComponent>()->setMesh(&mesh_cube);
	//obj.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&textureTest);
	//obj.getComponent<ST::RenderComponent>()->material.setTexture_Normal(&textureNormal);
	//obj.getComponent<ST::RenderComponent>()->material.setProgram(gm.basicProgram);

	// --------------------------

	int contadorAnimation = 0;
	float contadorCadaCuantosFrames = 0;

	while (w.isOpen() && !w.inputPressed(ST::ST_INPUT_ESCAPE)) {
		w.Clear();

		myCam.fpsMovement(w, 10.0f);

		// --------- Animation --------
		//for (int i = 0; i < HOWMANY; i++){
		//	objects.at(i).getComponent<ST::RenderComponent>()->material.setTexIndex({ contadorAnimation, 6 });
		//}

		//if (contadorCadaCuantosFrames >= 0.12f) {
		//	contadorCadaCuantosFrames = 0;
		//	contadorAnimation++;
		//}
		//contadorCadaCuantosFrames += w.DeltaTime();
		

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