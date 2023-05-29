#include "st_system_light.h"

#include <st_gameobj_manager.h>
#include <components/st_light.h>
#include <components/st_render.h>
#include <components/st_transform.h>

#include <components/st_camera.h>

#include <st_program.h>

ST::SystemLight::SystemLight(){

}

void ST::SystemLight::CompileLights(ST::GameObj_Manager& gm) {

	auto& lightComps = *gm.getComponentVector<ST::LightComponent>();
	auto& transformComps = *gm.getComponentVector<ST::TransformComponent>();
	auto& renderComps = *gm.getComponentVector<ST::RenderComponent>();

	lights_.clear();
	gm.shadowMapping->use();

	for (int n = 0; n < lightComps.size(); n++) {
		if (lightComps.at(n).has_value() && transformComps.at(n).has_value() && gm.mainCameraID() >= 0) {

			//gm.shadowMapping->use(); // Active Program

			ST::TransformComponent& tempTransform = transformComps.at(n).value();

			LightsStruct tempLightData;
			tempLightData.light_ = &lightComps.at(n).value();
			tempLightData.light_->position_ = tempTransform.getPosition();
			//tempLightData.light_->direction_ = -tempTransform.getUp();
			tempLightData.light_->direction_ = tempTransform.getForward();
			
			auto cameraTransform = gm.getComponent<ST::TransformComponent>(gm.mainCameraID());

			if (!cameraTransform) { exit; }

			if (tempLightData.light_->type_ == ST::Directional) {

				glm::mat4 view = lookAt(cameraTransform->getPosition() + 20.0f * -tempLightData.light_->direction_, cameraTransform->getPosition() + glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				//glm::mat4 view = lookAt(cameraTransform->getPosition() + 20.0f * -tempLightData.light_->direction_, cameraTransform->getPosition() + glm::vec3(0.0f, 0.0f, 0.0f), cameraTransform->getUp());

				// ----- Hight Res Shadow -----
				glm::mat4 orthoHigh = glm::ortho(-tempLightData.light_->shadowHighRadius_, tempLightData.light_->shadowHighRadius_,
												-tempLightData.light_->shadowHighRadius_, tempLightData.light_->shadowHighRadius_,
												-tempLightData.light_->shadowHighRadius_, tempLightData.light_->shadowHighRadius_);
				tempLightData.light_->matrixlighShadowHigh_ = (orthoHigh * view);
				glUniformMatrix4fv(gm.shadowMapping->getUniform("u_lightSpaceMatrix"), 1, GL_FALSE, &tempLightData.light_->matrixlighShadowHigh_[0][0]);
				//Render Scene.
				tempLightData.light_->shadowHigh->start();
				setUpRender(gm);
				tempLightData.light_->shadowHigh->end();

				// ----- Mid Res Shadow -----
				glm::mat4 orthoMedium = glm::ortho(-tempLightData.light_->shadowMediumRadius_, tempLightData.light_->shadowMediumRadius_,
													-tempLightData.light_->shadowMediumRadius_, tempLightData.light_->shadowMediumRadius_,
													-tempLightData.light_->shadowMediumRadius_, tempLightData.light_->shadowMediumRadius_);
				tempLightData.light_->matrixlighShadowMedium_ = (orthoMedium * view);
				glUniformMatrix4fv(gm.shadowMapping->getUniform("u_lightSpaceMatrix"), 1, GL_FALSE, &tempLightData.light_->matrixlighShadowMedium_[0][0]);
				//Render Scene.
				tempLightData.light_->shadowMedium->start();
				setUpRender(gm);
				tempLightData.light_->shadowMedium->end();

				// ----- Low Res Shadow -----
				glm::mat4 orthoLow = glm::ortho(-tempLightData.light_->shadowLowRadius_, tempLightData.light_->shadowLowRadius_,
												-tempLightData.light_->shadowLowRadius_, tempLightData.light_->shadowLowRadius_,
												-tempLightData.light_->shadowLowRadius_, tempLightData.light_->shadowLowRadius_);
				tempLightData.light_->matrixlighShadowLow_ = (orthoLow * view);
				glUniformMatrix4fv(gm.shadowMapping->getUniform("u_lightSpaceMatrix"), 1, GL_FALSE, &tempLightData.light_->matrixlighShadowLow_[0][0]);
				//Render Scene.
				tempLightData.light_->shadowLow->start();
				setUpRender(gm);
				tempLightData.light_->shadowLow->end();

			}
			else if (tempLightData.light_->type_ == ST::Point) {

				if (gm.mainCameraID() != -1) {
					tempTransform.m_transform_ = glm::lookAt(tempTransform.getPosition(), transformComps.at(gm.mainCameraID())->getPosition(), glm::vec3(0.0f, 1.0f, 0.0f));
					tempTransform.m_transform_ = glm::inverse(tempTransform.m_transform_);
				}
				if (renderComps.at(n).has_value()) {
					renderComps.at(n).value().material.setColor(tempLightData.light_->color_.x, tempLightData.light_->color_.y, tempLightData.light_->color_.z);
				}

				/*ST::ShadowMapping pointLightShadow;
				pointLightShadow.setUp(textureSize_.x, textureSize_.y, ST::Texture::T_CUBEMAP);
				
				glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), 1.0f, 1.0f, 25.0f);

				std::vector<glm::mat4> shadowTransforms;
				shadowTransforms.push_back(shadowProj * glm::lookAt(tempTransform.getPosition(), tempTransform.getPosition() + glm::vec3(1, 0, 0), glm::vec3(0, -1, 0)));
				shadowTransforms.push_back(shadowProj * glm::lookAt(tempTransform.getPosition(), tempTransform.getPosition() + glm::vec3(-1, 0, 0), glm::vec3(0, -1, 0)));
				shadowTransforms.push_back(shadowProj * glm::lookAt(tempTransform.getPosition(), tempTransform.getPosition() + glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)));
				shadowTransforms.push_back(shadowProj * glm::lookAt(tempTransform.getPosition(), tempTransform.getPosition() + glm::vec3(0, -1, 0), glm::vec3(0, 0, -1)));
				shadowTransforms.push_back(shadowProj * glm::lookAt(tempTransform.getPosition(), tempTransform.getPosition() + glm::vec3(0, 0, 1), glm::vec3(0, -1, 0)));
				shadowTransforms.push_back(shadowProj * glm::lookAt(tempTransform.getPosition(), tempTransform.getPosition() + glm::vec3(0, 0, -1), glm::vec3(0, -1, 0)));

				gm.shadowMappingPoint->use();

				char buffer[50];
				for (unsigned int i = 0; i < 6; ++i) {
					tempLightData.matrix_.push_back(shadowTransforms[i]);
					snprintf(buffer, 50, "lightSpaceMatrix[%d]", i);
					glUniformMatrix4fv(gm.shadowMapping->getUniform(buffer), 1, GL_FALSE, &shadowTransforms[i][0][0]);
				}
				glUniform1f(gm.shadowMapping->getUniform("far_plane"), 25.0f);
				glm::vec3 lightPos = tempTransform.getPosition();
				glUniform3fv(gm.shadowMapping->getUniform("lightPos"), 1, &lightPos.x);

				pointLightShadow.start();
				setUpRender(gm);
				pointLightShadow.end();

				tempLightData.renderTarget_.push_back(pointLightShadow);*/
			}
			else if (tempLightData.light_->type_ == ST::Spot) {
				
				if (gm.mainCameraID() != -1) {
					tempTransform.m_transform_ = glm::lookAt(tempTransform.getPosition(), transformComps.at(gm.mainCameraID())->getPosition(), glm::vec3(0.0f, 1.0f, 0.0f));
					tempTransform.m_transform_ = glm::inverse(tempTransform.m_transform_);
				}
				if (renderComps.at(n).has_value()) {
					renderComps.at(n).value().material.setColor(tempLightData.light_->color_.x, tempLightData.light_->color_.y, tempLightData.light_->color_.z);
				}

				ST::CameraComponent cam;				
				cam.setPerspective(120.0f, 1.0f, 1.0f, 100.0f);
				cam.lookAt(tempLightData.light_->position_, tempLightData.light_->position_ + tempTransform.getForward(), tempTransform.getUp());

				tempLightData.light_->matrixlighShadowHigh_ = (cam.projection * cam.view);
				glUniformMatrix4fv(gm.shadowMapping->getUniform("u_lightSpaceMatrix"), 1, GL_FALSE, &tempLightData.light_->matrixlighShadowHigh_[0][0]);

				//Render Scene.
				tempLightData.light_->shadowHigh->start();
				setUpRender(gm);
				tempLightData.light_->shadowHigh->end();
			}

			lights_.push_back(tempLightData);
		}
	}

}

void ST::SystemLight::setUpRender(ST::GameObj_Manager& gm){
	auto& render = *gm.getComponentVector<ST::RenderComponent>();
	auto& transform = *gm.getComponentVector<ST::TransformComponent>();
	
	std::vector<Light_MyObjToRender> objs_opaque;

	for (int i = 0; i < render.size(); i++) {

		if (render[i].has_value() && render[i]->mesh && transform[i].has_value()) {
			if (render[i]->visible_ && render[i]->castShadow_) {
				Light_MyObjToRender thisObj;
				thisObj.render_ = &render[i].value();
				thisObj.transform_ = &transform[i].value();

				objs_opaque.push_back(thisObj);
			}
		}
	}
	
	glDisable(GL_BLEND);
	doRender(objs_opaque);

	objs_opaque.clear();
}

void ST::SystemLight::doRender(std::vector<Light_MyObjToRender>& objs){
	std::vector<InstanceInfo> instancing;

	GLuint actualMeshRendering = 0;

	int lastIndice = 0;
	bool firstTime = true;

	bool popInstances = false;

	for (int i = 0; i < objs.size(); i++) {

		if (firstTime) {
			actualMeshRendering = objs[i].render_->mesh->getID();
			firstTime = false;
		}

		// Si tienen una mesh distinta.
		if (objs[i].render_->mesh->getID() != actualMeshRendering) {
			popInstances = true;
			actualMeshRendering = objs[i].render_->mesh->getID();
		}

		if (popInstances) {
			objs[lastIndice].render_->mesh->cullmode_ = kCull_Back;
			objs[lastIndice].render_->mesh->depthmode_ = kDepth_LessEqual;
			assert(glGetError() == GL_NO_ERROR);
			objs[lastIndice].render_->mesh->setInstanceData(instancing);
			objs[lastIndice].render_->mesh->render();
			assert(glGetError() == GL_NO_ERROR);
			instancing.clear();

			popInstances = false;
		}

		instancing.push_back({ objs[i].transform_->m_transform_,
							   objs[i].render_->material.getColor(),
							   objs[i].render_->material.getTexIndex(),
							   objs[i].render_->material.roughness_,
							   objs[i].render_->material.metallic_ });
		lastIndice = i;

	}// End For

	// Para pintar los ultimos objetos iguales.
	if (instancing.size() > 0) {
		objs[lastIndice].render_->mesh->cullmode_ = kCull_Back;
		objs[lastIndice].render_->mesh->depthmode_ = kDepth_LessEqual;
		objs[lastIndice].render_->mesh->setInstanceData(instancing);
		objs[lastIndice].render_->mesh->render();
		instancing.clear();
	}
}

ST::SystemLight::~SystemLight(){

}
