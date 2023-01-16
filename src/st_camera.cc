#include <st_camera.h>

ST::Camera::Camera(){
	//transform_.RotateY(3.1415f);
	
	type = kCam_Perpective;

	target_ = nullptr;

	fov_ = 90.0f;
	ratio_ = (1080.0f/720.0f);
	nearPlane_ = 0.05f;
	farPlane_ = 1000.0f;

	horizontal_ = 20.0f;
	vertical_ = 20.0f;

	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);
}

void ST::Camera::setPerspective(float fov, float ratio ,float nearPlane, float farPlane){
	fov_ = fov;
	ratio_ = ratio;
	nearPlane_ = nearPlane;
	farPlane_ = farPlane;
	type = kCam_Perpective;
}

void ST::Camera::setOrthographic(float h, float v, float nearPlane, float farPlane){
	horizontal_ = h;
	vertical_ = v;
	nearPlane_ = nearPlane;
	farPlane_ = farPlane;
	type = kCam_Orthographic;
}

void ST::Camera::setTarget(glm::vec3* target){
	target_ = target;
}

void ST::Camera::update(){
	//view = glm::lookAt(transform_.getPosition(), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//view = glm::lookAt(transform_.getPosition(), transform_.getPosition() + transform_.getForward(), glm::vec3(0.0f, 1.0f, 0.0f));

	//transform_.updateTransformMatrix();
	//view = glm::inverse(transform_.m_transform_);

	if(target_){
		view = glm::lookAt(transform_.getPosition(), *target_, transform_.getUp());
	}
	else {
		view = glm::lookAt(transform_.getPosition(), transform_.getPosition() + transform_.getForward(), transform_.getUp());
	}


	//camForward = normalize(glm::vec3(view[2]));

	//glm::mat4 m(1.0f);
	//m = m * glm::rotate(m, transform_.getRotation().x, glm::vec3(1.0f,0.0f,0.0f));
	//m = m * glm::rotate(m, transform_.getRotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
	//m = m * glm::rotate(m, transform_.getRotation().z, glm::vec3(0.0f, 0.0f, 1.0f));
	//m = m * glm::translate(m, transform_.getPosition());
	//
	//view = glm::inverse(m);


	switch (type){
	case ST::kCam_Perpective:
		projection = glm::perspective(glm::radians(fov_), ratio_, nearPlane_, farPlane_);
		break;
	case ST::kCam_Orthographic:
		break;
		projection = glm::ortho(-(horizontal_ / 2.0f), horizontal_ / 2.0f, vertical_ / 2.0f, -(vertical_ / 2.0f), nearPlane_, farPlane_);
	}
}

ST::Camera::~Camera(){

}
