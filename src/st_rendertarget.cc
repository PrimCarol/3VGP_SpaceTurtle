#include "st_rendertarget.h"
#include <stdio.h>

#include <st_gameobj_manager.h>
#include <st_transform.h>
#include <st_camera.h>
#include <st_program.h>
#include <st_system_light.h>

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

ST::RenderTarget::RenderTarget(){
	glGenFramebuffers(1, &internalID);
	glGenRenderbuffers(1, &rbo);
	glGetIntegerv(GL_VIEWPORT, last_viewport);
	//renderType_ = RT_Color;
	width_ = 0;
	height_ = 0;

	quadID = 0;

	visualMode = 0;
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

	/*glBindFramebuffer(GL_FRAMEBUFFER, internalID);
	unsigned int rboDepth;
	glGenRenderbuffers(1, &rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width_, height_);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);*/
}

void ST::RenderTarget::renderOnScreen(ST::GameObj_Manager& gm, ST::Program& Shader, std::vector<ST::LightsStruct>* lights){

	auto camVector = gm.getComponentVector<ST::CameraComponent>();
	if (gm.mainCameraID() == -1) {
		for (int i = 0; i < camVector->size(); i++) {
			if (camVector->at(i).has_value()) {
				ST::GameObj tempObj(i, gm);
				gm.setMainCamera(tempObj);
			}
		}
	}
	
	if (quadID != 0) {

		//glUseProgram(Shader.getID());
		Shader.use();

		for (int i = 0; i < texturesUniformName_.size(); i++){
			glUniform1i(glGetUniformLocation(Shader.getID(), texturesUniformName_.at(i)), i);
		}

		// Temporal <--------------------------------
		glm::vec3 viewPos = gm.getComponentVector<ST::TransformComponent>()->at(gm.mainCameraID())->getPosition();
		glUniform1i(glGetUniformLocation(Shader.getID(), "visualMode"), visualMode);
		glUniform3fv(glGetUniformLocation(Shader.getID(), "viewPos"), 1, &viewPos.x);

		glBindVertexArray(quadID);

		//glBindFramebuffer(GL_READ_FRAMEBUFFER, internalID);
		for (int i = 0; i < textureCount(); i++){
			glActiveTexture(GL_TEXTURE0+i);
			glBindTexture(GL_TEXTURE_2D, textureToRender_.at(i)->getID());
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		
		glDrawArrays(GL_TRIANGLES, 0, 6);

		if (lights) {
			for (int i = 0; i < lights->size(); i++){
				//Uniforms
				ST::LightComponent* tempLight = lights->at(i).light_;

				// Directional
				if (tempLight->type_ == ST::Directional) {
					glUniform3f(Shader.getUniform("u_DirectLight.direction"), tempLight->direction_.x, tempLight->direction_.y, tempLight->direction_.z);
					glUniform3f(Shader.getUniform("u_DirectLight.ambient"), tempLight->ambient_.x, tempLight->ambient_.y, tempLight->ambient_.z);
					glUniform3f(Shader.getUniform("u_DirectLight.diffuse"), tempLight->diffuse_.x, tempLight->diffuse_.y, tempLight->diffuse_.z);
					glUniform3f(Shader.getUniform("u_DirectLight.specular"), tempLight->specular_.x, tempLight->specular_.y, tempLight->specular_.z);
				}
				// Point
				if (tempLight->type_ == ST::Point) {
					glUniform3f(Shader.getUniform("u_PointLight.position"), tempLight->position_.x, tempLight->position_.y, tempLight->position_.z);
					glUniform3f(Shader.getUniform("u_PointLight.ambient"), tempLight->color_.x, tempLight->color_.y, tempLight->color_.z);
					glUniform3f(Shader.getUniform("u_PointLight.diffuse"), tempLight->color_.x, tempLight->color_.y, tempLight->color_.z);
					glUniform3f(Shader.getUniform("u_PointLight.specular"), tempLight->color_.x, tempLight->color_.y, tempLight->color_.z);
					glUniform1f(Shader.getUniform("u_PointLight.constant"), tempLight->constant_);
					glUniform1f(Shader.getUniform("u_PointLight.linear"), tempLight->linear_);
					glUniform1f(Shader.getUniform("u_PointLight.quadratic"), tempLight->quadratic_);
				}
				// Spot
				if (tempLight->type_ == ST::Spot) {
					glUniform3f(Shader.getUniform("u_SpotLight.position"), tempLight->position_.x, tempLight->position_.y, tempLight->position_.z);
					glUniform3f(Shader.getUniform("u_SpotLight.ambient"), tempLight->color_.x, tempLight->color_.y, tempLight->color_.z);
					glUniform3f(Shader.getUniform("u_SpotLight.diffuse"), tempLight->color_.x, tempLight->color_.y, tempLight->color_.z);
					glUniform3f(Shader.getUniform("u_SpotLight.specular"), tempLight->color_.x, tempLight->color_.y, tempLight->color_.z);
					glUniform1f(Shader.getUniform("u_SpotLight.constant"), tempLight->constant_);
					glUniform1f(Shader.getUniform("u_SpotLight.linear"), tempLight->linear_);
					glUniform1f(Shader.getUniform("u_SpotLight.quadratic"), tempLight->quadratic_);
					glUniform3f(Shader.getUniform("u_SpotLight.direction"), tempLight->direction_.x, tempLight->direction_.y, tempLight->direction_.z);
					glUniform1f(Shader.getUniform("u_SpotLight.cutOff"), tempLight->cutOff_);
					glUniform1f(Shader.getUniform("u_SpotLight.outerCutOff"), tempLight->outerCutOff_);
				}

				glUniform1i(Shader.getUniform("u_lightType"), tempLight->type_);

				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
		}

		glDisable(GL_BLEND);
	}

	glBindFramebuffer(GL_READ_FRAMEBUFFER, internalID);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer
	// blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
	// the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the 		
	// depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
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
	//glViewport(0, 0, width_, height_);
	glBindFramebuffer(GL_FRAMEBUFFER, internalID);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glGetIntegerv(GL_VIEWPORT, last_viewport);

	/*if (renderType_ == RT_Depth) {
		glViewport(0, 0, width_, height_);
		glClear(GL_DEPTH_BUFFER_BIT);
	}else {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}*/
	glViewport(0, 0, width_, height_);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ST::RenderTarget::end(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Reset viewport
	glViewport(last_viewport[0], last_viewport[1], last_viewport[2], last_viewport[3]);
}

ST::RenderTarget::~RenderTarget(){
	glDeleteRenderbuffers(1, &rbo);
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
	rbo = o.rbo;
}
