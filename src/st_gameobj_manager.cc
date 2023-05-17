#include <st_gameobj_manager.h>

#include <st_engine.h>
#include <st_gameobj.h>

#include <components/st_transform.h>
#include <components/st_hierarchy.h>
#include <components/st_name.h>
#include <components/st_render.h>
#include <components/st_collider.h>
#include <components/st_light.h>
#include <components/st_camera.h>

ST::GameObj_Manager::GameObj_Manager(){

	addComponentClass<ST::TransformComponent>();
	addComponentClass<ST::HierarchyComponent>();
	addComponentClass<ST::NameComponent>();
	addComponentClass<ST::RenderComponent>();
	addComponentClass<ST::ColliderComponent>();
	addComponentClass<ST::LightComponent>();
	addComponentClass<ST::CameraComponent>();
	
	objectSelected = ST::GameObj::null_id;
	root.addComponent<ST::HierarchyComponent>();

	mainCameraID_ = -1;

	// ------- Create Unlite Program -------
	unliteProgram = std::make_unique<ST::Program>();
	unliteProgram->setUp("../shaders/shader_unlite.vert", "../shaders/shader_unlite.frag");

	// ------- Create Normals Program -------
	normalsProgram = std::make_unique<ST::Program>();
	normalsProgram->setUp("../shaders/normals.vert", "../shaders/normals.frag", "../shaders/normals.geom");

	// ------- Create Shadow Mapping Program -------
	shadowMapping = std::make_unique<ST::Program>();
	shadowMapping->setUp("../shaders/shadowMapping.vert", "../shaders/shadowMapping.frag");

	// ------- Create Shadow Mapping Program PointLight -------
	shadowMappingPoint = std::make_unique<ST::Program>();
	shadowMappingPoint->setUp("../shaders/shadowMappingPoint.vert", "../shaders/shadowMappingPoint.frag", "../shaders/shadowMappingPoint.geom");

	// ------- Create FrameBuffer Program -------
	framebufferProgram = std::make_unique<ST::Program>();
	framebufferProgram->setUp("../shaders/frameBuffer.vert", "../shaders/frameBuffer.frag");

	// ------- Create FrameBuffer SSAO Program -------
	framebufferSSAOProgram = std::make_unique<ST::Program>();
	framebufferSSAOProgram->setUp("../shaders/frameBufferSSAO.vert", "../shaders/frameBufferSSAO.frag");

	// ------- Create PostProces BLUR Program -------
	postproces_blur = std::make_unique<ST::Program>();
	postproces_blur->setUp("../shaders/postproces_blur.vert", "../shaders/postproces_blur.frag");

	// ------- Create G-Buffer Program -------
	g_buffer = std::make_unique<ST::Program>();
	g_buffer->setUp("../shaders/g_buffers.vert", "../shaders/g_buffers.frag");

	// ------- Create Skybox Program -------
	skybox = std::make_unique<ST::Program>();
	skybox->setUp("../shaders/skybox.vert", "../shaders/skybox.frag");
}

void ST::GameObj_Manager::deleteGameObj(int ObjID){
	for (auto& [type, components_vector_] : component_map_) {
		components_vector_->deleteOn(ObjID);
	}
}

size_t ST::GameObj_Manager::size() const{
	return last_gameObj_;
}

void ST::GameObj_Manager::setMainCamera(const ST::GameObj& cam){
	if (cam.getComponent<ST::CameraComponent>()) {
		mainCameraID_ = cam.getID();
	}else {
		mainCameraID_ = -1;
	}
}

int ST::GameObj_Manager::mainCameraID() const{
	return mainCameraID_;
}

ST::GameObj_Manager::GameObj_Manager(const GameObj_Manager& o){
	printf("Copia GameObj_Manager -> No deberia de estar haciendo esto.");
}

ST::GameObj_Manager::~GameObj_Manager(){

}
