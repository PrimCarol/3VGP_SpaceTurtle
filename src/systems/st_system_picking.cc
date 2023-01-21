#include "st_system_picking.h"

#include <st_raycast.h>

ST::GameObj* ST::SystemPicking::tryPickObj(const ST::Window &w, const ST::GameObj_Manager& gm, const ST::Camera* c) {

	float objClose = 100000.0f;
	int objIndexClose = -1;

	if (c == nullptr) {
		static std::unique_ptr<ST::Camera> cam_ = std::make_unique<ST::Camera>();
		cam_->update();
		c = cam_.get();
	}

	for (int i = 0; i < gm.GameObjsList_.size(); i++) {

		ST::TransformComponent* t = gm.GameObjsList_[i]->getComponentTransform();

		if (t) {

			ST::Raycast ray;

			//glm::vec3 colliderPoint_min(-1.0f, -1.0f, -1.0f); // Collider
			//glm::vec3 colliderPoint_max(1.0f, 1.0f, 1.0f);

			//glm::vec3 colliderPoint_min(-gm.colliderComponentList_[i].size_);
			//glm::vec3 colliderPoint_max(gm.colliderComponentList_[i].size_);

			glm::vec3 colliderPoint_min(-t->getScale());
			glm::vec3 colliderPoint_max(t->getScale());

			float outputDistance = 100000.0f;

			if (c->getCameraType() == ST::kCam_Perpective) {
				// Donde pulse con el mouse.
				if (ray.TraceRay(c->transform_.getPosition(), ray.ScreenPosToWorldRay(w, *c), colliderPoint_min, colliderPoint_max,
					t->m_transform_, outputDistance)) {

					if (outputDistance < objClose) {
						objClose = outputDistance;
						objIndexClose = i;
					}
				}
			}
			else {
				// Enfrente de la camara.
				if (ray.TraceRay(c->transform_.getPosition(), c->transform_.getForward(), colliderPoint_min, colliderPoint_max,
					t->m_transform_, outputDistance)) {

					if (outputDistance < objClose) {
						objClose = outputDistance;
						objIndexClose = i;
					}
				}
			}
		}

	}

	if (objIndexClose != -1) {
		return gm.GameObjsList_[objIndexClose];
	}

	return nullptr;
}
