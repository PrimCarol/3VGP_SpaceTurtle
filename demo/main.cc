#include <st_engine.h>

#include <imgui.h>
#include <st_shader.h>

int main() {
	ST::Window w(1600, 900);
	w.ColorBg(0.2f, 0.2f, 0.2f); // Optional
	
	// ----------------------------------------------------------------

	ST::GameObj_Manager gm;

	ST::GameObj camera = gm.createGameObj(ST::TransformComponent{}, ST::CameraComponent{});
	camera.getComponent<ST::NameComponent>()->setName("Camera 02");
	camera.getComponent<ST::TransformComponent>()->setPosition(0.0f, 0.0f, -5.0f);
	camera.getComponent<ST::CameraComponent>()->setPerspective(90.0f,1600.0f/840.0f, 0.01f, 100000.0f);

	// --------------
	ST::Texture textureTest;
	textureTest.generateMipmap = true;
	//textureTest.set_mag_filter(ST::Texture::F_NEAREST);
	//textureTest.set_min_filter(ST::Texture::F_LINEAR);
	textureTest.loadSource("../others/checker_texture.jpg");
	//textureTest.setCols(71);
	//textureTest.setRows(19);

	ST::Texture textureCat;
	textureCat.loadSource("../others/Cat_diffuse.jpg");

	ST::Texture otherTexture;
	otherTexture.loadSource("../others/icon.png");
	
	ST::Cube test_mesh;
	ST::Quad quad_mesh;

	ST::Geometry cat_mesh;
	cat_mesh.loadFromFile("../others/cat_petit.obj");
	
	//int HOWMANY = 200;

	//std::vector<ST::GameObj> objects;
	//for (int i = 0; i < HOWMANY; i++){
	//	objects.push_back(gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{}));
	//	objects.back().getComponent<ST::RenderComponent>()->setMesh(&cat_mesh);
	//	objects.back().getComponent<ST::ColliderComponent>()->setMaxPoint(objects.back().getComponent<ST::RenderComponent>()->mesh->getMaxPoint());
	//	objects.back().getComponent<ST::ColliderComponent>()->setMinPoint(objects.back().getComponent<ST::RenderComponent>()->mesh->getMinPoint());
	//	//objects.back().getComponent<ST::RenderComponent>()->material.translucent = true;
	//	objects.back().getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&textureCat);
	//	//objects.back().getComponent<ST::RenderComponent>()->material.setTexIndex({ 9,15 });
	//	//objects.back().getComponent<ST::RenderComponent>()->material.setTexIndex({ST::Engine::getRandom(0.0f,71.0f),ST::Engine::getRandom(0.0f,19.0f) });
	//	//objects.back().getComponent<ST::RenderComponent>()->material.setColor(ST::Engine::getRandom(0.0f,1.0f),ST::Engine::getRandom(0.0f,1.0f), ST::Engine::getRandom(0.0f, 1.0f), 0.5f);
	//	//objects.back().getComponent<ST::RenderComponent>()->material.shininess = ST::Engine::getRandom(1.0f, 999.0f);
	//	objects.back().getComponent<ST::RenderComponent>()->material.setProgram(gm.basicProgram);
	//	objects.back().getComponent<ST::TransformComponent>()->setPosition(glm::vec3(ST::Engine::getRandom(-50.0f, 50.0f), ST::Engine::getRandom(0.0f, 50.0f), ST::Engine::getRandom(-50.0f, 50.0f)));
	//	objects.back().getComponent<ST::TransformComponent>()->setRotateX(ST::Engine::getRandom(0.0f, 360.0f));
	//	objects.back().getComponent<ST::TransformComponent>()->setRotateY(ST::Engine::getRandom(0.0f, 360.0f));
	//	objects.back().getComponent<ST::TransformComponent>()->setRotateZ(ST::Engine::getRandom(0.0f, 360.0f));
	//	objects.back().getComponent<ST::TransformComponent>()->setScale(0.5f, 0.5f, 0.5f);		
	//}

	ST::GameObj ground = gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{});
	ground.getComponent<ST::NameComponent>()->setName("Ground");
	ground.getComponent<ST::TransformComponent>()->setScale({ 100.0f,0.2f,100.0f });
	ground.getComponent<ST::TransformComponent>()->setPosition({0.0f,-5.0f,0.0f});
	ground.getComponent<ST::RenderComponent>()->material.setProgram(gm.basicProgram);
	ground.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&textureTest);
	ground.getComponent<ST::RenderComponent>()->setMesh(&test_mesh);

	ST::GameObj testObj = gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{}, ST::ColliderComponent{});
	testObj.getComponent<ST::NameComponent>()->setName("testObj");
	testObj.getComponent<ST::RenderComponent>()->setMesh(&cat_mesh);
	testObj.getComponent<ST::ColliderComponent>()->setMaxPoint(testObj.getComponent<ST::RenderComponent>()->mesh->getMaxPoint());
	testObj.getComponent<ST::ColliderComponent>()->setMinPoint(testObj.getComponent<ST::RenderComponent>()->mesh->getMinPoint());
	testObj.getComponent<ST::RenderComponent>()->material.setProgram(gm.basicProgram);
	testObj.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&textureCat);

	ST::GameObj DirLight = gm.createGameObj(ST::TransformComponent{}, ST::LightComponent{});
	DirLight.getComponent<ST::NameComponent>()->setName("DirLight");
	DirLight.getComponent<ST::TransformComponent>()->setPosition(0.000001f,10.0f,0.0f);
	DirLight.getComponent<ST::TransformComponent>()->setRotateY(1.63f);
	DirLight.getComponent<ST::LightComponent>()->type_ = ST::Directional;
	DirLight.getComponent<ST::LightComponent>()->ambient_ = glm::vec3(0.4f);
	DirLight.getComponent<ST::LightComponent>()->diffuse_ = glm::vec3(0.4f);
	DirLight.getComponent<ST::LightComponent>()->specular_ = glm::vec3(0.4f);


	// --------------------------
	// **************** TEST *****************
	ST::SystemLight lightSystem;

	ST::RenderTarget myRenderTarget;
	myRenderTarget.setUp(w.getWindowsWidth(), w.getWindowsHeight());
	myRenderTarget.createQuadToRender();
	// **************** TEST *****************

	while (w.isOpen() && !w.inputPressed(ST::ST_INPUT_ESCAPE)) {
		w.Clear();

		// ---- Camera ----
		ST::SystemCamera::Movemment(gm, w);
		ST::SystemCamera::UpdateCamera(gm);

		ST::SystemTransform::UpdateTransforms(gm);

		lightSystem.CompileShadows(gm);
		lightSystem.CompileLights(gm, *gm.basicProgram);
		
		myRenderTarget.start();
		ST::SystemRender::Render(gm);
		myRenderTarget.end();

		myRenderTarget.renderOnScreen(*gm.postproces_blur);

		if (w.inputPressed(ST::ST_INPUT_FIRE)) {
			gm.objectSelected = ST::SystemPicking::tryPickObj(w, gm);
		}
		if (w.inputPressed(ST::ST_INPUT_DELETE) && gm.objectSelected != -1) {
			gm.deleteGameObj(gm.objectSelected);
			gm.objectSelected = -1;
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