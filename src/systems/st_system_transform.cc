#include "st_system_transform.h"

#include <transform.hpp>

void ST::SystemTransform::UpdateTransforms(ST::GameObj_Manager &gm){

	for (int i = 0; i < gm.transformComponentList_.size(); i++) {

		ST::TransformComponent* t = &gm.transformComponentList_[i];
		ST::HierarchyComponent* h = &gm.hierarchyComponentList_[i];

		glm::mat4 m(1.0f);

		m = glm::translate(m, t->getPosition());

		m = glm::rotate(m, t->getRotation().x, { 1.0f,0.0f,0.0f });
		m = glm::rotate(m, t->getRotation().y, { 0.0f,1.0f,0.0f });
		m = glm::rotate(m, t->getRotation().z, { 0.0f,0.0f,1.0f });

		m = glm::scale(m, t->getScale());

		if (h->getParentID() != -1) {
			t->m_transform_ = gm.GameObjsList_[h->getParentID()]->getComponentTransform()->m_transform_ * m;
		}
		else {
			t->m_transform_ = m;
		}

		t->updateDirectionalVectors();
	}
}
