#include <st_node.h>

ST::Node::Node(){
	
	setName("Node");

	parent_ = nullptr;

	m_transform_ = glm::mat4(1);

	setPosition({ 0.0f,0.0f,0.0f });
	setScale({ 1.0f,1.0f,1.0f });
}

void ST::Node::setName(const char* n){
	name_ = n;
}

const char* ST::Node::getName(){
	return name_;
}

// ------------------------- Transforms -------------------------
void ST::Node::Move(glm::vec3 newPos) {
	m_transform_ = glm::translate(m_transform_, newPos);
}


void ST::Node::RotateX(float r) {
	m_transform_ = glm::rotate(m_transform_, r, { 1.0f,0.0f,0.0f });
}
void ST::Node::RotateY(float r) {
	m_transform_ = glm::rotate(m_transform_, r, { 0.0f,1.0f,0.0f });
}
void ST::Node::RotateZ(float r) {
	m_transform_ = glm::rotate(m_transform_, r, { 0.0f,0.0f,1.0f });
}

// ------------------------- Setters -------------------------
void ST::Node::setPosition(const glm::vec3 pos){
	m_transform_[3][0] = pos.x;
	m_transform_[3][1] = pos.y;
	m_transform_[3][2] = pos.z;
}
void ST::Node::setScale(const glm::vec3 newScale) {
	//m_transform = glm::scale(m_transform, newScale);
	m_transform_[0][0] = newScale.x;
	m_transform_[1][1] = newScale.y;
	m_transform_[2][2] = newScale.z;
}

// ------------------------- Getters -------------------------
glm::vec3 ST::Node::getPosition() {
	// 12 - 13 - 14
	
	// m - m - m - m
	// m - m - m - m
	// m - m - m - m
	// x - y - z - m
	return glm::vec3(m_transform_[3][0], m_transform_[3][1], m_transform_[3][2]);
}

glm::vec3 ST::Node::getScale() {
	// 0 - 5 - 10

	// x - m - m - m
	// m - y - m - m
	// m - m - z - m
	// m - m - m - m
	return glm::vec3(m_transform_[0][0], m_transform_[1][1], m_transform_[2][2]);
}

glm::vec3 ST::Node::getRotation() {
	//return glm::vec3(m_transform[3][0], m_transform[3][1], m_transform[3][2]);
	return glm::vec3();
}

ST::Node* ST::Node::getParent() const{
	return parent_;
}

int ST::Node::getChildCount() const{
	return child_.size();
}

ST::Node* ST::Node::getChild(int index) const{
	if (index > getChildCount() || index < 0) { return nullptr; }
	return child_.at(index);
}

void ST::Node::addChild(Node* n){
	if (n) {
		child_.push_back(n);
		n->parent_ = this;
	}
}

// ------------------------- Destroy -------------------------
ST::Node::~Node() {
	// Destroy
}