#include "st_system_render.h"

void ST::SystemRender::Render(const std::vector<ST::RenderComponent>& r, const std::vector<ST::TransformComponent>& t, ST::Camera* cam){
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
		mat = r[i].material.get();
		if (mat) {

			p = r[i].material->getProgram();

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
			glUniformMatrix4fv(u_m_trans, 1, GL_FALSE, &t[i].m_transform_[0][0]);

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
		if (r[i].mesh) {
			r[i].mesh->render();
		}

		//colliderComponentList_[i].draw(); // Bad thing.
	}
	glUseProgram(0);
}
