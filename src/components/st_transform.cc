#include <components/st_transform.h>


// -------------------- Transform ---------------------
ST::TransformComponent::TransformComponent(){
	//printf("Create Component: Transform\n");

	m_transform_ = glm::mat4(1);
	m_world_transform_ = glm::mat4(1);

	position_ = glm::vec3(0);
	rotation_ = glm::vec3(0);
	scale_ = glm::vec3(1.0f);

	dirty = true;

	setPosition(position_);
	setScale(scale_);
}

//void ST::TransformComponent::updateTransformMatrix(){
//	
//	glm::mat4 m(1.0f);
//
//	m = glm::translate(m, position_);
//
//	m = glm::rotate(m, rotation_.x, { 1.0f,0.0f,0.0f });
//	m = glm::rotate(m, rotation_.y, { 0.0f,1.0f,0.0f });
//	m = glm::rotate(m, rotation_.z, { 0.0f,0.0f,1.0f });
//
//	m = glm::scale(m, scale_);
//
//	m_transform_ = m;
//
//	updateDirectionalVectors();
//}

// ------------------------- Movement -------------------------
void ST::TransformComponent::Move(const glm::vec3 newPos) {
	position_ += newPos;
	dirty = true;
}

void ST::TransformComponent::RotateX(const float r) {
	rotation_.x += r;
	dirty = true;
}
void ST::TransformComponent::RotateY(const float r) {
	rotation_.y += r;
	dirty = true;
}
void ST::TransformComponent::RotateZ(const float r) {
	rotation_.z += r;
	dirty = true;
}

// ------------------------- Setters -------------------------
void ST::TransformComponent::setPosition(const glm::vec3 pos) {
	position_ = pos;
	dirty = true;
}
void ST::TransformComponent::setPosition(const float posX, const float posY, const float posZ) {
	position_.x = posX;
	position_.y = posY;
	position_.z = posZ;
	dirty = true;
}
void ST::TransformComponent::setRotateX(const float r) {
	rotation_.x = r;
	dirty = true;
}
void ST::TransformComponent::setRotateY(const float r) {
	rotation_.y = r;
	dirty = true;
}
void ST::TransformComponent::setRotateZ(const float r) {
	rotation_.z = r;
	dirty = true;
}
void ST::TransformComponent::setScale(const glm::vec3 newScale) {
	scale_ = newScale;
	dirty = true;
}

void ST::TransformComponent::setScale(const float scaleX, const float scaleY, const float scaleZ) {
	scale_.x = scaleX;
	scale_.y = scaleY;
	scale_.z = scaleZ;
	dirty = true;
}

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
const glm::vec3 ST::TransformComponent::getPosition() const {
	// 12 - 13 - 14

	// m - m - m - m
	// m - m - m - m
	// m - m - m - m
	// x - y - z - m
	//return glm::vec3(m_transform_[3][0], m_transform_[3][1], m_transform_[3][2]);
	return position_;
}

const glm::vec3 ST::TransformComponent::getScale() const {
	// 0 - 5 - 10

	// x - m - m - m
	// m - y - m - m
	// m - m - z - m
	// m - m - m - m
	//return glm::vec3(m_transform_[0][0], m_transform_[1][1], m_transform_[2][2]);
	return scale_;
}

const glm::vec3 ST::TransformComponent::getRotation() const {
	//return glm::vec3(m_transform[3][0], m_transform[3][1], m_transform[3][2]);
	return rotation_;
}

const glm::vec3 ST::TransformComponent::getForward() const {
	glm::vec3 tempForward;
	tempForward.x = m_transform_[0][2];
	tempForward.y = m_transform_[1][2];
	tempForward.z = m_transform_[2][2];
	
	return glm::normalize(tempForward);

	//return vectorForward_;
}
const glm::vec3 ST::TransformComponent::getUp() const {
	glm::vec3 tempUp;
	tempUp.x = m_transform_[0][1];
	tempUp.y = m_transform_[1][1];
	tempUp.z = m_transform_[2][1];

	return glm::normalize(tempUp);
	//return vectorUp_;
}
const glm::vec3 ST::TransformComponent::getRight() const {
	glm::vec3 tempRight;
	tempRight.x = m_transform_[0][0];
	tempRight.y = m_transform_[1][0];
	tempRight.z = m_transform_[2][0];

	return glm::normalize(tempRight);
	//return vectorRight_;
}

ST::TransformComponent::~TransformComponent(){
	//printf("Destroy Component: Transform\n");
}
