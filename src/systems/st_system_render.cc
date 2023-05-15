#include "st_system_render.h"

#include <map>
#include <st_gameobj_manager.h>

#include <components/st_collider.h>

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

//void ST::SystemRender::setUpRender(ST::GameObj_Manager& gm, /*std::vector<std::optional<ST::RenderComponent>>& render, std::vector<std::optional<ST::TransformComponent>>& transform,*/ MyCamera& cam){
//	
//	//ST::Material* mat = nullptr;
//	auto& render = *gm.getComponentVector<ST::RenderComponent>();
//	auto& transform = *gm.getComponentVector<ST::TransformComponent>();
//
//
//	std::vector<MyObjToRender> objs_opaque;
//	std::vector<MyObjToRender> objs_translucent;
//
//	// ----- Opacos -----
//	for (int i = 0; i < render.size(); i++){
//		
//		if (render[i].has_value() && transform[i].has_value()) {
//			if (render[i]->visible_) {
//				MyObjToRender thisObj;
//				thisObj.render_ = &render[i].value();
//				thisObj.transform_ = &transform[i].value();
//
//				if (!thisObj.render_->material.translucent) {
//					objs_opaque.push_back(thisObj);
//				}
//				else {
//					objs_translucent.push_back(thisObj);
//				}
//			}
//		}
//	}
//
//	glDisable(GL_BLEND);
//	doRender(objs_opaque, cam);
//
//	// ----- Translucidos -----
//	bool sortTranslucents = false; // <---------- Temporal
//
//	if (sortTranslucents) {
//		std::map<float, int> sorted;
//		for (int i = 0; i < objs_translucent.size(); i++){
//			glm::mat4 objWorldPos = objs_translucent[i].transform_->m_world_transform_;
//			glm::vec3 worldPos(objWorldPos[3][0], objWorldPos[3][1], objWorldPos[3][2]);
//			float distance = glm::length(cam.transform_->getPosition() - worldPos);
//			sorted[distance] = i;
//		}
//
//		std::vector<MyObjToRender> objs_translucent_sorted;
//		
//		for (std::map<float, int>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it) {
//			objs_translucent_sorted.push_back(objs_translucent[it->second]);
//		}
//
//		// Por defecto de momento.
//		glEnable(GL_BLEND);
//		glBlendEquation(GL_FUNC_ADD);
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//		doRender(objs_translucent_sorted, cam);
//
//		objs_translucent_sorted.clear();
//	}else {
//		// Por defecto de momento.
//		glEnable(GL_BLEND);
//		glBlendEquation(GL_FUNC_ADD);
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//		doRender(objs_translucent, cam);
//	}
//
//	objs_opaque.clear();
//	objs_translucent.clear();
//
//}

void ST::SystemRender::doRender(std::vector<MyObjToRender>& objs, MyCamera& cam, ST::GameObj_Manager& gm){
	
	std::vector<InstanceInfo> instancing;

	GLuint actualProgram = 0;
	GLuint actualMeshRendering = 0;
	
	bool actualhaveTexture = false;
	GLuint actualTextureRendering = 0;

	int lastIndice = 0;
	bool firstTime = true;

	bool popInstances = false;

	for (int i = 0; i < objs.size(); i++){

		if (firstTime) {
			const ST::Program* p = objs[i].render_->material.getProgram();
			if (p) {
				actualProgram = p->getID();
			}else {
				//printf("Object don't have program.\n");
				continue;
			}
			actualMeshRendering = objs[i].render_->mesh->getID();
			if (objs[i].render_->material.haveAlbedo) {
				actualhaveTexture = true;
				actualTextureRendering = objs[i].render_->material.getAlbedo()->getID();
			}
			firstTime = false;
		}

		// Si no tienen el mismo program.
		const ST::Program* p = objs[i].render_->material.getProgram();
		if (p) {
			if (p->getID() != actualProgram) {
				popInstances = true;
				actualProgram = p->getID();
			}
		}

		// Si unos tenian textura y este no, o al reves.
		if (objs[i].render_->material.haveAlbedo) {
			if (objs[i].render_->material.getAlbedo()->getID() != actualTextureRendering) {
				actualTextureRendering = objs[i].render_->material.getAlbedo()->getID();
				popInstances = true;
			}
			if (objs[i].render_->material.haveAlbedo != actualhaveTexture) {
				popInstances = true;
			}
			actualhaveTexture = objs[i].render_->material.haveAlbedo;
		} else {
			if (actualhaveTexture) {
				popInstances = true;
				actualTextureRendering = 0;
			}
			actualhaveTexture = false;
		}

		// Si tienen una mesh distinta.
		if (objs[i].render_->mesh->getID() != actualMeshRendering) {
			popInstances = true;
			actualMeshRendering = objs[i].render_->mesh->getID();
		}

		if (popInstances) {
			gm.drawcalls_++;

			//glEnable(GL_CULL_FACE);
			//glCullFace(GL_BACK);
			objs[lastIndice].render_->mesh->cullmode_ = objs[lastIndice].render_->thiscullmode_;
			objs[lastIndice].render_->mesh->depthmode_ = objs[lastIndice].render_->thisdepthmode_;

			setUpUniforms(objs[lastIndice].render_->material, objs[lastIndice].transform_, cam, gm);
			objs[lastIndice].render_->mesh->setInstanceData(instancing);
			objs[lastIndice].render_->mesh->render();
			instancing.clear();

			popInstances = false;
		}

		instancing.push_back({ objs[i].transform_->m_transform_,
							   objs[i].render_->material.getColor(),
							   objs[i].render_->material.getTexIndex(),
							   objs[i].render_->material.shininess });
		lastIndice = i;

	}// End For

	// Para pintar los ultimos objetos iguales.
	if (instancing.size() > 0) {
		gm.drawcalls_++;

		objs[lastIndice].render_->mesh->cullmode_ = objs[lastIndice].render_->thiscullmode_;
		objs[lastIndice].render_->mesh->depthmode_ = objs[lastIndice].render_->thisdepthmode_;

		setUpUniforms(objs[lastIndice].render_->material, objs[lastIndice].transform_, cam, gm);
		objs[lastIndice].render_->mesh->setInstanceData(instancing);
		objs[lastIndice].render_->mesh->render();
		instancing.clear();
	}
}

bool ST::SystemRender::setUpUniforms(ST::Material& mat, ST::TransformComponent* t,
									 MyCamera& cam, ST::GameObj_Manager& gm){
	const ST::Program* p = nullptr;

	p = mat.getProgram();
	//if (p) {
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
			//if (lastTextureAlbedo != mat.getAlbedo()->getID()) {
			//	lastTextureAlbedo = mat.getAlbedo()->getID();

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
				glBindTexture(mat.getAlbedo()->getTypeGL(), mat.getAlbedo()->getID());
			//}
		}
		if (mat.haveNormal) {
			//if (lastTextureNormal != mat.getNormal()->getID()) {
			//	lastTextureNormal = mat.getNormal()->getID();

				/*mat_Uniform = p->getUniform("rows");
				glUniform1i(mat_Uniform, mat.getNormal()->getRows());

				mat_Uniform = p->getUniform("cols");
				glUniform1i(mat_Uniform, mat.getNormal()->getCols());*/

				glUniform1i(p->getUniform("u_tex_Normal"), 1);
				glActiveTexture(GL_TEXTURE0 + 1);
				glBindTexture(GL_TEXTURE_2D, mat.getNormal()->getID());
			//}
		}
		if (mat.haveSpecular) {
			//if (lastTextureSpecular != mat.getSpecular()->getID()) {
			//	lastTextureSpecular = mat.getSpecular()->getID();

				/*mat_Uniform = p->getUniform("rows");
				glUniform1i(mat_Uniform, mat.getSpecular()->getRows());

				mat_Uniform = p->getUniform("cols");
				glUniform1i(mat_Uniform, mat.getSpecular()->getCols());*/

				glUniform1i(p->getUniform("u_tex_Specular"), 2);
				glActiveTexture(GL_TEXTURE0 + 2);
				glBindTexture(GL_TEXTURE_2D, mat.getSpecular()->getID());
			//}
		}

		// Shadow Mapping
		/*glUniform1i(p->getUniform("u_haveShadowMap"), gm.haveShadowMap_);
		
		glUniform1i(p->getUniform("shadowMap"), 3);
		glActiveTexture(GL_TEXTURE0 + 3);
		glBindTexture(GL_TEXTURE_2D, gm.shadowMap.textureID());

		GLuint lighSpaceMatrix = p->getUniform("lightSpaceMatrix");
		glUniformMatrix4fv(lighSpaceMatrix, 1, GL_FALSE, &gm.shadowMappingMatTest[0][0]);*/

		return true;
	//}
	//return false;
}

void ST::SystemRender::Render(ST::GameObj_Manager& gm, const ST::Program& p) {

	//gm.drawcalls_ = 0;

	auto& render = *gm.getComponentVector<ST::RenderComponent>();
	auto& transform = *gm.getComponentVector<ST::TransformComponent>();

	//glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_FALSE);

	// Buscamos si hay una camara como Main camera,
	//si no la hay, buscamos la primera que encontremos y la ponemos como Main.
	auto camVector = gm.getComponentVector<ST::CameraComponent>();
	if (gm.mainCameraID() == -1) {
		for (int i = 0; i < camVector->size(); i++) {
			if (camVector->at(i).has_value()) {
				ST::GameObj tempObj(i, gm);
				gm.setMainCamera(tempObj);
			}
		}
	}

	// ----------- Renderizamos ------------
	if (gm.mainCameraID() != -1) {
		if (transform[gm.mainCameraID()].has_value()) {
			//MyCamera cam;
			//cam.transform_ = &t[gm.mainCameraID()].value();
			//if (camVector->at(gm.mainCameraID()).has_value()) {
			//	cam.cam_ = &camVector->at(gm.mainCameraID()).value();
			//	//setUpRender(/*r, t,*/gm, cam);
			//}

			MyCamera cam;
			cam.cam_ = &camVector->at(gm.mainCameraID()).value();
			cam.transform_ = &transform[gm.mainCameraID()].value();

			std::vector<MyObjToRender> objs_opaque;
			std::vector<MyObjToRender> objs_translucent;

			GLenum error = glGetError();
			if (error != GL_NO_ERROR) {
				printf("Render Start-> OpenGL Error: %d\n", error);
			}

			// ----- Opacos -----
			for (int i = 0; i < render.size(); i++) {

				if (render[i].has_value() && transform[i].has_value()) {
					if (render[i]->visible_) {
						if (render[i]->material.getProgram() && render[i]->material.getProgram()->getID() == p.getID()) {
							MyObjToRender thisObj;
							thisObj.render_ = &render[i].value();
							thisObj.transform_ = &transform[i].value();

							if (!thisObj.render_->material.translucent) {
								objs_opaque.push_back(thisObj);
							}
							else {
								objs_translucent.push_back(thisObj);
							}

							// ------ Dibujamos sus normales. -------
							if (i == gm.objectSelected) {
								//ST::Program& normalProgram = *gm.normalsProgram;
								//normalProgram.use();
								//// ------ Camara -------
								//glUniformMatrix4fv(normalProgram.getUniform("u_view_matrix"), 1, GL_FALSE, &cam.cam_->view[0][0]);
								//glUniformMatrix4fv(normalProgram.getUniform("u_projection_matrix"), 1, GL_FALSE, &cam.cam_->projection[0][0]);
								//// ------ Camara -------
								//std::vector<InstanceInfo> instancing;
								//instancing.push_back({ thisObj.transform_->m_transform_,
								//					   thisObj.render_->material.getColor(),
								//					   thisObj.render_->material.getTexIndex(),
								//					   thisObj.render_->material.shininess });
								//thisObj.render_->mesh->setInstanceData(instancing);
								//thisObj.render_->mesh->render();

								//ST::ColliderComponent* collierComp = gm.getComponent<ST::ColliderComponent>(i);
								//if (collierComp) {
								//	ST::Program& colliderProgram = *gm.colliderProgram;
								//	colliderProgram.use();
								//	// ------ Camara -------
								//	glUniformMatrix4fv(colliderProgram.getUniform("u_view_matrix"), 1, GL_FALSE, &cam.cam_->view[0][0]);
								//	glUniformMatrix4fv(colliderProgram.getUniform("u_projection_matrix"), 1, GL_FALSE, &cam.cam_->projection[0][0]);

								//	glm::vec3 min = collierComp->getMinPoint();
								//	glm::vec3 max = collierComp->getMaxPoint();
								//	glUniform3fv(colliderProgram.getUniform("u_minColliderPos"), 1, &min.x);
								//	glUniform3fv(colliderProgram.getUniform("u_maxColliderPos"), 1, &max.x);
	
								//	thisObj.render_->mesh->render();
								//}
							}
						}
					}
				}
			}

			glDisable(GL_BLEND);
			doRender(objs_opaque, cam, gm);

			error = glGetError();
			if (error != GL_NO_ERROR) {
				printf("Render Opaques End -> OpenGL Error: %d\n", error);
			}

			// ----- Translucidos -----
			//bool sortTranslucents = false; // <---------- Temporal

			//if (sortTranslucents) {
			//	std::map<float, int> sorted;
			//	for (int i = 0; i < objs_translucent.size(); i++) {
			//		glm::mat4 objWorldPos = objs_translucent[i].transform_->m_world_transform_;
			//		glm::vec3 worldPos(objWorldPos[3][0], objWorldPos[3][1], objWorldPos[3][2]);
			//		float distance = glm::length(cam.transform_->getPosition() - worldPos);
			//		sorted[distance] = i;
			//	}

			//	std::vector<MyObjToRender> objs_translucent_sorted;

			//	for (std::map<float, int>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it) {
			//		objs_translucent_sorted.push_back(objs_translucent[it->second]);
			//	}

			//	// Por defecto de momento.
			//	glEnable(GL_BLEND);
			//	glBlendEquation(GL_FUNC_ADD);
			//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			//	doRender(objs_translucent_sorted, cam, gm);

			//	objs_translucent_sorted.clear();
			//}
			//else {
			//	// Por defecto de momento.
			//	glEnable(GL_BLEND);
			//	glBlendEquation(GL_FUNC_ADD);
			//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			//	doRender(objs_translucent, cam, gm);
			//}

			glEnable(GL_BLEND);
			glBlendEquation(GL_FUNC_ADD);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			doRender(objs_translucent, cam, gm);

			objs_opaque.clear();
			objs_translucent.clear();

		}
	}

	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("Render Exit-> OpenGL Error: %d\n", error);
	}

	//glUseProgram(0);
}
