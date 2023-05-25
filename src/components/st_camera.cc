#include <components/st_camera.h>

#include <st_window.h>
#include <st_texture.h>

ST::CameraComponent::CameraComponent(){
	
	type = kCam_Perspective;

	fov_ = 90.0f;
	ratio_ = (1080.0f / 720.0f);
	nearPlane_ = 0.05f;
	farPlane_ = 1000.0f;

	horizontal_ = 10.0f;
	vertical_ = 10.0f;

	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);
}

void ST::CameraComponent::setPerspective(float fov, float ratio, float nearPlane, float farPlane) {
	fov_ = fov;
	ratio_ = ratio;
	nearPlane_ = nearPlane;
	farPlane_ = farPlane;
	type = kCam_Perspective;
	projection = glm::perspective(glm::radians(fov_), ratio_, nearPlane_, farPlane_);
}

void ST::CameraComponent::setOrthographic(float h, float v, float nearPlane, float farPlane) {
	horizontal_ = h;
	vertical_ = v;
	nearPlane_ = nearPlane;
	farPlane_ = farPlane;
	type = kCam_Orthographic;
	projection = glm::ortho(-(horizontal_ / 2.0f), horizontal_ / 2.0f, -(vertical_ / 2.0f), vertical_ / 2.0f, nearPlane_, farPlane_);
}

ST::CameraType ST::CameraComponent::getCameraType() const {
	return type;
}

void ST::CameraComponent::lookAt(glm::vec3 myPos, glm::vec3 target, glm::vec3 upCamVector){
	view = glm::lookAt(myPos, target, upCamVector);
}

ST::CameraComponent::~CameraComponent(){
	//printf("Destroy Component: Collider\n");
}
