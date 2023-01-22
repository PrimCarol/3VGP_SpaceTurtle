#include <components/st_collider.h>

#include <st_mesh.h>

// -------------------- Collider ---------------------
ST::ColliderComponent::ColliderComponent(){
	//printf("Create Component: Collider\n");
	//center_ = glm::vec3(0.0f, 0.0f, 0.0f);
	//size_ = glm::vec3(1.0f,1.0f,1.0f);
}

/*#include <glad.h>
void ST::ColliderComponent::draw() const{
	glBegin(GL_LINES);
	
	glColor3f(0.0, 1.0, 0.0);

	glVertex3f(size_.x, size_.y, size_.z);
	glVertex3f(-size_.x, size_.y, size_.z);

	glVertex3f(-size_.x, size_.y, size_.z);
	glVertex3f(-size_.x, size_.y, -size_.z);

	glVertex3f(-size_.x, size_.y, -size_.z);
	glVertex3f(size_.x, size_.y, -size_.z);

	glVertex3f(size_.x, size_.y, size_.z);
	glVertex3f(size_.x, size_.y, -size_.z);

	glVertex3f(size_.x, -size_.y, size_.z);
	glVertex3f(-size_.x, -size_.y, size_.z);

	glVertex3f(-size_.x, -size_.y, size_.z);
	glVertex3f(-size_.x, -size_.y, -size_.z);

	glVertex3f(-size_.x, -size_.y, -size_.z);
	glVertex3f(size_.x, -size_.y, -size_.z);

	glVertex3f(size_.x, -size_.y, size_.z);
	glVertex3f(size_.x, -size_.y, -size_.z);

	glVertex3f(size_.x, -size_.y, size_.z);
	glVertex3f(size_.x, size_.y, size_.z);

	glVertex3f(size_.x, -size_.y, -size_.z);
	glVertex3f(size_.x, size_.y, -size_.z);

	glVertex3f(-size_.x, -size_.y, size_.z);
	glVertex3f(-size_.x, size_.y, size_.z);

	glVertex3f(-size_.x, -size_.y, -size_.z);
	glVertex3f(-size_.x, size_.y, -size_.z);

	//glVertex3f(-size_.x, -size_.y, -size_.z);
	glEnd();
}*/

ST::ColliderComponent::~ColliderComponent(){
	//printf("Destroy Component: Collider\n");

}

