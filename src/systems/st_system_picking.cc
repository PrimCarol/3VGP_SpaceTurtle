#include "st_system_picking.h"

#include <st_raycast.h>
#include <st_gameobj_manager.h>

#include <components/st_transform.h>
#include <components/st_render.h>
#include <components/st_collider.h>

int ST::SystemPicking::tryPickObj(const ST::Window& w, const ST::GameObj_Manager& gm){
	float objClose = 100000.0f;
	int objIndexClose = -1;

	//if (c == nullptr) {
	//	static std::unique_ptr<ST::Camera> cam_ = std::make_unique<ST::Camera>();
	//	cam_->update();
	//	c = cam_.get();
	//}

	//std::vector<std::optional<ST::RenderComponent>>& render = *gm.getComponentVector<ST::RenderComponent>();
	std::vector<std::optional<ST::TransformComponent>>& transform = *gm.getComponentVector<ST::TransformComponent>();
	std::vector<std::optional<ST::ColliderComponent>>& collider = *gm.getComponentVector<ST::ColliderComponent>();

	if (gm.mainCameraID >= 0 && (transform[gm.mainCameraID].has_value() && gm.getComponentVector<ST::CameraComponent>()->at(gm.mainCameraID).has_value())) {
		ST::CameraComponent* camComp = &gm.getComponentVector<ST::CameraComponent>()->at(gm.mainCameraID).value();

		for (int i = 0; i < gm.size(); i++) {
			if (collider[i].has_value() && collider[i]->active_) {
				if (transform[i].has_value()) {
					ST::Raycast ray;

					glm::vec3 maxPos = collider[i]->getMaxPoint();
					glm::vec3 minPos = collider[i]->getMinPoint();

					// Normal, este funciona.
					glm::vec3 colliderPoint_min(minPos * transform[i]->getScale());
					glm::vec3 colliderPoint_max(maxPos * transform[i]->getScale());
					glm::mat4 tcopia = transform[i]->m_Position_ * transform[i]->m_Rotation_;

					float outputDistance = 100000.0f;

					// Donde pulse con el mouse.
					if (ray.TraceRay(transform[gm.mainCameraID]->getPosition(), ray.ScreenPosToWorldRay(w, *camComp), colliderPoint_min, colliderPoint_max,
						tcopia, outputDistance)) {

						if (outputDistance < objClose) {
							objClose = outputDistance;
							objIndexClose = i;
						}
					}
				}
			}
		}

		if (objIndexClose != -1) {
			return objIndexClose;
		}
	}
	
	return -1;
}
