#include <st_engine.h>

#include <systems/st_system_render.h>
#include <systems/st_system_transform.h>

#include <imgui.h>

int main() {
	ST::Window w;
	w.ColorBg(0.2f, 0.2f, 0.2f); // Optional

	// ----------------------------------------------------------------

	ST::GameObj_Manager gm;

	ST::Cube mesh_cube;
	ST::Geometry mesh_cat;
	mesh_cat.loadFromFile("../others/cat_petit.obj");
	ST::Texture textureTest;
	textureTest.loadSource("../others/icon.png");
	ST::Texture textureCat;
	textureCat.loadSource("../others/cat_diffuse.jpg");

	std::unique_ptr<ST::GameObj> Sun = gm.createGameObj();
	Sun->getComponentRender()->setMesh(&mesh_cube);
	Sun->getComponentRender()->material->setTexture_Albedo(&textureTest);

	std::unique_ptr<ST::GameObj> Earth = gm.createGameObj();
	std::unique_ptr<ST::GameObj> EarthRotationPoint = gm.createGameObj();

	Earth->getComponentHierarchy()->parentID = EarthRotationPoint.get()->getID();

	Earth->getComponentRender()->setMesh(&mesh_cat);
	Earth->getComponentRender()->material->setTexture_Albedo(&textureCat);


	Earth->getComponentTransform()->setPosition(glm::vec3(0.0f, 3.0f, 0.0f));
	Earth->getComponentTransform()->setScale(glm::vec3(0.4f,0.4f,0.4f));

	// --------------------------

	while (w.isOpen() && !w.inputPressed(ST::ST_INPUT_ESCAPE)) {
		w.Clear();


		Sun->getComponentTransform()->RotateZ(1.0f * w.DeltaTime());
		EarthRotationPoint->getComponentTransform()->RotateZ(-3.0f * w.DeltaTime());
		//Earth->getComponentTransform()->RotateZ(2.0f * w.DeltaTime());

		ST::SystemTransform::UpdateTransforms(gm);
		ST::SystemRender::Render(gm.renderComponentList_, gm.transformComponentList_);

		// ----------------------------

		w.Render();
	}
	return 0;
}