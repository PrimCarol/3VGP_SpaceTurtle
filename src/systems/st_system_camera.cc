#include "st_system_camera.h"

#include <st_gameobj_manager.h>
#include <st_gameobj.h>
#include <st_window.h>
#include <components/st_transform.h>
#include <components/st_camera.h>

#include <transform.hpp>

void ST::SystemCamera::UpdateCamera(ST::GameObj_Manager& gm){
	//view = glm::lookAt(transform_.getPosition(), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//view = glm::lookAt(transform_.getPosition(), transform_.getPosition() + transform_.getForward(), glm::vec3(0.0f, 1.0f, 0.0f));

	if (gm.mainCameraID() == -1) {
		auto camVector = gm.getComponentVector<ST::CameraComponent>();
		for (int i = 0; i < camVector->size(); i++) {
			if (camVector->at(i).has_value()) {
				ST::GameObj tempObj(i, gm);
				gm.setMainCamera(tempObj);
			}
		}
	}
	if (gm.mainCameraID() != -1) {
		//ST::GameObj mainCamera = gm.getGameObj(*gm.mainCamera);

		if (gm.getComponentVector<ST::TransformComponent>()->at(gm.mainCameraID()).has_value() && gm.getComponentVector<ST::CameraComponent>()->at(gm.mainCameraID()).has_value()) {
			ST::TransformComponent* transformCamera = &gm.getComponentVector<ST::TransformComponent>()->at(gm.mainCameraID()).value();
			ST::CameraComponent* Camera = &gm.getComponentVector<ST::CameraComponent>()->at(gm.mainCameraID()).value();

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

			//Camera->view = glm::lookAt(transformCamera->getPosition(), transformCamera->getPosition() + transformCamera->getForward(), transformCamera->getUp());
			
			Camera->lookAt(transformCamera->getPosition(), transformCamera->getPosition() + transformCamera->getForward(), transformCamera->getUp());
			
			switch (Camera->getCameraType()) {
			case ST::kCam_Perspective:
				//Camera->projection = glm::perspective(glm::radians(Camera->fov_), Camera->ratio_, Camera->nearPlane_, Camera->farPlane_);
				Camera->setPerspective(Camera->fov_, Camera->ratio_, Camera->nearPlane_, Camera->farPlane_);
				break;
			case ST::kCam_Orthographic:
				//ortho(-(800.0f / 2.0f), 800.0f / 2.0f, 600.0f / 2.0f, -(600.0f / 2.0f),-1000.0f, 1000.0f);
				//Camera->projection = glm::ortho(-(Camera->horizontal_ / 2.0f), Camera->horizontal_ / 2.0f, Camera->vertical_ / 2.0f, -(Camera->vertical_ / 2.0f), Camera->nearPlane_, Camera->farPlane_);
				Camera->setOrthographic(Camera->horizontal_, Camera->vertical_, Camera->nearPlane_, Camera->farPlane_);
				break;
			}
		}
	}
}

void ST::SystemCamera::Movemment(ST::GameObj_Manager& gm, ST::Window& w, float MoveSpeed, float RotateSpeed){
	static bool firtsMouse = true;
	static float lastX = 0.0f;
	static float lastY = 0.0f;
	static float cameraSpeed = 1.0f;

	MoveSpeed *= cameraSpeed;

	if (gm.mainCameraID() == -1) {
		auto camVector = gm.getComponentVector<ST::CameraComponent>();
		for (int i = 0; i < camVector->size(); i++) {
			if (camVector->at(i).has_value()) {
				ST::GameObj tempObj(i, gm);
				gm.setMainCamera(tempObj);
			}
		}
	}
	if (gm.mainCameraID() != -1) {
		if (gm.getComponentVector<ST::CameraComponent>()->at(gm.mainCameraID()).has_value() && gm.getComponentVector<ST::TransformComponent>()->at(gm.mainCameraID()).has_value()) {
			ST::CameraComponent* camComp = &gm.getComponentVector<ST::CameraComponent>()->at(gm.mainCameraID()).value();
			ST::TransformComponent* transComp = &gm.getComponentVector<ST::TransformComponent>()->at(gm.mainCameraID()).value();

			glm::vec2 mousePos = { w.mousePosX(), w.mousePosY() };
			float extra_speed = 1.0f;
			if (w.inputPressed(ST::ST_INPUT_SHIFT)) {
				extra_speed = 5.0f;
			}
			if (w.inputPressed(ST::ST_INPUT_UP)) {
				if (camComp->type == ST::kCam_Perspective) {
					transComp->Move(transComp->getForward() * (MoveSpeed * extra_speed * w.DeltaTime()));
				}else {
					transComp->Move(transComp->getUp() * (MoveSpeed * extra_speed * w.DeltaTime()));
				}
			}
			if (w.inputPressed(ST::ST_INPUT_DOWN)) {
				if (camComp->type == ST::kCam_Perspective) {
					transComp->Move(-transComp->getForward() * (MoveSpeed * extra_speed * w.DeltaTime()));
				}else {
					transComp->Move(-transComp->getUp() * (MoveSpeed * extra_speed * w.DeltaTime()));
				}
			}
			if (w.inputPressed(ST::ST_INPUT_LEFT)) {
				transComp->Move(-transComp->getRight() * (-MoveSpeed * extra_speed * w.DeltaTime()));
			}
			if (w.inputPressed(ST::ST_INPUT_RIGHT)) {
				transComp->Move(transComp->getRight() * (-MoveSpeed * extra_speed * w.DeltaTime()));
			}

			if (camComp->type == ST::kCam_Perspective) {
				
				if (firtsMouse) {
					lastX = mousePos.x;
					lastY = mousePos.y;
					firtsMouse = false;
				}
				float yoffset = mousePos.x - lastX;
				float xoffset = mousePos.y - lastY;
				lastX = mousePos.x;
				lastY = mousePos.y;
				if (w.inputPressed(ST::ST_INPUT_FIRE_SECOND)) {

					cameraSpeed += w.mouseWheelY() * 0.1f;
					if (cameraSpeed <= 0) {
						cameraSpeed = 0;
					}

					transComp->setRotateX(transComp->getRotation().x + -xoffset * RotateSpeed * w.DeltaTime());
					transComp->setRotateY(transComp->getRotation().y + yoffset * RotateSpeed * w.DeltaTime());
				}
			}
		}
	}
}
