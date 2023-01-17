#include <st_engine.h>

#include <systems/st_system_render.h>

#include <imgui.h>

int main() {
	ST::Window w;
	w.ColorBg(1.0f, 0.8f, 0.9f); // Optional

	// ----------------------------------------------------------------

	ST::GameObj_Manager gm;

	ST::Cube mesh;
	//mesh.loadFromFile("../others/cat_petit.obj");
	ST::Texture testureTest;
	testureTest.loadSource("../others/icon.png");

	std::unique_ptr<ST::GameObj> a = gm.createGameObj();
	ST::RenderComponent* r = (ST::RenderComponent*)a->getComponent(ST::kComp_Render);
	if (r) {
		r->setMesh(&mesh);
		r->material->setTexture_Albedo(&testureTest);
	}


	std::unique_ptr<ST::GameObj> b = gm.createGameObj();
	ST::HierarchyComponent* h = (ST::HierarchyComponent*)b->getComponent(ST::kComp_Hierarchy);
	if (h) {
		h->parentID = a.get()->getID();
	}

	ST::RenderComponent* r2 = (ST::RenderComponent*)b->getComponent(ST::kComp_Render);
	if (r2) {
		r2->setMesh(&mesh);
		r2->material->setColor(glm::vec3(ST::Engine::getRandom(0.0f, 1.0f),
										 ST::Engine::getRandom(0.0f, 1.0f),
										 ST::Engine::getRandom(0.0f, 1.0f)));
	}

	ST::TransformComponent* t2 = (ST::TransformComponent*)b->getComponent(ST::kComp_Trans);
	if (t2) {
		t2->setPosition(glm::vec3(0.0f,3.0f,0.0f));
	}

	// --------------------------

	while (w.isOpen() && !w.inputPressed(ST::ST_INPUT_ESCAPE)) {
		w.Clear();


		ST::TransformComponent* t = (ST::TransformComponent*)a->getComponent(ST::kComp_Trans);
		if (t) {
			t->RotateZ(2.0f * w.DeltaTime());
		}

		gm.UpdateTransforms();
		ST::SystemRender::Render(gm.renderComponentList_, gm.transformComponentList_);

		// ----------------------------

		w.Render();
	}
	return 0;
}