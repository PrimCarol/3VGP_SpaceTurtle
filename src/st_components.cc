#include <st_components.h>
#include <stdio.h>

// -------------------- Parent ---------------------
ST::Components::Components(){
	printf("Component: Parent\n");
}

ST::Components::~Components(){ }

// -------------------- Mesh ---------------------
ST::MeshComponent::MeshComponent(){
	printf("Component: Mesh\n");
}

ST::MeshComponent::~MeshComponent(){ }

// -------------------- Transform ---------------------
ST::TransformComponent::TransformComponent(){
	printf("Component: Transform\n");

	m_transform_ = glm::mat4(1);

	setPosition({ 0.0f,0.0f,0.0f });
	setScale({ 1.0f,1.0f,1.0f });
}

// ------------------------- Movement -------------------------
void ST::TransformComponent::Move(glm::vec3 newPos) {
	m_transform_ = glm::translate(m_transform_, newPos);
}


void ST::TransformComponent::RotateX(float r) {
	m_transform_ = glm::rotate(m_transform_, r, { 1.0f,0.0f,0.0f });
}
void ST::TransformComponent::RotateY(float r) {
	m_transform_ = glm::rotate(m_transform_, r, { 0.0f,1.0f,0.0f });
}
void ST::TransformComponent::RotateZ(float r) {
	m_transform_ = glm::rotate(m_transform_, r, { 0.0f,0.0f,1.0f });
}

// ------------------------- Setters -------------------------
void ST::TransformComponent::setPosition(const glm::vec3 pos) {
	m_transform_[3][0] = pos.x;
	m_transform_[3][1] = pos.y;
	m_transform_[3][2] = pos.z;
}
void ST::TransformComponent::setScale(const glm::vec3 newScale) {
	//m_transform = glm::scale(m_transform, newScale);
	m_transform_[0][0] = newScale.x;
	m_transform_[1][1] = newScale.y;
	m_transform_[2][2] = newScale.z;
}

// ------------------------- Getters -------------------------
glm::vec3 ST::TransformComponent::getPosition() {
	// 12 - 13 - 14

	// m - m - m - m
	// m - m - m - m
	// m - m - m - m
	// x - y - z - m
	return glm::vec3(m_transform_[3][0], m_transform_[3][1], m_transform_[3][2]);
}

glm::vec3 ST::TransformComponent::getScale() {
	// 0 - 5 - 10

	// x - m - m - m
	// m - y - m - m
	// m - m - z - m
	// m - m - m - m
	return glm::vec3(m_transform_[0][0], m_transform_[1][1], m_transform_[2][2]);
}

glm::vec3 ST::TransformComponent::getRotation() {
	//return glm::vec3(m_transform[3][0], m_transform[3][1], m_transform[3][2]);
	return glm::vec3();
}

ST::TransformComponent::~TransformComponent(){ }

// -------------------- Material ---------------------
ST::MaterialComponent::MaterialComponent(){
	printf("Component: Material\n");
}

ST::MaterialComponent::~MaterialComponent(){ }
