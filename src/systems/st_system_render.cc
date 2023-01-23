#include "st_system_render.h"

void drawCollision(glm::vec3 min, glm::vec3 max){
	glBegin(GL_LINES);

	glColor3f(0.0, 1.0, 0.0);

	glVertex3f(max.x, max.y, max.z);
	glVertex3f(min.x, max.y, max.z);

	glVertex3f(min.x, max.y, max.z);
	glVertex3f(min.x, max.y, min.z);

	glVertex3f(min.x, max.y, min.z);
	glVertex3f(max.x, max.y, min.z);

	glVertex3f(max.x, max.y, max.z);
	glVertex3f(max.x, max.y, min.z);

	glVertex3f(max.x, min.y, max.z);
	glVertex3f(min.x, min.y, max.z);

	glVertex3f(min.x, min.y, max.z);
	glVertex3f(min.x, min.y, min.z);

	glVertex3f(min.x, min.y, min.z);
	glVertex3f(max.x, min.y, min.z);

	glVertex3f(max.x, min.y, max.z);
	glVertex3f(max.x, min.y, min.z);

	glVertex3f(max.x, min.y, max.z);
	glVertex3f(max.x, max.y, max.z);

	glVertex3f(max.x, min.y, min.z);
	glVertex3f(max.x, max.y, min.z);

	glVertex3f(min.x, min.y, max.z);
	glVertex3f(min.x, max.y, max.z);

	glVertex3f(min.x, min.y, min.z);
	glVertex3f(min.x, max.y, min.z);

	//glVertex3f(-size_.x, -size_.y, -size_.z);
	glEnd();
}

void ST::SystemRender::Render(const std::vector<std::optional<ST::RenderComponent>>& r, const std::vector<std::optional<ST::TransformComponent>>& t, ST::Camera* cam){
	ST::Material* mat = nullptr;
	const ST::Program* p = nullptr;

	glEnable(GL_DEPTH_TEST);

	if (cam == nullptr) {
		static std::unique_ptr<ST::Camera> cam_ = std::make_unique<ST::Camera>();
		cam = cam_.get();
	}

	cam->update();

	GLuint lastProgramID = 0;

	for (size_t i = 0; i < r.size(); i++) {

		// Material
		mat = r[i].value().material.get();
		if (mat) {

			p = mat->getProgram();

			if (lastProgramID != p->getID()) {
				p->use();
				lastProgramID = p->getID();
			}

			// ------ Camara -------
			GLuint camPos = p->getUniform("u_view_pos");
			glm::vec3 camTransPos = cam->transform_.getPosition();
			glUniform3fv(camPos, 1, &camTransPos.x);
			GLuint camView = p->getUniform("u_view_matrix");
			glUniformMatrix4fv(camView, 1, GL_FALSE, &cam->view[0][0]);
			GLuint camProjection = p->getUniform("u_projection_matrix");
			glUniformMatrix4fv(camProjection, 1, GL_FALSE, &cam->projection[0][0]);
			GLuint camVP = p->getUniform("u_vp_matrix");
			glm::mat4 cam_m_vp = cam->projection * cam->view;
			glUniformMatrix4fv(camVP, 1, GL_FALSE, &cam_m_vp[0][0]);
			// ------ Camara -------

			// De momento esta mal, funciona 1:1.
			GLuint u_m_trans = p->getUniform("u_m_trans");
			glUniformMatrix4fv(u_m_trans, 1, GL_FALSE, &t[i].value().m_transform_[0][0]);

			// Material 
			GLuint u_color = p->getUniform("u_color");
			glm::vec3 c = mat->getColor();
			glUniform3fv(u_color, 1, &c[0]);

			GLuint u_haveAlbedo = p->getUniform("u_haveAlbedo");
			glUniform1i(u_haveAlbedo, mat->haveAlbedo);

			if (mat->haveAlbedo) {
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, mat->getAlbedo()->getID());
			}
		}

		glm::vec3 maxPos(-999.0f, -999.0f, -1.0f), minPos(999.0f, 999.0f, 999.0f);

		if (r[i].value().mesh) {
			r[i].value().mesh->render();

			//if (ST::SystemRender::setCollisionsVisible) {
				//glm::vec3 maxPos(-1.0f, -1.0f, -1.0f), minPos(1.0f, 1.0f, 1.0f);
				for (int j = 0; j < r[i]->mesh->vertices_.size(); j++) {
					if (r[i]->mesh->vertices_[j].pos.x > maxPos.x) { maxPos.x = r[i]->mesh->vertices_[j].pos.x; }
					if (r[i]->mesh->vertices_[j].pos.y > maxPos.y) { maxPos.y = r[i]->mesh->vertices_[j].pos.y; }
					if (r[i]->mesh->vertices_[j].pos.z > maxPos.z) { maxPos.z = r[i]->mesh->vertices_[j].pos.z; }

					if (r[i]->mesh->vertices_[j].pos.x < minPos.x) { minPos.x = r[i]->mesh->vertices_[j].pos.x; }
					if (r[i]->mesh->vertices_[j].pos.y < minPos.y) { minPos.y = r[i]->mesh->vertices_[j].pos.y; }
					if (r[i]->mesh->vertices_[j].pos.z < minPos.z) { minPos.z = r[i]->mesh->vertices_[j].pos.z; }
				}

				//glm::vec3 colliderPoint_min(minPos * t[i]->getScale());
				//glm::vec3 colliderPoint_max(maxPos * t[i]->getScale());
				//
				//drawCollision(colliderPoint_min, colliderPoint_max);
			//}
		}

		glm::vec3 colliderPoint_min(minPos);
		glm::vec3 colliderPoint_max(maxPos);

		drawCollision(colliderPoint_min, colliderPoint_max);

		//colliderComponentList_[i].draw(); // Bad thing.
	}
	glUseProgram(0);
}
