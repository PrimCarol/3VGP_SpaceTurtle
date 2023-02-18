#include "st_system_render.h"

#include <map>
#include <st_gameobj_manager.h>

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

void ST::SystemRender::setUpRender(std::vector<std::optional<ST::RenderComponent>>& r, std::vector<std::optional<ST::TransformComponent>>& t, ST::Camera& cam){
	
	//ST::Material* mat = nullptr;
	
	std::vector<MyObjToRender> objs_opaque;
	std::vector<MyObjToRender> objs_translucent;

	//objs_opaque.clear();
	//objs_translucent.clear();

	for (int i = 0; i < r.size(); i++){
		
		if (r[i].has_value() && t[i].has_value()) {
			if (r[i]->visible_) {
				MyObjToRender thisObj;
				thisObj.render_ = &r[i].value();
				thisObj.transform_ = &t[i].value();

				if (!thisObj.render_->material.translucent) {
					objs_opaque.push_back(thisObj);
				}
				else {
					objs_translucent.push_back(thisObj);
				}
			}
		}
	}

	glDisable(GL_BLEND);
	doRender(objs_opaque, cam);

	std::map<float, int> sorted;
	for (int i = 0; i < objs_translucent.size(); i++){
		glm::mat4 objWorldPos = objs_translucent[i].transform_->m_world_transform_;
		glm::vec3 worldPos(objWorldPos[3][0], objWorldPos[3][1], objWorldPos[3][2]);
		float distance = glm::length(cam.transform_.getPosition() - worldPos);
		sorted[distance] = i;
	}

	std::vector<MyObjToRender> objs_translucent_sorted;
	for (std::map<float, int>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it){
		objs_translucent_sorted.push_back(objs_translucent[it->second]);
	}

	// Por defecto de momento.
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	doRender(objs_translucent_sorted, cam);

	objs_opaque.clear();
	objs_translucent.clear();
	objs_translucent_sorted.clear();

}

void ST::SystemRender::doRender(std::vector<MyObjToRender>& objs, ST::Camera& cam){
	
	std::vector<glm::mat4> sameGeometry;

	GLuint actualMeshRendering = 0;
	bool firstTime = true;

	for (int i = 0; i < objs.size(); i++){
		//if (setUpUniforms(objs[i].render_->material, objs[i].transform_, cam)) {
		//	if (objs[i].render_->mesh) {
		//		objs[i].render_->mesh->render();
		//	}
		//}

		if (firstTime) {
			actualMeshRendering = objs[i].render_->mesh->getId();
			firstTime = false;
		}

		if (objs[i].render_->mesh->getId() == actualMeshRendering) {
			sameGeometry.push_back(objs[i].transform_->m_transform_);
		}else {
			setUpUniforms(objs[i].render_->material, objs[i].transform_, cam);
			ST::Test renderTest(sameGeometry.size(), &sameGeometry);
			renderTest.render();
			sameGeometry.clear();

			actualMeshRendering = objs[i].render_->mesh->getId();
			sameGeometry.push_back(objs[i].transform_->m_transform_);
		}

		// TEST -------------------
		/*
		glm::vec3 maxPos(-1.0f, -1.0f, -1.0f), minPos(1.0f, 1.0f, 1.0f);

		if (objs[i].render_->mesh) {
			//glm::vec3 maxPos(-1.0f, -1.0f, -1.0f), minPos(1.0f, 1.0f, 1.0f);
			for (int j = 0; j < objs[i].render_->mesh->vertices_.size(); j++) {
				if (objs[i].render_->mesh->vertices_[j].pos.x > maxPos.x) { maxPos.x = objs[i].render_->mesh->vertices_[j].pos.x; }
				if (objs[i].render_->mesh->vertices_[j].pos.y > maxPos.y) { maxPos.y = objs[i].render_->mesh->vertices_[j].pos.y; }
				if (objs[i].render_->mesh->vertices_[j].pos.z > maxPos.z) { maxPos.z = objs[i].render_->mesh->vertices_[j].pos.z; }

				if (objs[i].render_->mesh->vertices_[j].pos.x < minPos.x) { minPos.x = objs[i].render_->mesh->vertices_[j].pos.x; }
				if (objs[i].render_->mesh->vertices_[j].pos.y < minPos.y) { minPos.y = objs[i].render_->mesh->vertices_[j].pos.y; }
				if (objs[i].render_->mesh->vertices_[j].pos.z < minPos.z) { minPos.z = objs[i].render_->mesh->vertices_[j].pos.z; }
			}

			//glm::vec3 worldScale(objs[i].transform_->m_world_transform_[0][0], objs[i].transform_->m_world_transform_[1][1], objs[i].transform_->m_world_transform_[2][2]);
			//glm::vec3 colliderPoint_min(minPos * worldScale);
			//glm::vec3 colliderPoint_max(maxPos * worldScale);
			
			glm::vec3 colliderPoint_min(minPos);
			glm::vec3 colliderPoint_max(maxPos);

			//glm::vec3 colliderPoint_min(minPos * objs[i].transform_->getScale());
			//glm::vec3 colliderPoint_max(maxPos * objs[i].transform_->getScale());

			drawCollision(colliderPoint_min, colliderPoint_max);
		}

		//glm::vec3 colliderPoint_min(minPos);
		//glm::vec3 colliderPoint_max(maxPos);
		//
		//drawCollision(colliderPoint_min, colliderPoint_max);
		*/
		// TEST -------------------

	}// End For

	if (sameGeometry.size() > 0) {
		setUpUniforms(objs[objs.size() - 1].render_->material, objs[objs.size() - 1].transform_, cam);
		ST::Test renderTest(sameGeometry.size(), &sameGeometry);
		renderTest.render();
	}
	sameGeometry.clear();
}

bool ST::SystemRender::setUpUniforms(ST::Material& mat, ST::TransformComponent* t, ST::Camera& cam){
	const ST::Program* p = nullptr;

	static GLuint lastTextureAlbedo = -1;
	static GLuint lastTextureNormal = -1;
	static GLuint lastTextureSpecular = -1;

	p = mat.getProgram();
	if (p) {
		p->use();
	
		// ------ Camara -------
		GLuint camPos = p->getUniform("u_view_pos");
		glm::vec3 camTransPos = cam.transform_.getPosition();
		glUniform3fv(camPos, 1, &camTransPos.x);
		GLuint camView = p->getUniform("u_view_matrix");
		glUniformMatrix4fv(camView, 1, GL_FALSE, &cam.view[0][0]);
		GLuint camProjection = p->getUniform("u_projection_matrix");
		glUniformMatrix4fv(camProjection, 1, GL_FALSE, &cam.projection[0][0]);
		GLuint camVP = p->getUniform("u_vp_matrix");
		glm::mat4 cam_m_vp = cam.projection * cam.view;
		glUniformMatrix4fv(camVP, 1, GL_FALSE, &cam_m_vp[0][0]);
		// ------ Camara -------

		if (t) {
			GLuint u_m_trans = p->getUniform("u_m_trans");
			glUniformMatrix4fv(u_m_trans, 1, GL_FALSE, &t->m_transform_[0][0]);
		}

		// Material
		GLuint mat_Uniform = -1;
		mat_Uniform = p->getUniform("u_color");
		glm::vec4 c = mat.getColor();
		glUniform4fv(mat_Uniform, 1, &c[0]);

		mat_Uniform = p->getUniform("u_shininess");
		glUniform1f(mat_Uniform, mat.shininess);

		mat_Uniform = p->getUniform("texIndex");
		glm::ivec2 texindex = mat.getTexIndex();
		glUniform2iv(mat_Uniform, 1, &texindex.x);

		mat_Uniform = p->getUniform("u_haveAlbedo");
		glUniform1i(mat_Uniform, mat.haveAlbedo);
		mat_Uniform = p->getUniform("u_haveSpecular");
		glUniform1i(mat_Uniform, mat.haveSpecular);
		mat_Uniform = p->getUniform("u_haveNormal");
		glUniform1i(mat_Uniform, mat.haveAlbedo);
		
		//int TextCount = 0;

		if (mat.haveAlbedo) {
			if (lastTextureAlbedo != mat.getAlbedo()->getID()) {
				lastTextureAlbedo = mat.getAlbedo()->getID();

				mat_Uniform = p->getUniform("rows");
				glUniform1i(mat_Uniform, mat.getAlbedo()->getRows());

				mat_Uniform = p->getUniform("cols");
				glUniform1i(mat_Uniform, mat.getAlbedo()->getCols());

				glUniform1i(p->getUniform("u_tex_Albedo"), 0);
				glActiveTexture(GL_TEXTURE0 + 0);
				glBindTexture(GL_TEXTURE_2D, mat.getAlbedo()->getID());
			}
		}
		if (mat.haveNormal) {
			if (lastTextureNormal != mat.getNormal()->getID()) {
				lastTextureNormal = mat.getNormal()->getID();

				mat_Uniform = p->getUniform("rows");
				glUniform1i(mat_Uniform, mat.getNormal()->getRows());

				mat_Uniform = p->getUniform("cols");
				glUniform1i(mat_Uniform, mat.getNormal()->getCols());

				glUniform1i(p->getUniform("u_tex_Normal"), 1);
				glActiveTexture(GL_TEXTURE0 + 1);
				glBindTexture(GL_TEXTURE_2D, mat.getNormal()->getID());
			}
		}
		if (mat.haveSpecular) {
			if (lastTextureSpecular != mat.getSpecular()->getID()) {
				lastTextureSpecular = mat.getSpecular()->getID();

				mat_Uniform = p->getUniform("rows");
				glUniform1i(mat_Uniform, mat.getSpecular()->getRows());

				mat_Uniform = p->getUniform("cols");
				glUniform1i(mat_Uniform, mat.getSpecular()->getCols());

				glUniform1i(p->getUniform("u_tex_Specular"), 2);
				glActiveTexture(GL_TEXTURE0 + 2);
				glBindTexture(GL_TEXTURE_2D, mat.getSpecular()->getID());
			}
		}

		return true;
	}
	return false;
}

void ST::SystemRender::Render(ST::GameObj_Manager& gm, ST::Camera* cam){

	std::vector<std::optional<ST::RenderComponent>>& r = *gm.getComponentVector<ST::RenderComponent>();
	std::vector<std::optional<ST::TransformComponent>>& t = *gm.getComponentVector<ST::TransformComponent>();
	
	glEnable(GL_DEPTH_TEST);

	if (cam == nullptr) {
		static std::unique_ptr<ST::Camera> cam_ = std::make_unique<ST::Camera>();
		cam = cam_.get();
	}

	cam->update();

	setUpRender(r,t, *cam);

	glUseProgram(0);

		//glm::vec3 maxPos(-1.0f, -1.0f, -1.0f), minPos(1.0f, 1.0f, 1.0f);

		//if (r[i].value().mesh) {
		//	r[i].value().mesh->render();

		//	if (renderColliders) {
		//		//glm::vec3 maxPos(-1.0f, -1.0f, -1.0f), minPos(1.0f, 1.0f, 1.0f);
		//		for (int j = 0; j < r[i]->mesh->vertices_.size(); j++) {
		//			if (r[i]->mesh->vertices_[j].pos.x > maxPos.x) { maxPos.x = r[i]->mesh->vertices_[j].pos.x; }
		//			if (r[i]->mesh->vertices_[j].pos.y > maxPos.y) { maxPos.y = r[i]->mesh->vertices_[j].pos.y; }
		//			if (r[i]->mesh->vertices_[j].pos.z > maxPos.z) { maxPos.z = r[i]->mesh->vertices_[j].pos.z; }

		//			if (r[i]->mesh->vertices_[j].pos.x < minPos.x) { minPos.x = r[i]->mesh->vertices_[j].pos.x; }
		//			if (r[i]->mesh->vertices_[j].pos.y < minPos.y) { minPos.y = r[i]->mesh->vertices_[j].pos.y; }
		//			if (r[i]->mesh->vertices_[j].pos.z < minPos.z) { minPos.z = r[i]->mesh->vertices_[j].pos.z; }
		//		}

		//		//glm::vec3 colliderPoint_min(minPos * t[i]->getScale());
		//		//glm::vec3 colliderPoint_max(maxPos * t[i]->getScale());
		//		//
		//		//drawCollision(colliderPoint_min, colliderPoint_max);
		//	}
		//}


		//if (renderColliders) {
		//	glm::vec3 colliderPoint_min(minPos);
		//	glm::vec3 colliderPoint_max(maxPos);

		//	drawCollision(colliderPoint_min, colliderPoint_max);
		//}

	//	//colliderComponentList_[i].draw(); // Bad thing.
	//}
}
