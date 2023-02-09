#include "st_system_transform.h"

#include <components/st_transform.h>

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

	auto* t = gm.getComponentVector<ST::TransformComponent>();

	for (int i = 0; i < t->size(); i++){
		if (t->at(i).has_value()) {
			printf("[%d] Tiene transform\n", i);
		}
	}

}
