#include "st_system_light.h"

#include <st_gameobj_manager.h>
#include <components/st_light.h>
#include <components/st_render.h>
#include <components/st_transform.h>

#include <components/st_camera.h>
#include <st_rendertarget.h>

#include <st_program.h>

void ST::SystemLight::CompileLights(ST::GameObj_Manager& gm, ST::Program& thisProgram){

	auto* lightComps = gm.getComponentVector<ST::LightComponent>();
	auto* renderComps = gm.getComponentVector<ST::RenderComponent>();
	auto* transformComps = gm.getComponentVector<ST::TransformComponent>();

	char buffer[50];

	thisProgram.use();

	int countDirectionalLights = 0;
	int countPointLights = 0;
	int countSpotLights = 0;

	GLint idUniform = -1;

	for (int n = 0; n < lightComps->size(); n++) {
		if (lightComps->at(n).has_value()) {
			ST::LightComponent thisLight = lightComps->at(n).value();

			// ---- Lights ----

			glm::vec3 dirLight(0.0f,-1.0f,0.0f);

			if (transformComps->at(n).has_value()) {
				dirLight = transformComps->at(n)->getForward();
				if (gm.mainCameraID() != -1) {
					transformComps->at(n)->m_transform_ = glm::lookAt(transformComps->at(n)->getPosition(), transformComps->at(gm.mainCameraID())->getPosition(), glm::vec3(0.0f,1.0f,0.0f));
					transformComps->at(n)->m_transform_ = glm::inverse(transformComps->at(n)->m_transform_);
				}
				//thisLight.dirLight_.x = sinf(transformComps->at(n).value().getRotation().x);
				//thisLight.dirLight_.y = sinf(transformComps->at(n).value().getRotation().y);
				//thisLight.dirLight_.z = sinf(transformComps->at(n).value().getRotation().z);
			}

			if (thisLight.type_ == ST::Directional) {
				/*

				Creamos una camara (CameraComponent) en orthografic, para saber lo que ve la camara.

				*/
				//ST::CameraComponent cam;

				snprintf(buffer, 50, "u_DirectLight[%d].direction", countDirectionalLights);
				idUniform = thisProgram.getUniform(buffer);
				glUniform3f(idUniform, dirLight.x, dirLight.y, dirLight.z);

				snprintf(buffer, 50, "u_DirectLight[%d].ambient", countDirectionalLights);
				idUniform = thisProgram.getUniform(buffer);
				glUniform3f(idUniform, thisLight.ambient_.x, thisLight.ambient_.y, thisLight.ambient_.z);

				snprintf(buffer, 50, "u_DirectLight[%d].diffuse", countDirectionalLights);
				idUniform = thisProgram.getUniform(buffer);
				glUniform3f(idUniform, thisLight.diffuse_.x, thisLight.diffuse_.y, thisLight.diffuse_.z);

				snprintf(buffer, 50, "u_DirectLight[%d].specular", countDirectionalLights);
				idUniform = thisProgram.getUniform(buffer);
				glUniform3f(idUniform, thisLight.specular_.x, thisLight.specular_.y, thisLight.specular_.z);

				countDirectionalLights++;

			} else if (thisLight.type_ == ST::Point) {

				snprintf(buffer, 50, "u_PointLight[%d].position", countPointLights);
				idUniform = thisProgram.getUniform(buffer);
				glUniform3f(idUniform, transformComps->at(n).value().getPosition().x, transformComps->at(n).value().getPosition().y, transformComps->at(n).value().getPosition().z);

				snprintf(buffer, 50, "u_PointLight[%d].ambient", countPointLights);
				idUniform = thisProgram.getUniform(buffer);
				glUniform3f(idUniform, thisLight.color_.x, thisLight.color_.y, thisLight.color_.z);

				snprintf(buffer, 50, "u_PointLight[%d].diffuse", countPointLights);
				idUniform = thisProgram.getUniform(buffer);
				glUniform3f(idUniform, thisLight.color_.x, thisLight.color_.y, thisLight.color_.z);

				snprintf(buffer, 50, "u_PointLight[%d].specular", countPointLights);
				idUniform = thisProgram.getUniform(buffer);
				glUniform3f(idUniform, thisLight.color_.x, thisLight.color_.y, thisLight.color_.z);

				snprintf(buffer, 50, "u_PointLight[%d].constant", countPointLights);
				idUniform = thisProgram.getUniform(buffer);
				glUniform1f(idUniform, thisLight.constant_);

				snprintf(buffer, 50, "u_PointLight[%d].linear", countPointLights);
				idUniform = thisProgram.getUniform(buffer);
				glUniform1f(idUniform, thisLight.linear_);

				snprintf(buffer, 50, "u_PointLight[%d].quadratic", countPointLights);
				idUniform = thisProgram.getUniform(buffer);
				glUniform1f(idUniform, thisLight.quadratic_);

				countPointLights++;

			} else if (thisLight.type_ == ST::Spot){

				snprintf(buffer, 50, "u_SpotLight[%d].position", countSpotLights);
				idUniform = thisProgram.getUniform(buffer);
				glUniform3f(idUniform, transformComps->at(n).value().getPosition().x, transformComps->at(n).value().getPosition().y, transformComps->at(n).value().getPosition().z);

				snprintf(buffer, 50, "u_SpotLight[%d].ambient", countSpotLights);
				idUniform = thisProgram.getUniform(buffer);
				glUniform3f(idUniform, thisLight.color_.x, thisLight.color_.y, thisLight.color_.z);

				snprintf(buffer, 50, "u_SpotLight[%d].diffuse", countSpotLights);
				idUniform = thisProgram.getUniform(buffer);
				glUniform3f(idUniform, thisLight.color_.x, thisLight.color_.y, thisLight.color_.z);

				snprintf(buffer, 50, "u_SpotLight[%d].specular", countSpotLights);
				idUniform = thisProgram.getUniform(buffer);
				glUniform3f(idUniform, thisLight.color_.x, thisLight.color_.y, thisLight.color_.z);

				snprintf(buffer, 50, "u_SpotLight[%d].constant", countSpotLights);
				idUniform = thisProgram.getUniform(buffer);
				glUniform1f(idUniform, thisLight.constant_);

				snprintf(buffer, 50, "u_SpotLight[%d].linear", countSpotLights);
				idUniform = thisProgram.getUniform(buffer);
				glUniform1f(idUniform, thisLight.linear_);

				snprintf(buffer, 50, "u_SpotLight[%d].quadratic", countSpotLights);
				idUniform = thisProgram.getUniform(buffer);
				glUniform1f(idUniform, thisLight.quadratic_);

				snprintf(buffer, 50, "u_SpotLight[%d].direction", countSpotLights);
				idUniform = thisProgram.getUniform(buffer);
				glUniform3f(idUniform, transformComps->at(n).value().getRotation().x, transformComps->at(n).value().getRotation().y, transformComps->at(n).value().getRotation().z);

				snprintf(buffer, 50, "u_SpotLight[%d].cutOff", countSpotLights);
				idUniform = thisProgram.getUniform(buffer);
				glUniform1f(idUniform, thisLight.cutOff_);

				snprintf(buffer, 50, "u_SpotLight[%d].outerCutOff", countSpotLights);
				idUniform = thisProgram.getUniform(buffer);
				glUniform1f(idUniform, thisLight.outerCutOff_);

				countSpotLights++;
			}

			if (renderComps->at(n).has_value()) {
				renderComps->at(n).value().material.setColor(thisLight.color_.x, thisLight.color_.y, thisLight.color_.z);
			}

		} // if Have Light
	} // For Lights
	
	idUniform = thisProgram.getUniform("u_numDirectLights");
	glUniform1i(idUniform, countDirectionalLights);

	idUniform = thisProgram.getUniform("u_numPointLights");
	glUniform1i(idUniform, countPointLights);

	idUniform = thisProgram.getUniform("u_numSpotLights");
	glUniform1i(idUniform, countSpotLights);

	//glUseProgram(0);
}

#include <imgui.h>
#include <systems/st_system_render.h>

void ST::SystemLight::CompileShadows(ST::GameObj_Manager& gm){

	static ST::RenderTarget renderTarget;
	static bool firtsTime = true;
	if (firtsTime) {
		renderTarget.setUp(1920,840, ST::Texture::F_DEPTH, ST::Texture::DT_FLOAT);
		static ST::Quad q;
		ST::GameObj tempGo = gm.createGameObj(ST::TransformComponent{}, ST::RenderComponent{});
		tempGo.getComponent<ST::RenderComponent>()->setMesh(&q);
		tempGo.getComponent<ST::RenderComponent>()->material.setProgram(gm.unliteProgram);
		tempGo.getComponent<ST::RenderComponent>()->material.setTexture_Albedo(&renderTarget.textureToRender_);
		tempGo.getComponent<ST::TransformComponent>()->setScale(10.0f, 10.0f, 1.0f);
		tempGo.getComponent<ST::TransformComponent>()->setPosition(0.0f, -4.63f, 0.0f);
		tempGo.getComponent<ST::TransformComponent>()->setRotateX(1.58f);
		firtsTime = false;
	}

	auto* lightComps = gm.getComponentVector<ST::LightComponent>();
	auto* transformComps = gm.getComponentVector<ST::TransformComponent>();

	gm.shadowMapping->use();

	int countDirectionalLights = 0;
	int countPointLights = 0;
	int countSpotLights = 0;

	GLint idUniform = -1;


	for (int n = 0; n < lightComps->size(); n++) {
		if (lightComps->at(n).has_value() && transformComps->at(n).has_value()) {
			ST::LightComponent thisLight = lightComps->at(n).value();
			ST::TransformComponent thisTrans = transformComps->at(n).value();

			if (thisLight.type_ == ST::Directional) {

				glm::mat4 lightSpaceMatrix;

				ST::CameraComponent cam;
				//cam.lookAt(thisTrans.getPosition(), thisTrans.getForward(), glm::vec3(0.0f, 1.0f, 0.0f));
				cam.lookAt(thisTrans.getPosition(), thisTrans.getForward(), glm::vec3(0.0f, 1.0f, 0.0f));
				//cam.lookAt(thisTrans.getPosition(), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
				cam.setOrthographic(10.0f, 10.0f, 1.0f, 50.0f);
				lightSpaceMatrix = cam.projection * cam.view;


				idUniform = gm.shadowMapping->getUniform("lightSpaceMatrix");
				glUniformMatrix4fv(idUniform, 1, GL_FALSE, &lightSpaceMatrix[0][0]);

				renderTarget.start();
				//Render Scene.
				setUpRender(gm);
				renderTarget.end();
			}

		}
	}

	//ImGui::Begin("ViewDepth");
	//ImGui::Image((void*)(intptr_t)renderTarget.textureID(), ImVec2(192,120));
	//ImGui::End();
}

void ST::SystemLight::setUpRender(ST::GameObj_Manager& gm){
	auto render = *gm.getComponentVector<ST::RenderComponent>();
	auto transform = *gm.getComponentVector<ST::TransformComponent>();
	
	std::vector<Light_MyObjToRender> objs_opaque;

	for (int i = 0; i < render.size(); i++) {

		if (render[i].has_value() && transform[i].has_value()) {
			if (render[i]->visible_) {
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
			//setUpUniforms(objs[lastIndice].render_->material, objs[lastIndice].transform_, cam);
			objs[lastIndice].render_->mesh->setInstanceData(instancing);
			objs[lastIndice].render_->mesh->render();
			instancing.clear();

			actualMeshRendering = objs[i].render_->mesh->getID();
		}

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
