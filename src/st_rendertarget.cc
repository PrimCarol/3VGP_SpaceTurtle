#include "st_rendertarget.h"
#include <stdio.h>

#include <st_gameobj_manager.h>
#include <st_system_assets.h>
#include <st_transform.h>
#include <st_camera.h>
#include <st_program.h>
#include <st_system_light.h>
#include <random>

GLenum RenderTypeToGL(ST::RenderTarget::RenderType rt) {
	GLenum aux = GL_NONE;
	switch (rt){
	case ST::RenderTarget::RT_Color:
		aux = GL_COLOR_ATTACHMENT0;
		break;
	case ST::RenderTarget::RT_Depth:
		aux = GL_DEPTH_ATTACHMENT;
		break;
	case ST::RenderTarget::RT_Stencil:
		aux = GL_STENCIL_ATTACHMENT;
		break;
	default:
		printf("Render Type >> Invalid Format");
		break;
	}

	return aux;
}

float lerp(float a, float b, float f){
	return a + f * (b - a);
}

ST::RenderTarget::RenderTarget(){
	glGenFramebuffers(1, &internalID);
	glGetIntegerv(GL_VIEWPORT, last_viewport);
	
	width_ = 0;
	height_ = 0;

	quadID = 0;

	visualMode = 0;
	ssaoActive = true;

	createQuadToRender();

	std::uniform_real_distribution<float> randomFloats(0.0, 1.0); // random floats between [0.0, 1.0]
	std::default_random_engine generator;
	for (unsigned int i = 0; i < 64; ++i){
		glm::vec3 sample(
			randomFloats(generator) * 2.0 - 1.0,
			randomFloats(generator) * 2.0 - 1.0,
			randomFloats(generator)
		);
		sample = glm::normalize(sample);
		sample *= randomFloats(generator);

		float scale = (float)i / 64.0;
		scale = lerp(0.1f, 1.0f, scale * scale);
		sample *= scale;
		ssaoKernel.push_back(sample);
	}

	std::vector<glm::vec3> ssaoNoise;
	for (unsigned int i = 0; i < 16; i++){
		glm::vec3 noise(
			randomFloats(generator) * 2.0 - 1.0,
			randomFloats(generator) * 2.0 - 1.0,
			0.0f);
		ssaoNoise.push_back(noise);
	}

	glGenTextures(1, &noiseTexture);
	glBindTexture(GL_TEXTURE_2D, noiseTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 4, 4, 0, GL_RGB, GL_FLOAT, &ssaoNoise[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void ST::RenderTarget::addTexture(int w, int h, const char* name, ST::Texture::Format f, ST::Texture::Format internalf, ST::Texture::DataType dt, ST::Texture::TextType t){
	width_ = w;
	height_ = h;

	glBindFramebuffer(GL_FRAMEBUFFER, internalID);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("RenderTarget 01 -> OpenGL Error: %d\n", error);
	}

	textureToRender_.push_back(std::make_shared<ST::Texture>());
	textureToRender_.back()->init(width_, height_, t, dt, f, internalf);
	textureToRender_.back()->set_wrap_s(ST::Texture::W_CLAMP_TO_BORDER);
	textureToRender_.back()->set_wrap_t(ST::Texture::W_CLAMP_TO_BORDER);
	textureToRender_.back()->bind();

	if (f == ST::Texture::F_DEPTH) {
		glFramebufferTexture2D(GL_FRAMEBUFFER, RenderTypeToGL(RT_Depth), textureToRender_.back()->getTypeGL(), textureToRender_.back()->getID(), 0);
		textureToRender_.back()->set_data(0);
	}else {
		glFramebufferTexture2D(GL_FRAMEBUFFER, RenderTypeToGL(RT_Color) + textureCount(), textureToRender_.back()->getTypeGL(), textureToRender_.back()->getID(), 0);
		textureToRender_.back()->set_data(0);

		texturesTypeRender_.push_back(RenderTypeToGL(RT_Color) + textureCount());
	}
	texturesUniformName_.push_back(name);
	
	error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("RenderTarget 02 -> OpenGL Error: %d\n", error);
	}

	if (f != ST::Texture::F_DEPTH) {
		glDrawBuffers(textureCount(), &texturesTypeRender_.front());
	}

	error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("RenderTarget 03 -> OpenGL Error: %d\n", error);
	}

	textureToRender_.back()->unbind();
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

int ST::RenderTarget::textureCount(){
	return textureToRender_.size();
}

void ST::RenderTarget::nextVisualMode(){
	visualMode++;
	if (visualMode >= textureCount()) {
		visualMode = 0;
	}
}

void ST::RenderTarget::activateSSAO(bool a){
	ssaoActive = a;
}

void ST::RenderTarget::createQuadToRender(){

	// El Quad para renderizar.
	float quadVertices[] = {
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	const GLuint quadIndices[] = {
		0, 2, 1,
		0, 3, 2
	};

	GLuint quadVBO;
	glGenVertexArrays(1, &quadID);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadID);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

void ST::RenderTarget::renderOnScreen(ST::GameObj_Manager& gm, std::vector<ST::LightsStruct>* lights){

	auto camVector = gm.getComponentVector<ST::CameraComponent>();
	if (gm.mainCameraID() == -1) {
		for (int i = 0; i < camVector->size(); i++) {
			if (camVector->at(i).has_value()) {
				ST::GameObj tempObj(i, gm);
				gm.setMainCamera(tempObj);
			}
		}
	}
	
	if (quadID != 0 && gm.mainCameraID() >= 0) {

		auto camTrans = gm.getComponentVector<ST::TransformComponent>()->at(gm.mainCameraID()).value();
		auto camComp = gm.getComponentVector<ST::CameraComponent>()->at(gm.mainCameraID()).value();

		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			printf("Render FrameBuffer-> OpenGL Error: %d\n", error);
		}

		glBindVertexArray(quadID);

		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_ONE, GL_ONE);

		if (lights) {		

			// ----- Light Pass ------
			gm.framebufferProgram->use();

			for (int i = 0; i < textureCount(); i++) {
				glUniform1i(glGetUniformLocation(gm.framebufferProgram->getID(), texturesUniformName_.at(i)), i);
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, textureToRender_.at(i)->getID());
			}

			if (gm.skybox_) {
				ST::RenderComponent* skyboxRender = gm.skybox_->getComponent<ST::RenderComponent>();
				ST::TransformComponent* skyboxTrans = gm.skybox_->getComponent<ST::TransformComponent>();
				if (skyboxTrans) {
					skyboxTrans->setPosition(camTrans.getPosition());
				}
				if (skyboxRender && skyboxRender->material.haveAlbedo) {
					glUniform1i(gm.framebufferProgram->getUniform("gSkybox"), 6);
					glActiveTexture(GL_TEXTURE0 + 6);
					glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxRender->material.getAlbedo()->getID());
				}
			}

			// Temporal <--------------------------------
			glm::vec3 viewPos = camTrans.getPosition();
			glUniform1i(glGetUniformLocation(gm.framebufferProgram->getID(), "visualMode"), visualMode);
			glUniform3fv(glGetUniformLocation(gm.framebufferProgram->getID(), "viewPos"), 1, &viewPos.x);
			//View Matrix
			glUniformMatrix4fv(gm.framebufferProgram->getUniform("viewMatrix"), 1, GL_FALSE, &camComp.view[0][0]);
			glUniformMatrix4fv(gm.framebufferProgram->getUniform("projMatrix"), 1, GL_FALSE, &camComp.projection[0][0]);

			for (int i = 0; i < lights->size(); i++){
				//Uniforms
				ST::LightComponent* tempLight = lights->at(i).light_;

				// Directional
				if (tempLight->type_ == ST::Directional) {
					
					glUniform3f(gm.framebufferProgram->getUniform("u_DirectLight.direction"), tempLight->direction_.x, tempLight->direction_.y, tempLight->direction_.z);
					glUniform3f(gm.framebufferProgram->getUniform("u_DirectLight.ambient"), tempLight->ambient_.x, tempLight->ambient_.y, tempLight->ambient_.z);
					glUniform3f(gm.framebufferProgram->getUniform("u_DirectLight.diffuse"), tempLight->diffuse_.x, tempLight->diffuse_.y, tempLight->diffuse_.z);
					glUniform3f(gm.framebufferProgram->getUniform("u_DirectLight.specular"), tempLight->specular_.x, tempLight->specular_.y, tempLight->specular_.z);

					if (tempLight->haveShadow_) {
						// ShadowMapping
						glUniform1f(gm.framebufferProgram->getUniform("cascadeEndShadow[0]"), tempLight->shadowHighRadius_);
						glUniformMatrix4fv(gm.framebufferProgram->getUniform("lightSpaceMatrix[0]"), 1, GL_FALSE, &tempLight->matrixlighShadowHigh_[0][0]);
						glUniform1i(gm.framebufferProgram->getUniform("shadowMap[0]"), 7);
						glActiveTexture(GL_TEXTURE0 + 7);
						glBindTexture(GL_TEXTURE_2D, tempLight->shadowHigh->textureID());
						glUniform1f(gm.framebufferProgram->getUniform("cascadeEndShadow[1]"), tempLight->shadowMediumRadius_);
						glUniformMatrix4fv(gm.framebufferProgram->getUniform("lightSpaceMatrix[1]"), 1, GL_FALSE, &tempLight->matrixlighShadowMedium_[0][0]);
						glUniform1i(gm.framebufferProgram->getUniform("shadowMap[1]"), 8);
						glActiveTexture(GL_TEXTURE0 + 8);
						glBindTexture(GL_TEXTURE_2D, tempLight->shadowMedium->textureID());
						glUniform1f(gm.framebufferProgram->getUniform("cascadeEndShadow[2]"), tempLight->shadowLowRadius_);
						glUniformMatrix4fv(gm.framebufferProgram->getUniform("lightSpaceMatrix[2]"), 1, GL_FALSE, &tempLight->matrixlighShadowLow_[0][0]);
						glUniform1i(gm.framebufferProgram->getUniform("shadowMap[2]"), 9);
						glActiveTexture(GL_TEXTURE0 + 9);
						glBindTexture(GL_TEXTURE_2D, tempLight->shadowLow->textureID());
					}
				}
				// Point
				if (tempLight->type_ == ST::Point) {

					glUniform3f(gm.framebufferProgram->getUniform("u_PointLight.position"), tempLight->position_.x, tempLight->position_.y, tempLight->position_.z);
					glUniform3f(gm.framebufferProgram->getUniform("u_PointLight.ambient"), tempLight->color_.x, tempLight->color_.y, tempLight->color_.z);
					glUniform3f(gm.framebufferProgram->getUniform("u_PointLight.diffuse"), tempLight->color_.x, tempLight->color_.y, tempLight->color_.z);
					glUniform3f(gm.framebufferProgram->getUniform("u_PointLight.specular"), tempLight->color_.x, tempLight->color_.y, tempLight->color_.z);
					glUniform1f(gm.framebufferProgram->getUniform("u_PointLight.linear"), tempLight->linear_);
					glUniform1f(gm.framebufferProgram->getUniform("u_PointLight.quadratic"), tempLight->quadratic_);
					const float maxBrightness = std::fmaxf(std::fmaxf(tempLight->color_.r, tempLight->color_.g), tempLight->color_.b);
					float radius = (-tempLight->linear_ + std::sqrt(tempLight->linear_ * tempLight->linear_ - 4 * tempLight->quadratic_ * (1.0 - (256.0f / 5.0f) * maxBrightness))) / (2.0f * tempLight->quadratic_);
					glUniform1f(gm.framebufferProgram->getUniform("u_PointLight.radius"), radius);

					// ShadowMapping
					/*glUniform1f(Shader.getUniform("far_plane"), 25.0f);
					glUniform1i(Shader.getUniform("shadowMapPointLight"), 6);
					glActiveTexture(GL_TEXTURE0 + 6);
					glBindTexture(GL_TEXTURE_CUBE_MAP, lights->at(i).renderTarget_[0].textureID());*/

					error = glGetError();
					if (error != GL_NO_ERROR) {
						printf("PointLight-> OpenGL Error: %d\n", error);
					}
				}
				// Spot
				if (tempLight->type_ == ST::Spot) {
					glUniform3f(gm.framebufferProgram->getUniform("u_SpotLight.position"), tempLight->position_.x, tempLight->position_.y, tempLight->position_.z);
					glUniform3f(gm.framebufferProgram->getUniform("u_SpotLight.ambient"), tempLight->color_.x, tempLight->color_.y, tempLight->color_.z);
					glUniform3f(gm.framebufferProgram->getUniform("u_SpotLight.diffuse"), tempLight->color_.x, tempLight->color_.y, tempLight->color_.z);
					glUniform3f(gm.framebufferProgram->getUniform("u_SpotLight.specular"), tempLight->color_.x, tempLight->color_.y, tempLight->color_.z);
					glUniform1f(gm.framebufferProgram->getUniform("u_SpotLight.linear"), tempLight->linear_);
					glUniform1f(gm.framebufferProgram->getUniform("u_SpotLight.quadratic"), tempLight->quadratic_);
					glUniform3f(gm.framebufferProgram->getUniform("u_SpotLight.direction"), tempLight->direction_.x, tempLight->direction_.y, tempLight->direction_.z);
					glUniform1f(gm.framebufferProgram->getUniform("u_SpotLight.cutOff"), tempLight->cutOff_);
					glUniform1f(gm.framebufferProgram->getUniform("u_SpotLight.outerCutOff"), tempLight->outerCutOff_);

					if (tempLight->haveShadow_) {
						// ShadowMapping
						glUniformMatrix4fv(gm.framebufferProgram->getUniform("lightSpaceMatrix[0]"), 1, GL_FALSE, &tempLight->matrixlighShadowHigh_[0][0]);
						glUniform1i(gm.framebufferProgram->getUniform("shadowMap[0]"), 7);
						glActiveTexture(GL_TEXTURE0 + 7);
						glBindTexture(GL_TEXTURE_2D, tempLight->shadowHigh->textureID());
					}
				}

				glUniform1i(gm.framebufferProgram->getUniform("u_lightType"), tempLight->type_+1); // si es 0, es que no hay luz.

				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
		}

		// ------ SSAO PASS ------
		if (visualMode == 0 && ssaoActive || visualMode == 4) {
			if (visualMode == 0) {
				glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_SRC_COLOR);
				glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);		
			}else {
				glDisable(GL_BLEND);
			}

			gm.framebufferSSAOProgram->use();

			for (int i = 0; i < textureCount(); i++) {
				glUniform1i(glGetUniformLocation(gm.framebufferSSAOProgram->getID(), texturesUniformName_.at(i)), i);
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, textureToRender_.at(i)->getID());
			}

			glUniform1i(glGetUniformLocation(gm.framebufferSSAOProgram->getID(), "ssaoNoise"), 5);
			glActiveTexture(GL_TEXTURE0 + 5);
			glBindTexture(GL_TEXTURE_2D, noiseTexture);

			glUniform3fv(glGetUniformLocation(gm.framebufferSSAOProgram->getID(), "samples"), 64, &ssaoKernel.front().x);

			glUniformMatrix4fv(gm.framebufferSSAOProgram->getUniform("projMatrix"), 1, GL_FALSE, &camComp.projection[0][0]);
			glUniformMatrix4fv(gm.framebufferSSAOProgram->getUniform("viewMatrix"), 1, GL_FALSE, &camComp.view[0][0]);

			glDrawArrays(GL_TRIANGLES, 0, 6);

			GLenum error = glGetError();
			if (error != GL_NO_ERROR) {
				printf("Render FrameBuffer SSAO PASS-> OpenGL Error: %d\n", error);
			}
		}
	}

	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("End Render FrameBuffer-> OpenGL Error: %d\n", error);
	}

	//glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, internalID);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer

	glBlitFramebuffer(0, 0, last_viewport[2], last_viewport[3], 0, 0, last_viewport[2], last_viewport[3], GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint ST::RenderTarget::getID(){
	return internalID;
}

GLuint ST::RenderTarget::textureID(int index){
	if (index < 0 || index > textureCount()) { index = 0; }
	return textureToRender_.at(index)->getID();
}

void ST::RenderTarget::start() {
	glBindFramebuffer(GL_FRAMEBUFFER, internalID);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glGetIntegerv(GL_VIEWPORT, last_viewport);

	glViewport(0, 0, width_, height_);
}

void ST::RenderTarget::end(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Reset viewport
	glViewport(last_viewport[0], last_viewport[1], last_viewport[2], last_viewport[3]);
}

ST::RenderTarget::~RenderTarget(){
	glDeleteFramebuffers(1, &internalID);
}

ST::RenderTarget::RenderTarget(const RenderTarget& o){
	height_ = o.height_;
	width_ = o.width_;
	//renderType_ = o.renderType_;
	visualMode = o.visualMode;

	last_viewport[0] = o.last_viewport[0];
	last_viewport[1] = o.last_viewport[1];
	last_viewport[2] = o.last_viewport[2];
	last_viewport[3] = o.last_viewport[3];

	textureToRender_ = o.textureToRender_;

	internalID = o.internalID;
}
