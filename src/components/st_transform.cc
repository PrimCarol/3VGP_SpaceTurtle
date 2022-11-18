#include <components/st_transform.h>

// -------------------- Transform ---------------------
ST::TransformComponent::TransformComponent(){
	//printf("Create Component: Transform\n");

	m_transform_ = glm::mat4(1);

	setPosition({ 0.0f,0.0f,0.0f });
	setScale({ 1.0f,1.0f,1.0f });
}

// ------------------------- Movement -------------------------
void ST::TransformComponent::Move(const glm::vec3 newPos) {
	m_transform_ = glm::translate(m_transform_, newPos);
	updateDirectionalVectors();
}


void ST::TransformComponent::RotateX(const float r) {
	m_transform_ = glm::rotate(m_transform_, r, { 1.0f,0.0f,0.0f });
	updateDirectionalVectors();
}
void ST::TransformComponent::RotateY(const float r) {
	m_transform_ = glm::rotate(m_transform_, r, { 0.0f,1.0f,0.0f });
	updateDirectionalVectors();
}
void ST::TransformComponent::RotateZ(const float r) {
	m_transform_ = glm::rotate(m_transform_, r, { 0.0f,0.0f,1.0f });
	updateDirectionalVectors();
}

// ------------------------- Setters -------------------------
void ST::TransformComponent::setPosition(const glm::vec3 pos) {
	m_transform_[3][0] = pos.x;
	m_transform_[3][1] = pos.y;
	m_transform_[3][2] = pos.z;
	updateDirectionalVectors();
}
void ST::TransformComponent::setScale(const glm::vec3 newScale) {
	//m_transform = glm::scale(m_transform, newScale);
	m_transform_[0][0] = newScale.x;
	m_transform_[1][1] = newScale.y;
	m_transform_[2][2] = newScale.z;
	updateDirectionalVectors();
}

// ------------------------ Physic Component -----------------------
//void ST::TransformComponent::setVelocity(const glm::vec3 vel){
//	movementVelocity = vel;
//}

//const glm::vec3 ST::TransformComponent::getVelocity(){
//	return movementVelocity;
//}

void ST::TransformComponent::updateDirectionalVectors(){
	vectorForward_.x = m_transform_[0][2];
	vectorForward_.y = m_transform_[1][2];
	vectorForward_.z = m_transform_[2][2];

	vectorRight_.x = m_transform_[0][0];
	vectorRight_.y = m_transform_[1][0];
	vectorRight_.z = m_transform_[2][0];

	vectorUp_.x = m_transform_[0][1];
	vectorUp_.y = m_transform_[1][1];
	vectorUp_.z = m_transform_[2][1];

	// Habria que normalizar esto???????
	vectorForward_ = glm::normalize(vectorForward_);
	vectorRight_ = glm::normalize(vectorRight_);
	vectorUp_ = glm::normalize(vectorUp_);
}

// ------------------------- Getters -------------------------
const glm::vec3 ST::TransformComponent::getPosition() {
	// 12 - 13 - 14

	// m - m - m - m
	// m - m - m - m
	// m - m - m - m
	// x - y - z - m
	return glm::vec3(m_transform_[3][0], m_transform_[3][1], m_transform_[3][2]);
}

const glm::vec3 ST::TransformComponent::getScale() {
	// 0 - 5 - 10

	// x - m - m - m
	// m - y - m - m
	// m - m - z - m
	// m - m - m - m
	return glm::vec3(m_transform_[0][0], m_transform_[1][1], m_transform_[2][2]);
}

const glm::vec3 ST::TransformComponent::getRotation() {
	//return glm::vec3(m_transform[3][0], m_transform[3][1], m_transform[3][2]);
	return glm::vec3();
}

const glm::vec3 ST::TransformComponent::getForward(){
	return vectorForward_;
}
const glm::vec3 ST::TransformComponent::getUp() {
	return vectorUp_;
}
const glm::vec3 ST::TransformComponent::getRight() {
	return vectorRight_;
}

ST::TransformComponent::~TransformComponent(){
	//printf("Destroy Component: Transform\n");
}

