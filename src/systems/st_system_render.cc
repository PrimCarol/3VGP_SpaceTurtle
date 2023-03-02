#include "st_system_render.h"

#include <map>
#include <st_gameobj_manager.h>

//void drawCollision(glm::vec3 min, glm::vec3 max){
//	glBegin(GL_LINES);
//
//	glColor3f(0.0, 1.0, 0.0);
//
//	glVertex3f(max.x, max.y, max.z);
//	glVertex3f(min.x, max.y, max.z);
//
//	glVertex3f(min.x, max.y, max.z);
//	glVertex3f(min.x, max.y, min.z);
//
//	glVertex3f(min.x, max.y, min.z);
//	glVertex3f(max.x, max.y, min.z);
//
//	glVertex3f(max.x, max.y, max.z);
//	glVertex3f(max.x, max.y, min.z);
//
//	glVertex3f(max.x, min.y, max.z);
//	glVertex3f(min.x, min.y, max.z);
//
//	glVertex3f(min.x, min.y, max.z);
//	glVertex3f(min.x, min.y, min.z);
//
//	glVertex3f(min.x, min.y, min.z);
//	glVertex3f(max.x, min.y, min.z);
//
//	glVertex3f(max.x, min.y, max.z);
//	glVertex3f(max.x, min.y, min.z);
//
//	glVertex3f(max.x, min.y, max.z);
//	glVertex3f(max.x, max.y, max.z);
//
//	glVertex3f(max.x, min.y, min.z);
//	glVertex3f(max.x, max.y, min.z);
//
//	glVertex3f(min.x, min.y, max.z);
//	glVertex3f(min.x, max.y, max.z);
//
//	glVertex3f(min.x, min.y, min.z);
//	glVertex3f(min.x, max.y, min.z);
//
//	//glVertex3f(-size_.x, -size_.y, -size_.z);
//	glEnd();
//}

void ST::SystemRender::setUpRender(std::vector<std::optional<ST::RenderComponent>>& render, std::vector<std::optional<ST::TransformComponent>>& transform, MyCamera& cam){
	
	//ST::Material* mat = nullptr;

	std::vector<MyObjToRender> objs_opaque;
	std::vector<MyObjToRender> objs_translucent;

	// ----- Opacos -----
	for (int i = 0; i < render.size(); i++){
		
		if (render[i].has_value() && transform[i].has_value()) {
			if (render[i]->visible_) {
				MyObjToRender thisObj;
				thisObj.render_ = &render[i].value();
				thisObj.transform_ = &transform[i].value();

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

	// ----- Translucidos -----
	bool sortTranslucents = false; // <---------- Temporal

	if (sortTranslucents) {
		std::map<float, int> sorted;
		for (int i = 0; i < objs_translucent.size(); i++){
			glm::mat4 objWorldPos = objs_translucent[i].transform_->m_world_transform_;
			glm::vec3 worldPos(objWorldPos[3][0], objWorldPos[3][1], objWorldPos[3][2]);
			float distance = glm::length(cam.transform_->getPosition() - worldPos);
			sorted[distance] = i;
		}

		std::vector<MyObjToRender> objs_translucent_sorted;
		
		for (std::map<float, int>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it) {
			objs_translucent_sorted.push_back(objs_translucent[it->second]);
		}

		// Por defecto de momento.
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		doRender(objs_translucent_sorted, cam);

		objs_translucent_sorted.clear();
	}else {
		// Por defecto de momento.
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		doRender(objs_translucent, cam);
	}

	objs_opaque.clear();
	objs_translucent.clear();

}

void ST::SystemRender::doRender(std::vector<MyObjToRender>& objs, MyCamera& cam){
	
	std::vector<InstanceInfo> instancing;

	GLuint actualMeshRendering = 0;
	GLuint actualTextureRendering = 0;
	int lastIndice = 0;
	bool firstTime = true;

	for (int i = 0; i < objs.size(); i++){

		if (firstTime) {
			actualMeshRendering = objs[i].render_->mesh->getID();
			if (objs[i].render_->material.haveAlbedo) {
				actualTextureRendering = objs[i].render_->material.getAlbedo()->getID();
				objs[i].render_->material.getAlbedo()->bind();
			}
			firstTime = false;
		}

		if (objs[i].render_->mesh->getID() != actualMeshRendering) {
			setUpUniforms(objs[lastIndice].render_->material, objs[lastIndice].transform_, cam);
			objs[lastIndice].render_->mesh->setInstanceData(instancing);
			objs[lastIndice].render_->mesh->render();
			instancing.clear();

			actualMeshRendering = objs[i].render_->mesh->getID();
		}

		if (objs[i].render_->material.haveAlbedo) {
			if (objs[i].render_->material.getAlbedo()->getID() != actualTextureRendering) {
				setUpUniforms(objs[lastIndice].render_->material, objs[lastIndice].transform_, cam);
				objs[lastIndice].render_->mesh->setInstanceData(instancing);
				objs[lastIndice].render_->mesh->render();
				instancing.clear();

				actualTextureRendering = objs[i].render_->material.getAlbedo()->getID();
				objs[i].render_->material.getAlbedo()->bind();
			}
		}

		instancing.push_back({ objs[i].transform_->m_transform_,
							   objs[i].render_->material.getColor(),
							   objs[i].render_->material.getTexIndex(),
							   objs[i].render_->material.shininess });
		lastIndice = i;

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

	if (instancing.size() > 0) {
		setUpUniforms(objs[lastIndice].render_->material, objs[lastIndice].transform_, cam);
		objs[lastIndice].render_->mesh->setInstanceData(instancing);
		objs[lastIndice].render_->mesh->render();
		instancing.clear();
	}
}

bool ST::SystemRender::setUpUniforms(ST::Material& mat, ST::TransformComponent* t, MyCamera& cam){
	const ST::Program* p = nullptr;

	static GLuint lastTextureAlbedo = -1;
	static GLuint lastTextureNormal = -1;
	static GLuint lastTextureSpecular = -1;

	p = mat.getProgram();
	if (p) {
		p->use();

		// ------ Camara -------
		GLuint camPos = p->getUniform("u_view_pos");
		glm::vec3 camTransPos = cam.transform_->getPosition();
		glUniform3fv(camPos, 1, &camTransPos.x);
		GLuint camView = p->getUniform("u_view_matrix");
		glUniformMatrix4fv(camView, 1, GL_FALSE, &cam.cam_->view[0][0]);
		GLuint camProjection = p->getUniform("u_projection_matrix");
		glUniformMatrix4fv(camProjection, 1, GL_FALSE, &cam.cam_->projection[0][0]);
		GLuint camVP = p->getUniform("u_vp_matrix");
		glm::mat4 cam_m_vp = cam.cam_->projection * cam.cam_->view;
		glUniformMatrix4fv(camVP, 1, GL_FALSE, &cam_m_vp[0][0]);
		// ------ Camara -------


		// Material
		GLuint mat_Uniform = -1;

		mat_Uniform = p->getUniform("u_haveAlbedo");
		glUniform1i(mat_Uniform, mat.haveAlbedo);
		mat_Uniform = p->getUniform("u_haveSpecular");
		glUniform1i(mat_Uniform, mat.haveSpecular);
		mat_Uniform = p->getUniform("u_haveNormal");
		glUniform1i(mat_Uniform, mat.haveAlbedo);

		if (mat.haveAlbedo) {
			if (lastTextureAlbedo != mat.getAlbedo()->getID()) {
				lastTextureAlbedo = mat.getAlbedo()->getID();

				mat_Uniform = p->getUniform("rows");
				glUniform1i(mat_Uniform, mat.getAlbedo()->getRows());

				mat_Uniform = p->getUniform("cols");
				glUniform1i(mat_Uniform, mat.getAlbedo()->getCols());

				mat_Uniform = p->getUniform("sizeTileX");
				glUniform1i(mat_Uniform, mat.getAlbedo()->width() / mat.getAlbedo()->getCols());

				mat_Uniform = p->getUniform("sizeTileY");
				glUniform1i(mat_Uniform, mat.getAlbedo()->height() / mat.getAlbedo()->getRows());

				glUniform1i(p->getUniform("u_tex_Albedo"), 0);
				glActiveTexture(GL_TEXTURE0 + 0);
				glBindTexture(GL_TEXTURE_2D, mat.getAlbedo()->getID());
			}
		}
		if (mat.haveNormal) {
			if (lastTextureNormal != mat.getNormal()->getID()) {
				lastTextureNormal = mat.getNormal()->getID();

				/*mat_Uniform = p->getUniform("rows");
				glUniform1i(mat_Uniform, mat.getNormal()->getRows());

				mat_Uniform = p->getUniform("cols");
				glUniform1i(mat_Uniform, mat.getNormal()->getCols());*/

				glUniform1i(p->getUniform("u_tex_Normal"), 1);
				glActiveTexture(GL_TEXTURE0 + 1);
				glBindTexture(GL_TEXTURE_2D, mat.getNormal()->getID());
			}
		}
		if (mat.haveSpecular) {
			if (lastTextureSpecular != mat.getSpecular()->getID()) {
				lastTextureSpecular = mat.getSpecular()->getID();

				/*mat_Uniform = p->getUniform("rows");
				glUniform1i(mat_Uniform, mat.getSpecular()->getRows());

				mat_Uniform = p->getUniform("cols");
				glUniform1i(mat_Uniform, mat.getSpecular()->getCols());*/

				glUniform1i(p->getUniform("u_tex_Specular"), 2);
				glActiveTexture(GL_TEXTURE0 + 2);
				glBindTexture(GL_TEXTURE_2D, mat.getSpecular()->getID());
			}
		}

		return true;
	}
	return false;
}

void ST::SystemRender::Render(ST::GameObj_Manager& gm){

	std::vector<std::optional<ST::RenderComponent>>& r = *gm.getComponentVector<ST::RenderComponent>();
	std::vector<std::optional<ST::TransformComponent>>& t = *gm.getComponentVector<ST::TransformComponent>();
	
	glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_FALSE);

	/*if (cam == nullptr) {
		static std::unique_ptr<ST::Camera> cam_ = std::make_unique<ST::Camera>();
		cam = cam_.get();
	}*/

	//cam->update();

	if (gm.mainCameraID >= 0) {
		if (t[gm.mainCameraID].has_value()) {
			MyCamera cam;
			cam.transform_ = &t[gm.mainCameraID].value();
			if (gm.getComponentVector<ST::CameraComponent>()->at(gm.mainCameraID).has_value()) {
				cam.cam_ = &gm.getComponentVector<ST::CameraComponent>()->at(gm.mainCameraID).value();
				setUpRender(r, t, cam);
			}
		}
	}

	//glUseProgram(0);
}
