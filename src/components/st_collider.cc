#include <components/st_collider.h>

#include <st_mesh.h>

// -------------------- Collider ---------------------
ST::ColliderComponent::ColliderComponent(){
	minPoint_ = glm::vec3(-1.0f);
	maxPoint_ = glm::vec3(1.0f);
	active_ = true;
}

void ST::ColliderComponent::setMinPoint(const glm::vec3 xyz) {
	minPoint_ = xyz;
}

void ST::ColliderComponent::setMaxPoint(const glm::vec3 xyz) {
	maxPoint_ = xyz;
}

glm::vec3 ST::ColliderComponent::getMaxPoint() const{
	return maxPoint_;
}

glm::vec3 ST::ColliderComponent::getMinPoint() const {
	return minPoint_;
}

#include <glad.h>
void ST::ColliderComponent::draw() const{
	glBegin(GL_LINES);

	glColor3f(0.0, 1.0, 0.0);

	glVertex3f(maxPoint_.x, maxPoint_.y, maxPoint_.z);
	glVertex3f(minPoint_.x, maxPoint_.y, maxPoint_.z);

	glVertex3f(minPoint_.x, maxPoint_.y, maxPoint_.z);
	glVertex3f(minPoint_.x, maxPoint_.y, minPoint_.z);

	glVertex3f(minPoint_.x, maxPoint_.y, minPoint_.z);
	glVertex3f(maxPoint_.x, maxPoint_.y, minPoint_.z);

	glVertex3f(maxPoint_.x, maxPoint_.y, maxPoint_.z);
	glVertex3f(maxPoint_.x, maxPoint_.y, minPoint_.z);

	glVertex3f(maxPoint_.x, minPoint_.y, maxPoint_.z);
	glVertex3f(minPoint_.x, minPoint_.y, maxPoint_.z);

	glVertex3f(minPoint_.x, minPoint_.y, maxPoint_.z);
	glVertex3f(minPoint_.x, minPoint_.y, minPoint_.z);

	glVertex3f(minPoint_.x, minPoint_.y, minPoint_.z);
	glVertex3f(maxPoint_.x, minPoint_.y, minPoint_.z);

	glVertex3f(maxPoint_.x, minPoint_.y, maxPoint_.z);
	glVertex3f(maxPoint_.x, minPoint_.y, minPoint_.z);

	glVertex3f(maxPoint_.x, minPoint_.y, maxPoint_.z);
	glVertex3f(maxPoint_.x, maxPoint_.y, maxPoint_.z);

	glVertex3f(maxPoint_.x, minPoint_.y, minPoint_.z);
	glVertex3f(maxPoint_.x, maxPoint_.y, minPoint_.z);

	glVertex3f(minPoint_.x, minPoint_.y, maxPoint_.z);
	glVertex3f(minPoint_.x, maxPoint_.y, maxPoint_.z);

	glVertex3f(minPoint_.x, minPoint_.y, minPoint_.z);
	glVertex3f(minPoint_.x, maxPoint_.y, minPoint_.z);

	//glVertex3f(-size_.x, -size_.y, -size_.z);
	glEnd();
}

ST::ColliderComponent::~ColliderComponent(){
	//printf("Destroy Component: Collider\n");

}

