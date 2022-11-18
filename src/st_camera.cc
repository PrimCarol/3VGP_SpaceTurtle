#include <st_camera.h>

//ST::Camera::Camera(){
//	
//}


ST::Camera::Camera(int width, int height, glm::vec3 pos){
	transform_.setPosition(pos);
	transform_.RotateY(3.1415f);
	width_ = width;
	height_ = height;

	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);
}

void ST::Camera::updateMatrix(float fov, float nearPlane, float farPlane){
	//view = glm::lookAt(transform_.getPosition(), transform_.getPosition() + transform_.getForward(), transform_.getUp());
	view = glm::inverse(transform_.m_transform_);
	projection = glm::perspective(glm::radians(fov), float(width_/height_), nearPlane, farPlane);
}

ST::Camera::~Camera(){

}
