#include "st_system_picking.h"

#include <st_raycast.h>

/*ST::GameObj* ST::SystemPicking::tryPickObj(const ST::Window& w, const ST::GameObj_Manager& gm, const ST::Camera* c) {

	float objClose = 100000.0f;
	int objIndexClose = -1;

	if (c == nullptr) {
		static std::unique_ptr<ST::Camera> cam_ = std::make_unique<ST::Camera>();
		cam_->update();
		c = cam_.get();
	}

	
	std::vector<std::optional<ST::RenderComponent>>& r = *gm.getComponentVector<ST::RenderComponent>();
	std::vector<std::optional<ST::TransformComponent>>& t = *gm.getComponentVector<ST::TransformComponent>();

	for (int i = 0; i < gm.size(); i++) {
		if (r[i].has_value() && t[i].has_value()) {
			ST::Raycast ray;

			glm::vec3 maxPos(-1.0f, -1.0f, -1.0f), minPos(1.0f, 1.0f, 1.0f);

			if (r[i]->mesh) {
				for (int j = 0; j < r[i]->mesh->vertices_.size(); j++) {
					if (r[i]->mesh->vertices_[j].pos.x > maxPos.x) { maxPos.x = r[i]->mesh->vertices_[j].pos.x; }
					if (r[i]->mesh->vertices_[j].pos.y > maxPos.y) { maxPos.y = r[i]->mesh->vertices_[j].pos.y; }
					if (r[i]->mesh->vertices_[j].pos.z > maxPos.z) { maxPos.z = r[i]->mesh->vertices_[j].pos.z; }

					if (r[i]->mesh->vertices_[j].pos.y < minPos.y) { minPos.y = r[i]->mesh->vertices_[j].pos.y; }
					if (r[i]->mesh->vertices_[j].pos.z < minPos.z) { minPos.z = r[i]->mesh->vertices_[j].pos.z; }
					if (r[i]->mesh->vertices_[j].pos.x < minPos.x) { minPos.x = r[i]->mesh->vertices_[j].pos.x; }
				}
			}

			// Normal, este funciona.
			glm::vec3 colliderPoint_min(minPos * t[i]->getScale());
			glm::vec3 colliderPoint_max(maxPos * t[i]->getScale());
			glm::mat4 tcopia = t[i]->m_Position_ * t[i]->m_Rotation_;

			float outputDistance = 100000.0f;

			// Donde pulse con el mouse.
			if (ray.TraceRay(c->transform_.getPosition(), ray.ScreenPosToWorldRay(w, *c), colliderPoint_min, colliderPoint_max,
				tcopia, outputDistance)) {

				if (outputDistance < objClose) {
					objClose = outputDistance;
					objIndexClose = i;
				}
			}

		}
	}

	if (objIndexClose != -1) {
		return gm.getGameObj(r[objIndexClose]);
	}
	
	

	//for (int i = 0; i < gm.GameObjsList_.size(); i++) {

	//	ST::TransformComponent* t = gm.GameObjsList_[i]->getComponentTransform();

	//	if (t) {

	//		ST::Raycast ray;

	//		glm::vec3 maxPos(-1.0f, -1.0f, -1.0f), minPos(1.0f, 1.0f, 1.0f);
	//		ST::RenderComponent* r = gm.GameObjsList_[i]->getComponentRender();
	//		if (r) {
	//			if (r->mesh) {
	//				for (int j = 0; j < r->mesh->vertices_.size(); j++) {
	//					if (r->mesh->vertices_[j].pos.x > maxPos.x) { maxPos.x = r->mesh->vertices_[j].pos.x; }
	//					if (r->mesh->vertices_[j].pos.y > maxPos.y) { maxPos.y = r->mesh->vertices_[j].pos.y; }
	//					if (r->mesh->vertices_[j].pos.z > maxPos.z) { maxPos.z = r->mesh->vertices_[j].pos.z; }

	//					if (r->mesh->vertices_[j].pos.x < minPos.x) { minPos.x = r->mesh->vertices_[j].pos.x; }
	//					if (r->mesh->vertices_[j].pos.y < minPos.y) { minPos.y = r->mesh->vertices_[j].pos.y; }
	//					if (r->mesh->vertices_[j].pos.z < minPos.z) { minPos.z = r->mesh->vertices_[j].pos.z; }
	//				}
	//			}
	//		}

	//		//glm::vec3 worldScale(t->m_world_transform_[0][0], t->m_world_transform_[1][1], t->m_world_transform_[2][2]);
	//		//glm::vec3 colliderPoint_min(minPos * worldScale);
	//		//glm::vec3 colliderPoint_max(maxPos * worldScale);
	//		//glm::mat4 tcopia = t->m_World_Position_ * t->m_World_Rotation_;


	//		//glm::vec3 worldScale(t->m_world_transform_[0][0], t->m_world_transform_[1][1], t->m_world_transform_[2][2]);
	//		//glm::vec3 colliderPoint_min(minPos * worldScale);
	//		//glm::vec3 colliderPoint_max(maxPos * worldScale);
	//		//glm::mat4 tcopia = t->m_world_transform_;

	//		// Normal, este funciona.
	//		glm::vec3 colliderPoint_min(minPos * t->getScale());
	//		glm::vec3 colliderPoint_max(maxPos * t->getScale());
	//		glm::mat4 tcopia = t->m_Position_ * t->m_Rotation_;

	//		float outputDistance = 100000.0f;

	//		// Donde pulse con el mouse.
	//		if (ray.TraceRay(c->transform_.getPosition(), ray.ScreenPosToWorldRay(w, *c), colliderPoint_min, colliderPoint_max,
	//			tcopia, outputDistance)) {

	//			if (outputDistance < objClose) {
	//				objClose = outputDistance;
	//				objIndexClose = i;
	//			}
	//		}

	//		//if (c->getCameraType() == ST::kCam_Perpective) {
	//		//	// Donde pulse con el mouse.
	//		//	if (ray.TraceRay(c->transform_.getPosition(), ray.ScreenPosToWorldRay(w, *c), colliderPoint_min, colliderPoint_max,
	//		//		tcopia, outputDistance)) {

	//		//		if (outputDistance < objClose) {
	//		//			objClose = outputDistance;
	//		//			objIndexClose = i;
	//		//		}
	//		//	}
	//		//}
	//		//else {
	//		//	// Enfrente de la camara.
	//		//	if (ray.TraceRay(c->transform_.getPosition(), c->transform_.getForward(), colliderPoint_min, colliderPoint_max,
	//		//		t->m_transform_, outputDistance)) {

	//		//		if (outputDistance < objClose) {
	//		//			objClose = outputDistance;
	//		//			objIndexClose = i;
	//		//		}
	//		//	}
	//		//}
	//	}

	//}

	//if (objIndexClose != -1) {
	//	return gm.GameObjsList_[objIndexClose];
	//}

	return nullptr;
}*/

#include <st_gameobj_manager.h>

#include <components/st_transform.h>
#include <components/st_render.h>

int ST::SystemPicking::tryPickObj(const ST::Window& w, const ST::GameObj_Manager& gm, const ST::Camera* c){
	float objClose = 100000.0f;
	int objIndexClose = -1;

	if (c == nullptr) {
		static std::unique_ptr<ST::Camera> cam_ = std::make_unique<ST::Camera>();
		cam_->update();
		c = cam_.get();
	}

	std::vector<std::optional<ST::RenderComponent>>& r = *gm.getComponentVector<ST::RenderComponent>();
	std::vector<std::optional<ST::TransformComponent>>& t = *gm.getComponentVector<ST::TransformComponent>();

	for (int i = 0; i < gm.size(); i++) {
		if (r[i].has_value() && t[i].has_value()) {
			ST::Raycast ray;

			glm::vec3 maxPos(-1.0f, -1.0f, -1.0f), minPos(1.0f, 1.0f, 1.0f);

			/*if (r[i]->mesh) {
				for (int j = 0; j < r[i]->mesh->vertices_.size(); j++) {
					if (r[i]->mesh->vertices_[j].pos.x > maxPos.x) { maxPos.x = r[i]->mesh->vertices_[j].pos.x; }
					if (r[i]->mesh->vertices_[j].pos.y > maxPos.y) { maxPos.y = r[i]->mesh->vertices_[j].pos.y; }
					if (r[i]->mesh->vertices_[j].pos.z > maxPos.z) { maxPos.z = r[i]->mesh->vertices_[j].pos.z; }

					if (r[i]->mesh->vertices_[j].pos.y < minPos.y) { minPos.y = r[i]->mesh->vertices_[j].pos.y; }
					if (r[i]->mesh->vertices_[j].pos.z < minPos.z) { minPos.z = r[i]->mesh->vertices_[j].pos.z; }
					if (r[i]->mesh->vertices_[j].pos.x < minPos.x) { minPos.x = r[i]->mesh->vertices_[j].pos.x; }
				}
			}*/

			// Normal, este funciona.
			glm::vec3 colliderPoint_min(minPos * t[i]->getScale());
			glm::vec3 colliderPoint_max(maxPos * t[i]->getScale());
			glm::mat4 tcopia = t[i]->m_Position_ * t[i]->m_Rotation_;

			float outputDistance = 100000.0f;

			// Donde pulse con el mouse.
			if (ray.TraceRay(c->transform_.getPosition(), ray.ScreenPosToWorldRay(w, *c), colliderPoint_min, colliderPoint_max,
				tcopia, outputDistance)) {

				if (outputDistance < objClose) {
					objClose = outputDistance;
					objIndexClose = i;
				}
			}

		}
	}

	if (objIndexClose != -1) {
		return objIndexClose;
	}
	
	return -1;
}
