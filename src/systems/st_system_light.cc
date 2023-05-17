#include "st_system_light.h"

#include <st_gameobj_manager.h>
#include <components/st_light.h>
#include <components/st_render.h>
#include <components/st_transform.h>

#include <components/st_camera.h>

#include <st_program.h>

ST::SystemLight::SystemLight(){
	textureSize_ = glm::ivec2(2048);
}

//void ST::SystemLight::CompileLights(ST::GameObj_Manager& gm, ST::Program& thisProgram){
//
//	auto& lightComps = *gm.getComponentVector<ST::LightComponent>();
//	auto& renderComps = *gm.getComponentVector<ST::RenderComponent>();
//	auto& transformComps = *gm.getComponentVector<ST::TransformComponent>();
//
//	char buffer[50];
//
//	thisProgram.use();
//
//	int countDirectionalLights = 0;
//	int countPointLights = 0;
//	int countSpotLights = 0;
//
//	GLint idUniform = -1;
//
//	for (int n = 0; n < lightComps.size(); n++) {
//		if (lightComps.at(n).has_value()) {
//			ST::LightComponent thisLight = lightComps.at(n).value();
//
//			// ---- Lights ----
//
//			glm::vec3 dirLight(0.0f,-1.0f,0.0f);
//
//			if (transformComps.at(n).has_value()) {
//				dirLight = -transformComps.at(n)->getUp();
//				if (gm.mainCameraID() != -1) {
//					transformComps.at(n)->m_transform_ = glm::lookAt(transformComps.at(n)->getPosition(), transformComps.at(gm.mainCameraID())->getPosition(), glm::vec3(0.0f,1.0f,0.0f));
//					transformComps.at(n)->m_transform_ = glm::inverse(transformComps.at(n)->m_transform_);
//				}
//				//thisLight.dirLight_.x = sinf(transformComps->at(n).value().getRotation().x);
//				//thisLight.dirLight_.y = sinf(transformComps->at(n).value().getRotation().y);
//				//thisLight.dirLight_.z = sinf(transformComps->at(n).value().getRotation().z);
//			}
//
//			if (thisLight.type_ == ST::Directional) {
//				/*
//
//				Creamos una camara (CameraComponent) en orthografic, para saber lo que ve la camara.
//
//				*/
//				//ST::CameraComponent cam;
//
//				snprintf(buffer, 50, "u_DirectLight[%d].direction", countDirectionalLights);
//				idUniform = thisProgram.getUniform(buffer);
//				glUniform3f(idUniform, dirLight.x, dirLight.y, dirLight.z);
//
//				snprintf(buffer, 50, "u_DirectLight[%d].ambient", countDirectionalLights);
//				idUniform = thisProgram.getUniform(buffer);
//				glUniform3f(idUniform, thisLight.ambient_.x, thisLight.ambient_.y, thisLight.ambient_.z);
//
//				snprintf(buffer, 50, "u_DirectLight[%d].diffuse", countDirectionalLights);
//				idUniform = thisProgram.getUniform(buffer);
//				glUniform3f(idUniform, thisLight.diffuse_.x, thisLight.diffuse_.y, thisLight.diffuse_.z);
//
//				snprintf(buffer, 50, "u_DirectLight[%d].specular", countDirectionalLights);
//				idUniform = thisProgram.getUniform(buffer);
//				glUniform3f(idUniform, thisLight.specular_.x, thisLight.specular_.y, thisLight.specular_.z);
//
//				countDirectionalLights++;
//
//			} else if (thisLight.type_ == ST::Point) {
//
//				snprintf(buffer, 50, "u_PointLight[%d].position", countPointLights);
//				idUniform = thisProgram.getUniform(buffer);
//				glUniform3f(idUniform, transformComps.at(n).value().getPosition().x, transformComps.at(n).value().getPosition().y, transformComps.at(n).value().getPosition().z);
//
//				snprintf(buffer, 50, "u_PointLight[%d].ambient", countPointLights);
//				idUniform = thisProgram.getUniform(buffer);
//				glUniform3f(idUniform, thisLight.color_.x, thisLight.color_.y, thisLight.color_.z);
//
//				snprintf(buffer, 50, "u_PointLight[%d].diffuse", countPointLights);
//				idUniform = thisProgram.getUniform(buffer);
//				glUniform3f(idUniform, thisLight.color_.x, thisLight.color_.y, thisLight.color_.z);
//
//				snprintf(buffer, 50, "u_PointLight[%d].specular", countPointLights);
//				idUniform = thisProgram.getUniform(buffer);
//				glUniform3f(idUniform, thisLight.color_.x, thisLight.color_.y, thisLight.color_.z);
//
//				snprintf(buffer, 50, "u_PointLight[%d].constant", countPointLights);
//				idUniform = thisProgram.getUniform(buffer);
//				glUniform1f(idUniform, thisLight.constant_);
//
//				snprintf(buffer, 50, "u_PointLight[%d].linear", countPointLights);
//				idUniform = thisProgram.getUniform(buffer);
//				glUniform1f(idUniform, thisLight.linear_);
//
//				snprintf(buffer, 50, "u_PointLight[%d].quadratic", countPointLights);
//				idUniform = thisProgram.getUniform(buffer);
//				glUniform1f(idUniform, thisLight.quadratic_);
//
//				countPointLights++;
//
//			} else if (thisLight.type_ == ST::Spot){
//
//				snprintf(buffer, 50, "u_SpotLight[%d].position", countSpotLights);
//				idUniform = thisProgram.getUniform(buffer);
//				glUniform3f(idUniform, transformComps.at(n).value().getPosition().x, transformComps.at(n).value().getPosition().y, transformComps.at(n).value().getPosition().z);
//
//				snprintf(buffer, 50, "u_SpotLight[%d].ambient", countSpotLights);
//				idUniform = thisProgram.getUniform(buffer);
//				glUniform3f(idUniform, thisLight.color_.x, thisLight.color_.y, thisLight.color_.z);
//
//				snprintf(buffer, 50, "u_SpotLight[%d].diffuse", countSpotLights);
//				idUniform = thisProgram.getUniform(buffer);
//				glUniform3f(idUniform, thisLight.color_.x, thisLight.color_.y, thisLight.color_.z);
//
//				snprintf(buffer, 50, "u_SpotLight[%d].specular", countSpotLights);
//				idUniform = thisProgram.getUniform(buffer);
//				glUniform3f(idUniform, thisLight.color_.x, thisLight.color_.y, thisLight.color_.z);
//
//				snprintf(buffer, 50, "u_SpotLight[%d].constant", countSpotLights);
//				idUniform = thisProgram.getUniform(buffer);
//				glUniform1f(idUniform, thisLight.constant_);
//
//				snprintf(buffer, 50, "u_SpotLight[%d].linear", countSpotLights);
//				idUniform = thisProgram.getUniform(buffer);
//				glUniform1f(idUniform, thisLight.linear_);
//
//				snprintf(buffer, 50, "u_SpotLight[%d].quadratic", countSpotLights);
//				idUniform = thisProgram.getUniform(buffer);
//				glUniform1f(idUniform, thisLight.quadratic_);
//
//				snprintf(buffer, 50, "u_SpotLight[%d].direction", countSpotLights);
//				idUniform = thisProgram.getUniform(buffer);
//				glUniform3f(idUniform, transformComps.at(n).value().getRotation().x, transformComps.at(n).value().getRotation().y, transformComps.at(n).value().getRotation().z);
//
//				snprintf(buffer, 50, "u_SpotLight[%d].cutOff", countSpotLights);
//				idUniform = thisProgram.getUniform(buffer);
//				glUniform1f(idUniform, thisLight.cutOff_);
//
//				snprintf(buffer, 50, "u_SpotLight[%d].outerCutOff", countSpotLights);
//				idUniform = thisProgram.getUniform(buffer);
//				glUniform1f(idUniform, thisLight.outerCutOff_);
//
//				countSpotLights++;
//			}
//
//			if (renderComps.at(n).has_value()) {
//				renderComps.at(n).value().material.setColor(thisLight.color_.x, thisLight.color_.y, thisLight.color_.z);
//			}
//
//		} // if Have Light
//	} // For Lights
//	
//	idUniform = thisProgram.getUniform("u_numDirectLights");
//	glUniform1i(idUniform, countDirectionalLights);
//
//	idUniform = thisProgram.getUniform("u_numPointLights");
//	glUniform1i(idUniform, countPointLights);
//
//	idUniform = thisProgram.getUniform("u_numSpotLights");
//	glUniform1i(idUniform, countSpotLights);
//
//	// Shadow Mapping
//	//if (shadowMaps_.size() > 0) {
//	//	glUniform1i(thisProgram.getUniform("u_haveShadowMap"), true);
//
//	//	glUniform1i(thisProgram.getUniform("shadowMap"), 3);
//	//	glActiveTexture(GL_TEXTURE0 + 3);
//	//	glBindTexture(GL_TEXTURE_2D, shadowMaps_[0].renderTarget_[0].textureID()); // <------- REVISAR
//
//	//	GLuint lighSpaceMatrix = thisProgram.getUniform("lightSpaceMatrix");
//	//	glUniformMatrix4fv(lighSpaceMatrix, 1, GL_FALSE, &shadowMaps_[0].matrix_[0][0]);
//	//}else {
//	//	glUniform1i(thisProgram.getUniform("u_haveShadowMap"), false);
//	//}
//
//	//glUseProgram(0);
//}

void ST::SystemLight::CompileLights(ST::GameObj_Manager& gm) {

	auto& lightComps = *gm.getComponentVector<ST::LightComponent>();
	auto& transformComps = *gm.getComponentVector<ST::TransformComponent>();
	auto& renderComps = *gm.getComponentVector<ST::RenderComponent>();
	
	//static glm::vec2 camShadowSize = glm::vec2(100.0f, 100.0f);
	//static glm::vec2 camShadowDistance = glm::vec2(-20.0f, 100.0f); // Temporal <-------------------

	lights_.clear();
	gm.shadowMapping->use();

	for (int n = 0; n < lightComps.size(); n++) {
		if (lightComps.at(n).has_value() && transformComps.at(n).has_value()) {

			//gm.shadowMapping->use(); // Active Program

			ST::TransformComponent& tempTransform = transformComps.at(n).value();

			LightsStruct tempLightData;
			tempLightData.light_ = &lightComps.at(n).value();
			tempLightData.light_->position_ = tempTransform.getPosition();
			//tempLightData.light_->direction_ = -tempTransform.getUp();
			tempLightData.light_->direction_ = tempTransform.getForward();
			
			auto cameraTransform = gm.getComponent<ST::TransformComponent>(gm.mainCameraID());

			if (tempLightData.light_->type_ == ST::Directional) {
				ST::ShadowMapping thisLightRenderTargetHigh;
				thisLightRenderTargetHigh.setUp(textureSize_.x, textureSize_.y);
				ST::ShadowMapping thisLightRenderTargetMid;
				thisLightRenderTargetMid.setUp(textureSize_.x, textureSize_.y);		

				//glm::mat4 view = lookAt(cameraTransform->getPosition() + 20.0f * -tempLightData.light_->direction_, cameraTransform->getPosition() + glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				glm::mat4 view = lookAt(cameraTransform->getPosition() + 20.0f * -tempLightData.light_->direction_, cameraTransform->getPosition() + glm::vec3(0.0f, 0.0f, 0.0f), cameraTransform->getUp());

				// ----- Hight Res Shadow -----
				glm::mat4 orthoHigh = glm::ortho(-35.0f, 35.0f, -35.0f, 35.0f, -35.0f, 35.0f);
				tempLightData.matrix_.push_back(orthoHigh * view);
				glUniformMatrix4fv(gm.shadowMapping->getUniform("u_lightSpaceMatrix"), 1, GL_FALSE, &tempLightData.matrix_[0][0][0]);
				//Render Scene.
				thisLightRenderTargetHigh.start();
				setUpRender(gm);
				thisLightRenderTargetHigh.end();
				tempLightData.renderTarget_.push_back(thisLightRenderTargetHigh);

				// ----- Mid Res Shadow -----
				glm::mat4 orthoMid = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, -30.0f, 170.0f);
				tempLightData.matrix_.push_back(orthoMid * view);
				glUniformMatrix4fv(gm.shadowMapping->getUniform("u_lightSpaceMatrix"), 1, GL_FALSE, &tempLightData.matrix_[1][0][0]);
				//Render Scene.
				thisLightRenderTargetMid.start();
				setUpRender(gm);
				thisLightRenderTargetMid.end();
				tempLightData.renderTarget_.push_back(thisLightRenderTargetMid);

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
			

				//ST::ShadowMapping pointShadowForward;
				//pointShadowForward.setUp(textureSize_.x, textureSize_.y);
				//tempLightData.renderTarget_.emplace_back(pointShadowForward);

				//ST::ShadowMapping pointShadowBackward;
				//pointShadowBackward.setUp(textureSize_.x, textureSize_.y);
				//tempLightData.renderTarget_.emplace_back(pointShadowBackward);

				//ST::ShadowMapping pointShadowBottom;
				//pointShadowBottom.setUp(textureSize_.x, textureSize_.y);
				//tempLightData.renderTarget_.emplace_back(pointShadowBottom);

				//ST::ShadowMapping pointShadowUp;
				//pointShadowUp.setUp(textureSize_.x, textureSize_.y);
				//tempLightData.renderTarget_.emplace_back(pointShadowUp);

				//ST::ShadowMapping pointShadowRight;
				//pointShadowRight.setUp(textureSize_.x, textureSize_.y);
				//tempLightData.renderTarget_.emplace_back(pointShadowRight);

				//ST::ShadowMapping pointShadowLeft;
				//pointShadowLeft.setUp(textureSize_.x, textureSize_.y);
				//tempLightData.renderTarget_.emplace_back(pointShadowLeft);

				//glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), 1.0f, 1.0f, 25.0f);
				//tempLightData.matrix_.push_back(shadowProj * glm::lookAt(tempTransform.getPosition(), tempTransform.getPosition() + glm::vec3(1, 0, 0), glm::vec3(0, -1, 0)));
				//tempLightData.matrix_.push_back(shadowProj * glm::lookAt(tempTransform.getPosition(), tempTransform.getPosition() + glm::vec3(-1, 0, 0), glm::vec3(0, -1, 0)));
				//tempLightData.matrix_.push_back(shadowProj * glm::lookAt(tempTransform.getPosition(), tempTransform.getPosition() + glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)));
				//tempLightData.matrix_.push_back(shadowProj * glm::lookAt(tempTransform.getPosition(), tempTransform.getPosition() + glm::vec3(0, -1, 0), glm::vec3(0, 0, -1)));
				//tempLightData.matrix_.push_back(shadowProj * glm::lookAt(tempTransform.getPosition(), tempTransform.getPosition() + glm::vec3(0, 0, 1), glm::vec3(0, -1, 0)));
				//tempLightData.matrix_.push_back(shadowProj * glm::lookAt(tempTransform.getPosition(), tempTransform.getPosition() + glm::vec3(0, 0, -1), glm::vec3(0, -1, 0)));

				//for (unsigned int i = 0; i < tempLightData.renderTarget_.size(); ++i) {
				//	glUniformMatrix4fv(gm.shadowMapping->getUniform("u_lightSpaceMatrix"), 1, GL_FALSE, &tempLightData.matrix_[i][0][0]);

				//	//Render Scene.
				//	tempLightData.renderTarget_[i].start();
				//	setUpRender(gm);
				//	tempLightData.renderTarget_[i].end();
				//}

			}
			else if (tempLightData.light_->type_ == ST::Spot) {
				
				if (gm.mainCameraID() != -1) {
					tempTransform.m_transform_ = glm::lookAt(tempTransform.getPosition(), transformComps.at(gm.mainCameraID())->getPosition(), glm::vec3(0.0f, 1.0f, 0.0f));
					tempTransform.m_transform_ = glm::inverse(tempTransform.m_transform_);
				}
				if (renderComps.at(n).has_value()) {
					renderComps.at(n).value().material.setColor(tempLightData.light_->color_.x, tempLightData.light_->color_.y, tempLightData.light_->color_.z);
				}
				
				ST::ShadowMapping spotLightShadow;
				spotLightShadow.setUp(textureSize_.x, textureSize_.y);

				ST::CameraComponent cam;
				
				cam.setPerspective(120.0f, 1.0f, 1.0f, 100.0f);
				cam.lookAt(tempLightData.light_->position_, tempLightData.light_->position_ + tempTransform.getForward(), tempTransform.getUp());

				tempLightData.matrix_.push_back(cam.projection * cam.view);

				glUniformMatrix4fv(gm.shadowMapping->getUniform("u_lightSpaceMatrix"), 1, GL_FALSE, &tempLightData.matrix_[0][0][0]);

				//Render Scene.
				spotLightShadow.start();
				setUpRender(gm);
				spotLightShadow.end();

				tempLightData.renderTarget_.push_back(spotLightShadow);
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

		if (render[i].has_value() && transform[i].has_value()) {
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

	/*GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("Post DoRender-> OpenGL Error: %d\n", error);
	}*/

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
