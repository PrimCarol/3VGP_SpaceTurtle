#include "st_system_light.h"

#include <st_gameobj_manager.h>
#include <components/st_light.h>
#include <components/st_render.h>
#include <components/st_transform.h>

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
				dirLight = transformComps->at(n).value().getRotation();
				//thisLight.dirLight_.x = sinf(transformComps->at(n).value().getRotation().x);
				//thisLight.dirLight_.y = sinf(transformComps->at(n).value().getRotation().y);
				//thisLight.dirLight_.z = sinf(transformComps->at(n).value().getRotation().z);
			}

			switch (thisLight.type_) {
			case ST::Directional:

				/*
				
				Creamos una camara (CameraComponent) en orthografic, para saber lo que ve la camara.
				
				*/

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
				break;
			case ST::Point:

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
				break;
			case ST::Spot:

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

				break;
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

	glUseProgram(0);
}
