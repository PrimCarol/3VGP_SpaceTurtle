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

				// ---- Lights ----
				for (int n = 0; n < lightComps->size(); n++) {
					if (lightComps->at(n).has_value()) {
						ST::LightComponent thisLight = lightComps->at(n).value();

						printf("[%d] Luz -> ", n);

						if (transformComps->at(i).has_value()) {
							thisLight.dirLight_ = transformComps->at(n).value().getRotation();
						}

						GLint idUniform = -1;

						switch (thisLight.type_) {
						case ST::Directional:
							printf("Directional \n");

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
							printf("Point \n");
							break;
						case ST::Spot:
							printf("Spot \n");
							break;
						}
					}

				} // end for lightComps

				glUseProgram(0);

			} // if thisProgram

		}
	}
}
