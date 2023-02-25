#include "st_system_camera.h"

#include <st_gameobj_manager.h>
#include <st_gameobj.h>
#include <components/st_transform.h>
#include <components/st_camera.h>

#include <transform.hpp>

void ST::SystemCamera::UpdateCamera(ST::GameObj_Manager& gm){
	//view = glm::lookAt(transform_.getPosition(), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//view = glm::lookAt(transform_.getPosition(), transform_.getPosition() + transform_.getForward(), glm::vec3(0.0f, 1.0f, 0.0f));

	//transform_.updateTransformMatrix();
	//view = glm::inverse(transform_.m_transform_);
	if (gm.mainCameraID >= 0) {
		//ST::GameObj mainCamera = gm.getGameObj(*gm.mainCamera);

		if (gm.getComponentVector<ST::TransformComponent>()->at(gm.mainCameraID).has_value() && gm.getComponentVector<ST::CameraComponent>()->at(gm.mainCameraID).has_value()) {
			ST::TransformComponent* transformCamera = &gm.getComponentVector<ST::TransformComponent>()->at(gm.mainCameraID).value();
			ST::CameraComponent* Camera = &gm.getComponentVector<ST::CameraComponent>()->at(gm.mainCameraID).value();

			glm::mat4 m(1.0f);

			m = glm::translate(m, transformCamera->getPosition());

			m = glm::rotate(m, transformCamera->getRotation().x, { 1.0f,0.0f,0.0f });
			m = glm::rotate(m, transformCamera->getRotation().y, { 0.0f,1.0f,0.0f });
			m = glm::rotate(m, transformCamera->getRotation().z, { 0.0f,0.0f,1.0f });

			//m = glm::scale(m, transform_.getScale());
			transformCamera->m_transform_ = m;

			transformCamera->updateDirectionalVectors();


			/*if (Camera->target_ != glm::vec3(-9.0f, -9.0f, -9.0f)) {
				view = glm::lookAt(transform_.getPosition(), target_, transform_.getUp());
			}
			else {
				view = glm::lookAt(transform_.getPosition(), transform_.getPosition() + transform_.getForward(), transform_.getUp());
			}*/

			Camera->view = glm::lookAt(transformCamera->getPosition(), transformCamera->getPosition() + transformCamera->getForward(), transformCamera->getUp());

			switch (Camera->getCameraType()) {
			case ST::kCam_Perpective:
				Camera->projection = glm::perspective(glm::radians(Camera->fov_), Camera->ratio_, Camera->nearPlane_, Camera->farPlane_);
				break;
			case ST::kCam_Orthographic:
				//ortho(-(800.0f / 2.0f), 800.0f / 2.0f, 600.0f / 2.0f, -(600.0f / 2.0f),-1000.0f, 1000.0f);
				Camera->projection = glm::ortho(-(Camera->horizontal_ / 2.0f), Camera->horizontal_ / 2.0f, Camera->vertical_ / 2.0f, -(Camera->vertical_ / 2.0f), Camera->nearPlane_, Camera->farPlane_);
				break;
			}
		}
	}
}
