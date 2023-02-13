#include "st_system_light.h"

#include <st_gameobj_manager.h>
#include <components/st_light.h>
#include <components/st_render.h>
#include <components/st_transform.h>

void ST::SystemLight::CompileLights(ST::GameObj_Manager& gm){

	auto* lightComps = gm.getComponentVector<ST::LightComponent>();
	auto* renderComps = gm.getComponentVector<ST::RenderComponent>();
	auto* transformComps = gm.getComponentVector<ST::TransformComponent>();

	for (int i = 0; i < renderComps->size(); i++){
		if (renderComps->at(i).has_value()) {
			
			ST::RenderComponent renderComp = renderComps->at(i).value();
			const ST::Program* thisProgram = nullptr;

			thisProgram = renderComp.material.getProgram();

			if (thisProgram) {

				thisProgram->use();

				char buffer[50];
				int countPointLights = 0;
				int countSpotLights = 0;

				// ---- Lights ----
				for (int n = 0; n < lightComps->size(); n++) {
					if (lightComps->at(n).has_value()) {
						ST::LightComponent thisLight = lightComps->at(n).value();

						if (transformComps->at(i).has_value()) {
							thisLight.dirLight_ = transformComps->at(n).value().getRotation();
							//thisLight.dirLight_.x = sinf(transformComps->at(n).value().getRotation().x);
							//thisLight.dirLight_.y = sinf(transformComps->at(n).value().getRotation().y);
							//thisLight.dirLight_.z = sinf(transformComps->at(n).value().getRotation().z);
						}

						GLint idUniform = -1;

						switch (thisLight.type_) {
						case ST::Directional:

							idUniform = thisProgram->getUniform("u_DirectLight.direction");
							glUniform3f(idUniform, thisLight.dirLight_.x, thisLight.dirLight_.y, thisLight.dirLight_.z);

							idUniform = thisProgram->getUniform("u_DirectLight.ambient");
							glUniform3f(idUniform, thisLight.ambient_.x, thisLight.ambient_.y, thisLight.ambient_.z);

							idUniform = thisProgram->getUniform("u_DirectLight.diffuse");
							glUniform3f(idUniform, thisLight.diffuse_.x, thisLight.diffuse_.y, thisLight.diffuse_.z);

							idUniform = thisProgram->getUniform("u_DirectLight.specular");
							glUniform3f(idUniform, thisLight.specular_.x, thisLight.specular_.y, thisLight.specular_.z);

							break;
						case ST::Point:

							snprintf(buffer, 50, "u_PointLight[%d].position", countPointLights);
							idUniform = thisProgram->getUniform(buffer);
							glUniform3f(idUniform, transformComps->at(n).value().getPosition().x, transformComps->at(n).value().getPosition().y, transformComps->at(n).value().getPosition().z);
							
							snprintf(buffer, 50, "u_PointLight[%d].ambient", countPointLights);
							idUniform = thisProgram->getUniform(buffer);
							glUniform3f(idUniform, thisLight.color_.x, thisLight.color_.y, thisLight.color_.z);
							
							snprintf(buffer, 50, "u_PointLight[%d].diffuse", countPointLights);
							idUniform = thisProgram->getUniform(buffer);
							glUniform3f(idUniform, thisLight.color_.x, thisLight.color_.y, thisLight.color_.z);
							
							snprintf(buffer, 50, "u_PointLight[%d].specular", countPointLights);
							idUniform = thisProgram->getUniform(buffer);
							glUniform3f(idUniform, thisLight.color_.x, thisLight.color_.y, thisLight.color_.z);
							
							snprintf(buffer, 50, "u_PointLight[%d].constant", countPointLights);
							idUniform = thisProgram->getUniform(buffer);
							glUniform1f(idUniform, thisLight.constant_);

							snprintf(buffer, 50, "u_PointLight[%d].linear", countPointLights);
							idUniform = thisProgram->getUniform(buffer);
							glUniform1f(idUniform, thisLight.linear_);

							snprintf(buffer, 50, "u_PointLight[%d].quadratic", countPointLights);
							idUniform = thisProgram->getUniform(buffer);
							glUniform1f(idUniform, thisLight.quadratic_);

							countPointLights++;
							break;
						case ST::Spot:

							snprintf(buffer, 50, "u_SpotLight[%d].position", countSpotLights);
							idUniform = thisProgram->getUniform(buffer);
							glUniform3f(idUniform, transformComps->at(n).value().getPosition().x, transformComps->at(n).value().getPosition().y, transformComps->at(n).value().getPosition().z);

							snprintf(buffer, 50, "u_SpotLight[%d].ambient", countSpotLights);
							idUniform = thisProgram->getUniform(buffer);
							glUniform3f(idUniform, thisLight.color_.x, thisLight.color_.y, thisLight.color_.z);

							snprintf(buffer, 50, "u_SpotLight[%d].diffuse", countSpotLights);
							idUniform = thisProgram->getUniform(buffer);
							glUniform3f(idUniform, thisLight.color_.x, thisLight.color_.y, thisLight.color_.z);

							snprintf(buffer, 50, "u_SpotLight[%d].specular", countSpotLights);
							idUniform = thisProgram->getUniform(buffer);
							glUniform3f(idUniform, thisLight.color_.x, thisLight.color_.y, thisLight.color_.z);

							snprintf(buffer, 50, "u_SpotLight[%d].constant", countSpotLights);
							idUniform = thisProgram->getUniform(buffer);
							glUniform1f(idUniform, thisLight.constant_);

							snprintf(buffer, 50, "u_SpotLight[%d].linear", countSpotLights);
							idUniform = thisProgram->getUniform(buffer);
							glUniform1f(idUniform, thisLight.linear_);

							snprintf(buffer, 50, "u_SpotLight[%d].quadratic", countSpotLights);
							idUniform = thisProgram->getUniform(buffer);
							glUniform1f(idUniform, thisLight.quadratic_);

							snprintf(buffer, 50, "u_SpotLight[%d].direction", countSpotLights);
							idUniform = thisProgram->getUniform(buffer);
							glUniform3f(idUniform, transformComps->at(n).value().getRotation().x, transformComps->at(n).value().getRotation().y, transformComps->at(n).value().getRotation().z);

							snprintf(buffer, 50, "u_SpotLight[%d].cutOff", countSpotLights);
							idUniform = thisProgram->getUniform(buffer);
							glUniform1f(idUniform, thisLight.cutOff_);

							snprintf(buffer, 50, "u_SpotLight[%d].outerCutOff", countSpotLights);
							idUniform = thisProgram->getUniform(buffer);
							glUniform1f(idUniform, thisLight.outerCutOff_);

							countSpotLights++;

							break;
						}
					}

				} // end for lightComps

				GLint idUniform = -1;

				idUniform = thisProgram->getUniform("u_numPointLights");
				glUniform1i(idUniform, countPointLights);

				idUniform = thisProgram->getUniform("u_numSpotLights");
				glUniform1i(idUniform, countSpotLights);

				glUseProgram(0);

			} // if thisProgram

		}
	}
}
