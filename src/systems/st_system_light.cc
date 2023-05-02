#include "st_system_light.h"

#include <st_gameobj_manager.h>
#include <components/st_light.h>
#include <components/st_render.h>
#include <components/st_transform.h>

#include <components/st_camera.h>

#include <st_program.h>

ST::SystemLight::SystemLight(){
	textureSize_ = glm::ivec2(1024);
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
	
	static glm::vec2 camShadowSize = glm::vec2(100.0f, 100.0f);
	static glm::vec2 camShadowDistance = glm::vec2(-30.0f, 30.0f); // Temporal <-------------------

	lights_.clear();
	gm.shadowMapping->use(); // ????????????????????

	for (int n = 0; n < lightComps.size(); n++) {
		if (lightComps.at(n).has_value() && transformComps.at(n).has_value()) {

			ST::TransformComponent tempTransform = transformComps.at(n).value();

			LightsStruct tempLightData;
			tempLightData.light_ = &lightComps.at(n).value();
			tempLightData.light_->position_ = tempTransform.getPosition();
			tempLightData.light_->direction_ = -tempTransform.getUp();
			tempLightData.matrix_ = tempTransform.m_transform_;
			
			if (tempLightData.light_->type_ == ST::Directional) {
				ST::ShadowMapping thisLightRenderTargetHigh;
				thisLightRenderTargetHigh.setUp(textureSize_.x, textureSize_.y);
				//thisLightRenderTarget.addTexture(textureSize_.x, textureSize_.y, "ShadowMap", ST::Texture::F_DEPTH, ST::Texture::DT_FLOAT);

				// Coger posicion camara + forward de la camara -> transformComps[gm.mainCameraID()] esto seria el "target" de la view
				// lookAt ("target" - forwad de la luz, el "target", el up de la camara)
				ST::CameraComponent cam;

				/*glm::vec3 target = transformComps[gm.mainCameraID()]->getPosition() + transformComps[gm.mainCameraID()]->getForward();
				cam.lookAt(target - tempTransform.getForward(), target, tempTransform.getUp());*/

				//glm::vec3 target = transformComps[gm.mainCameraID()]->getPosition() + transformComps[gm.mainCameraID()]->getForward() * 10.0f;
				//cam.lookAt(target - tempTransform.getForward(), target, transformComps[gm.mainCameraID()]->getUp());

				//cam.lookAt(thisTrans.getPosition(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // <-- Temporalmente este en uso.
				// Jugar de alguna forma con la posicion de la camara principal y la directional, para que nos siga,
				// luego con que la direccion sea su direccion habitual, no el look at.
				cam.lookAt(tempTransform.getPosition(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				cam.setOrthographic(camShadowSize.x, camShadowSize.y, camShadowDistance.x, camShadowDistance.y);

				// La rotacion no da un efecto correcto.
				//if (transformComps[gm.mainCameraID()].has_value()) {
				//	//tempTransform.RotateY(-3.1415f);
				//	//tempTransform.RotateX(3.1415f);
				//	//tempTransform.m_Rotation_ = glm::mat4(1.0f);
				//	//tempTransform.m_Rotation_ = glm::rotate(tempTransform.m_Rotation_, tempTransform.getRotation().x, { 1.0f,0.0f,0.0f });
				//	//tempTransform.m_Rotation_ = glm::rotate(tempTransform.m_Rotation_, tempTransform.getRotation().y, { 0.0f,1.0f,0.0f });
				//	//tempTransform.m_Rotation_ = glm::rotate(tempTransform.m_Rotation_, tempTransform.getRotation().z, { 0.0f,0.0f,1.0f });
				//	tempMat = tempTransform.m_Rotation_ * transformComps[gm.mainCameraID()].value().m_Position_;
				//}
				//else {
				//	tempMat = tempTransform.m_Rotation_;
				//}

				//tempMat *= glm::rotate(90.0f, glm::vec3(0.0f,0.0f,1.0f));
				//tempLightData.matrix_ = cam.projection * tempMat;
				tempLightData.matrix_ = cam.projection * cam.view;

				glUniformMatrix4fv(gm.shadowMapping->getUniform("lightSpaceMatrix"), 1, GL_FALSE, &tempLightData.matrix_[0][0]);

				//Render Scene.
				thisLightRenderTargetHigh.start();
				//glCullFace(GL_FRONT); // <--- Test
				glDisable(GL_CULL_FACE);
				setUpRender(gm);
				glEnable(GL_CULL_FACE);
				glCullFace(GL_BACK); // <--- Test
				thisLightRenderTargetHigh.end();

				tempLightData.renderTarget_.push_back(thisLightRenderTargetHigh);
				//shadowMapsLocal.push_back(thisLightShadow);

				//ImGui::Begin("ViewDepth");
				////ImGui::DragInt("View", &indexView, 1.0f, 0, shadowMaps_.size() - 1);
				////if (indexView >= shadowMapsLocal.size()) { indexView = shadowMapsLocal.size() - 1; }
				//ImGui::Image((void*)(intptr_t)tempLightData.renderTarget_[0].textureID(), ImVec2(192, 120));
				//ImGui::SetNextItemWidth(50.0f);
				//ImGui::DragFloat("Horizontal", &camShadowSize.x); ImGui::SameLine();
				//ImGui::SetNextItemWidth(50.0f);
				//ImGui::DragFloat("Vertical", &camShadowSize.y);
				//ImGui::SetNextItemWidth(50.0f);
				//ImGui::DragFloat("Near", &camShadowDistance.x); ImGui::SameLine();
				//ImGui::SetNextItemWidth(50.0f);
				//ImGui::DragFloat("Far", &camShadowDistance.y);
				//ImGui::SetNextItemWidth(50.0f);
				//ImGui::DragInt("Texture Witdh", &textureSize_.x); ImGui::SameLine();
				//ImGui::SetNextItemWidth(50.0f);
				//ImGui::DragInt("Texture Height", &textureSize_.y);
				//ImGui::End();
			}
			else if (tempLightData.light_->type_ == ST::Point) {
				/*for (unsigned int i = 0; i < 6; i++){

					GLenum face = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;

					ST::ShadowMapping thisLightRenderTargetHigh;
					thisLightRenderTargetHigh.setUp(textureSize_.x, textureSize_.y, face);
				}*/
			}
			else if (tempLightData.light_->type_ == ST::Spot) {
				ST::ShadowMapping spotLightShadow;
				spotLightShadow.setUp(textureSize_.x, textureSize_.y);

				ST::CameraComponent cam;
				cam.lookAt(tempLightData.light_->position_, tempLightData.light_->position_ + tempTransform.getForward(), glm::vec3(0.0f, 1.0f, 0.0f));
				cam.setPerspective(90.0f, 1.0f, camShadowDistance.x, camShadowDistance.y);

				tempLightData.matrix_ = cam.projection * cam.view;

				glUniformMatrix4fv(gm.shadowMapping->getUniform("lightSpaceMatrix"), 1, GL_FALSE, &tempLightData.matrix_[0][0]);

				//Render Scene.
				spotLightShadow.start();
				//glCullFace(GL_FRONT); // <--- Test
				glDisable(GL_CULL_FACE);
				setUpRender(gm);
				glEnable(GL_CULL_FACE);
				glCullFace(GL_BACK); // <--- Test
				spotLightShadow.end();

				tempLightData.renderTarget_.push_back(spotLightShadow);

				//ImGui::Begin("ViewDepth");
				////ImGui::DragInt("View", &indexView, 1.0f, 0, shadowMaps_.size() - 1);
				////if (indexView >= shadowMapsLocal.size()) { indexView = shadowMapsLocal.size() - 1; }
				//ImGui::Image((void*)(intptr_t)tempLightData.renderTarget_[0].textureID(), ImVec2(192, 120));
				//ImGui::SetNextItemWidth(50.0f);
				//ImGui::DragFloat("Horizontal", &camShadowSize.x); ImGui::SameLine();
				//ImGui::SetNextItemWidth(50.0f);
				//ImGui::DragFloat("Vertical", &camShadowSize.y);
				//ImGui::SetNextItemWidth(50.0f);
				//ImGui::DragFloat("Near", &camShadowDistance.x); ImGui::SameLine();
				//ImGui::SetNextItemWidth(50.0f);
				//ImGui::DragFloat("Far", &camShadowDistance.y);
				//ImGui::SetNextItemWidth(50.0f);
				//ImGui::DragInt("Texture Witdh", &textureSize_.x); ImGui::SameLine();
				//ImGui::SetNextItemWidth(50.0f);
				//ImGui::DragInt("Texture Height", &textureSize_.y);
				//ImGui::End();
			}

			lights_.push_back(tempLightData);
		}
	}

}


void ST::SystemLight::CompileShadows(ST::GameObj_Manager& gm){

	auto& lightComps = *gm.getComponentVector<ST::LightComponent>();
	auto& transformComps = *gm.getComponentVector<ST::TransformComponent>();

	gm.shadowMapping->use(); // El Program, seguramente sacarlo del RenderSystem.

	int countDirectionalLights = 0;
	int countPointLights = 0;
	int countSpotLights = 0;

	GLint idUniform = -1;

	static glm::vec2 camShadowSize = glm::vec2(20.0f,20.0f);
	static glm::vec2 camShadowDistance = glm::vec2(-30.0f, 30.0f);

	//std::vector<Light_ShadowMap> shadowMapsLocal;
	//shadowMaps_.clear();

	//for (int n = 0; n < lightComps.size(); n++) {
	//	if (lightComps.at(n).has_value() && transformComps.at(n).has_value()) {
	//		ST::LightComponent thisLight = lightComps.at(n).value();
	//		ST::TransformComponent thisTrans = transformComps.at(n).value();

	//		if (thisLight.type_ == ST::Directional) {

	//			Light_ShadowMap thisLightShadow;
	//			ST::ShadowMapping thisLightRenderTarget;
	//			thisLightRenderTarget.setUp(textureSize_.x, textureSize_.y);
	//			//thisLightRenderTarget.addTexture(textureSize_.x, textureSize_.y, "ShadowMap", ST::Texture::F_DEPTH, ST::Texture::DT_FLOAT);
	//			
	//			ST::CameraComponent cam;
	//			//cam.lookAt(thisTrans.getPosition(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // <-- Temporalmente este en uso.
	//			// Jugar de alguna forma con la posicion de la camara principal y la directional, para que nos siga,
	//			// luego con que la direccion sea su direccion habitual, no el look at.
	//			//cam.lookAt(thisTrans.getPosition(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//			cam.setOrthographic(camShadowSize.x, camShadowSize.y, camShadowDistance.x, camShadowDistance.y);
	//			
	//			glm::mat4 tempMat(1.0); // la view que sacaria con el LookAt.

	//			if (transformComps[gm.mainCameraID()].has_value()) {
	//				tempMat = thisTrans.m_Rotation_ * transformComps[gm.mainCameraID()].value().m_Position_;
	//			}else {
	//				tempMat = thisTrans.m_Rotation_;
	//			}
	//			
	//			//tempMat *= glm::rotate(90.0f, glm::vec3(0.0f,0.0f,1.0f));
	//			thisLightShadow.matrix_ = cam.projection * tempMat;


	//			idUniform = gm.shadowMapping->getUniform("lightSpaceMatrix");
	//			glUniformMatrix4fv(idUniform, 1, GL_FALSE, &thisLightShadow.matrix_[0][0]);

	//			//Render Scene.
	//			thisLightRenderTarget.start();
	//			//glCullFace(GL_FRONT); // <--- Test
	//			glDisable(GL_CULL_FACE);
	//			setUpRender(gm);
	//			glEnable(GL_CULL_FACE);
	//			glCullFace(GL_BACK); // <--- Test
	//			thisLightRenderTarget.end();


	//			thisLightShadow.renderTarget_.push_back(thisLightRenderTarget);
	//			shadowMapsLocal.push_back(thisLightShadow);
	//		}
	//	}
	//}
	//static int indexView = 0;
	//
	//shadowMaps_ = shadowMapsLocal;
	//if (shadowMaps_.size() > 0) {
	//	ImGui::Begin("ViewDepth");
	//	ImGui::DragInt("View", &indexView, 1.0f, 0, shadowMaps_.size()-1);
	//	if (indexView >= shadowMapsLocal.size()) { indexView = shadowMapsLocal.size() - 1; }
	//	ImGui::Image((void*)(intptr_t)shadowMaps_[indexView].renderTarget_[0].textureID(), ImVec2(192, 120));
	//	ImGui::SetNextItemWidth(50.0f);
	//	ImGui::DragFloat("Horizontal", &camShadowSize.x); ImGui::SameLine();
	//	ImGui::SetNextItemWidth(50.0f);
	//	ImGui::DragFloat("Vertical", &camShadowSize.y);
	//	ImGui::SetNextItemWidth(50.0f);
	//	ImGui::DragFloat("Near", &camShadowDistance.x); ImGui::SameLine();
	//	ImGui::SetNextItemWidth(50.0f);
	//	ImGui::DragFloat("Far", &camShadowDistance.y);
	//	ImGui::SetNextItemWidth(50.0f);
	//	ImGui::DragInt("Texture Witdh", &textureSize_.x); ImGui::SameLine();
	//	ImGui::SetNextItemWidth(50.0f);
	//	ImGui::DragInt("Texture Height", &textureSize_.y);
	//	ImGui::End();
	//}
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

	objs_opaque.clear();
}

void ST::SystemLight::doRender(std::vector<Light_MyObjToRender>& objs){
	
	std::vector<InstanceInfo> instancing;
	GLuint actualMeshRendering = 0;
	int lastIndice = 0;
	bool firstTime = true;

	for (int i = 0; i < objs.size(); i++) {
		if (firstTime) {
			actualMeshRendering = objs[i].render_->mesh->getID();
			firstTime = false;
		}

		if (objs[i].render_->mesh->getID() != actualMeshRendering) {
			objs[lastIndice].render_->mesh->setInstanceData(instancing);
			objs[lastIndice].render_->mesh->render();
			instancing.clear();

			actualMeshRendering = objs[i].render_->mesh->getID();
		}

		// Mirar EmplaceBack
		instancing.push_back({ objs[i].transform_->m_transform_,
							   objs[i].render_->material.getColor(),
							   objs[i].render_->material.getTexIndex(),
							   objs[i].render_->material.shininess });
		lastIndice = i;
	}

	if (instancing.size() > 0) {
		objs[lastIndice].render_->mesh->setInstanceData(instancing);
		objs[lastIndice].render_->mesh->render();
		instancing.clear();
	}
}

ST::SystemLight::~SystemLight(){

}
