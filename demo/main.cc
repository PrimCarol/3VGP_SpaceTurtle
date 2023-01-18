#include <st_engine.h>

#include <systems/st_system_render.h>
#include <systems/st_system_transform.h>

int main() {
	ST::Window w;
	w.ColorBg(0.2f, 0.2f, 0.2f); // Optional

	// ----------------------------------------------------------------

	ST::GameObj_Manager gm;

	ST::Camera myCam;

	ST::Cube mesh_cube;
	ST::Geometry mesh_cat;
	mesh_cat.loadFromFile("../others/skull_petit.obj");
	ST::Texture textureTest;
	textureTest.loadSource("../others/icon.png");
	ST::Texture textureCat;
	textureCat.loadSource("../others/cat_diffuse.jpg");
	ST::Texture textureChecker;
	textureChecker.loadSource("../others/checker_texture.jpg");

	std::unique_ptr<ST::GameObj> Sun = gm.createGameObj();
	Sun->getComponentRender()->setMesh(&mesh_cube);
	Sun->getComponentRender()->material->setTexture_Albedo(&textureTest);

	std::unique_ptr<ST::GameObj> EarthRotationPoint = gm.createGameObj();
	std::unique_ptr<ST::GameObj> Earth = gm.createGameObj();

	Earth->getComponentHierarchy()->parentID = EarthRotationPoint->getID();

	Earth->getComponentRender()->setMesh(&mesh_cube);
	Earth->getComponentRender()->material->setTexture_Albedo(&textureChecker);

	Earth->getComponentTransform()->setPosition(glm::vec3(0.0f, 3.0f, 0.0f));
	Earth->getComponentTransform()->setScale(glm::vec3(0.4f,0.4f,0.4f));


	std::unique_ptr<ST::GameObj> MoonRotationPoint = gm.createGameObj();
	std::unique_ptr<ST::GameObj> Moon = gm.createGameObj();

	MoonRotationPoint->getComponentHierarchy()->parentID = Earth->getID();
	Moon->getComponentHierarchy()->parentID = MoonRotationPoint->getID();

	Moon->getComponentTransform()->setPosition(glm::vec3(0.0f, 3.0f, 0.0f));
	Moon->getComponentTransform()->setScale(glm::vec3(0.4f, 0.4f, 0.4f));

	Moon->getComponentRender()->setMesh(&mesh_cube);
	Moon->getComponentRender()->material->setTexture_Albedo(&textureChecker);

	// --------------------------

	while (w.isOpen() && !w.inputPressed(ST::ST_INPUT_ESCAPE)) {
		w.Clear();

		myCam.fpsMovement(w);

		Sun->getComponentTransform()->RotateZ(1.0f * w.DeltaTime());
		EarthRotationPoint->getComponentTransform()->RotateZ(-3.0f * w.DeltaTime());

		MoonRotationPoint->getComponentTransform()->RotateX(-5.0f * w.DeltaTime());

		ST::SystemTransform::UpdateTransforms(gm);
		ST::SystemRender::Render(gm.renderComponentList_, gm.transformComponentList_, &myCam);

		// ----------------------------

		w.Render();
	}
	return 0;
}