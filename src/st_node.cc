#include <st_node.h>

ST::Node::Node(){
	
	m_transform = glm::mat4(1);

	setPosition({ 0.0f,0.0f,0.0f });
	setScale({ 1.0f,1.0f,1.0f });
}

// ------------------------- Transforms -------------------------
void ST::Node::Move(glm::vec3 newPos) {
	m_transform = glm::translate(m_transform, newPos);
}


void ST::Node::RotateX(float r) {
	m_transform = glm::rotate(m_transform, r, { 1.0f,0.0f,0.0f });
}
void ST::Node::RotateY(float r) {
	m_transform = glm::rotate(m_transform, r, { 0.0f,1.0f,0.0f });
}
void ST::Node::RotateZ(float r) {
	m_transform = glm::rotate(m_transform, r, { 0.0f,0.0f,1.0f });
}

// ------------------------- Setters -------------------------
void ST::Node::setPosition(const glm::vec3 pos){
	m_transform[3][0] = pos.x;
	m_transform[3][1] = pos.y;
	m_transform[3][2] = pos.z;
}
void ST::Node::setScale(const glm::vec3 newScale) {
	//m_transform = glm::scale(m_transform, newScale);
	m_transform[0][0] = newScale.x;
	m_transform[1][1] = newScale.y;
	m_transform[2][2] = newScale.z;
}

// ------------------------- Getters -------------------------
glm::vec3 ST::Node::getPosition() {
	// 12 - 13 - 14
	
	// m - m - m - m
	// m - m - m - m
	// m - m - m - m
	// x - y - z - m
	return glm::vec3(m_transform[3][0], m_transform[3][1], m_transform[3][2]);
}

glm::vec3 ST::Node::getScale() {
	// 0 - 5 - 10

	// x - m - m - m
	// m - y - m - m
	// m - m - z - m
	// m - m - m - m
	return glm::vec3(m_transform[0][0], m_transform[1][1], m_transform[2][2]);
}

glm::vec3 ST::Node::getRotation() {
	//return glm::vec3(m_transform[3][0], m_transform[3][1], m_transform[3][2]);
	return glm::vec3();
}

// ------------------------- Destroy -------------------------
ST::Node::~Node() {
	// Destroy
}