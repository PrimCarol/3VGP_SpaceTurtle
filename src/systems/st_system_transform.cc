#include "st_system_transform.h"

#include <components/st_transform.h>
#include <components/st_hierarchy.h>

#include <transform.hpp>

void ST::SystemTransform::UpdateTransforms(ST::GameObj_Manager &gm){

	//for (int i = 0; i < gm.transformComponentList_.size(); i++) {

	//	ST::TransformComponent* t = &gm.transformComponentList_[i].value();
	//	ST::HierarchyComponent* h = &gm.hierarchyComponentList_[i].value();

	//	// ------- Local -------
	//	glm::mat4 m(1.0f);

	//	t->m_Position_ = glm::mat4(1.0f);
	//	t->m_Position_ = glm::translate(t->m_Position_, t->getPosition());

	//	t->m_Rotation_ = glm::mat4(1.0f);
	//	t->m_Rotation_ = glm::rotate(t->m_Rotation_, t->getRotation().x, { 1.0f,0.0f,0.0f });
	//	t->m_Rotation_ = glm::rotate(t->m_Rotation_, t->getRotation().y, { 0.0f,1.0f,0.0f });
	//	t->m_Rotation_ = glm::rotate(t->m_Rotation_, t->getRotation().z, { 0.0f,0.0f,1.0f });

	//	m = t->m_Position_ * t->m_Rotation_;

	//	m = glm::scale(m, t->getScale());

	//	t->m_transform_ = m;

	//	// ------ World -----
	//	t->m_World_Position_ = t->m_Position_;
	//	t->m_World_Rotation_ = t->m_Rotation_;
	//	t->m_world_transform_ = m;

	//	if (h) {
	//		if (h->getParentID() != -1) {
	//			//t->m_transform_ = gm.GameObjsList_[h->getParentID()]->getComponentTransform()->m_transform_ * m;
	//			t->m_transform_ = gm.transformComponentList_[h->getParentID()]->m_world_transform_ * m;
	//			t->m_world_transform_ = gm.transformComponentList_[h->getParentID()]->m_world_transform_ * m;

	//			//t->m_World_Position_ = gm.transformComponentList_[h->getParentID()]->m_Position_ * t->m_Position_;
	//			//t->m_World_Rotation_ = gm.transformComponentList_[h->getParentID()]->m_Rotation_ * t->m_Rotation_;
	//		}
	//	}

	//	t->updateDirectionalVectors();
	//}

	auto* transformVector = gm.getComponentVector<ST::TransformComponent>();

	if (transformVector) {
		for (int i = 0; i < transformVector->size(); i++) {
			if (transformVector->at(i).has_value()) {
				ST::TransformComponent* t = &transformVector->at(i).value();
				//printf("[%d] Tiene transform\n", i);

				// ------- Local -------
				glm::mat4 m(1.0f);

				t->m_Position_ = glm::mat4(1.0f);
				t->m_Position_ = glm::translate(t->m_Position_, t->getPosition());

				t->m_Rotation_ = glm::mat4(1.0f);
				t->m_Rotation_ = glm::rotate(t->m_Rotation_, t->getRotation().x, { 1.0f,0.0f,0.0f });
				t->m_Rotation_ = glm::rotate(t->m_Rotation_, t->getRotation().y, { 0.0f,1.0f,0.0f });
				t->m_Rotation_ = glm::rotate(t->m_Rotation_, t->getRotation().z, { 0.0f,0.0f,1.0f });

				m = t->m_Position_ * t->m_Rotation_;

				m = glm::scale(m, t->getScale());

				t->m_transform_ = m;

				// ------ World -----
				t->m_World_Position_ = t->m_Position_;
				t->m_World_Rotation_ = t->m_Rotation_;
				t->m_world_transform_ = m;

				if (gm.getComponentVector<ST::HierarchyComponent>()->at(i).has_value()) {
					ST::HierarchyComponent* h = &gm.getComponentVector<ST::HierarchyComponent>()->at(i).value();
					if (h->getParentID() != -1) {

						if (gm.getComponentVector<ST::HierarchyComponent>()->at(h->getParentID()).has_value()) {
							if (gm.getComponentVector<ST::TransformComponent>()->at(h->getParentID()).has_value()) {
								ST::TransformComponent* tparent = &gm.getComponentVector<ST::TransformComponent>()->at(h->getParentID()).value();

								t->m_transform_ = tparent->m_world_transform_ * m;
								t->m_world_transform_ = tparent->m_world_transform_ * m;

								t->m_World_Position_ = tparent->m_Position_ * t->m_Position_;
								t->m_World_Rotation_ = tparent->m_Rotation_ * t->m_Rotation_;

								t->m_Position_ = tparent->m_Position_ * t->m_Position_;
								t->m_Rotation_ = tparent->m_Rotation_ * t->m_Rotation_;
							}
						}


						//t->m_transform_ = gm.GameObjsList_[h->getParentID()]->getComponentTransform()->m_transform_ * m;

						//t->m_transform_ = gm.transformComponentList_[h->getParentID()]->m_world_transform_ * m;
						//t->m_world_transform_ = gm.transformComponentList_[h->getParentID()]->m_world_transform_ * m;

						//t->m_World_Position_ = gm.transformComponentList_[h->getParentID()]->m_Position_ * t->m_Position_;
						//t->m_World_Rotation_ = gm.transformComponentList_[h->getParentID()]->m_Rotation_ * t->m_Rotation_;
					}
				}

				t->updateDirectionalVectors();
			}
		}
	}
}
