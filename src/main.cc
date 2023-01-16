#include <st_engine.h>

#include <systems/st_system_render.h>

int main() {
	ST::Window w;
	w.ColorBg(1.0f, 0.8f, 0.9f); // Optional

	// ----------------------------------------------------------------

	ST::GameObj_Manager gm;

	ST::Cube mesh;
	//mesh.loadFromFile("../others/cat_petit.obj");
	ST::Texture testureTest;
	testureTest.loadSource("../others/icon.png");

	std::vector<std::unique_ptr<ST::GameObj>> a;
	a.push_back(gm.createGameObj());

	for (int i = 0; i < a.size(); i++) {

		ST::RenderComponent* r = (ST::RenderComponent*)a[i]->getComponent(ST::kComp_Render);
		if (r) {
			r->setMesh(&mesh);
			r->material->setTexture_Albedo(&testureTest);
			//r->material->setColor(glm::vec3(ST::Engine::getRandom(0.0f, 1.0f),
			//								ST::Engine::getRandom(0.0f, 1.0f),
			//								ST::Engine::getRandom(0.0f, 1.0f)));
		}
	}

	// --------------------------

	while (w.isOpen() && !w.inputPressed(ST::ST_INPUT_ESCAPE)) {
		w.Clear();

		// ----------------------------------------------------------------
		//for (int i = 0; i < a.size(); i++){
		//	ST::TransformComponent* t = (ST::TransformComponent*)a[i]->getComponent(ST::kComp_Trans);
		//	if (t) {
		//		t->RotateY(2.0f * w.DeltaTime());
		//	}
		//}

		ST::TransformComponent* t = (ST::TransformComponent*)a[0]->getComponent(ST::kComp_Trans);
		if (t) {
			t->RotateY(2.0f * w.DeltaTime());
		}

		ST::SystemRender::Render(gm.renderComponentList_, gm.transformComponentList_);

		// ----------------------------

		w.Render();
	}
	return 0;
}