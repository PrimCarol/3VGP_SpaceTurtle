#include "st_rendertarget.h"
#include <stdio.h>

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
	renderType_ = RT_Color;
	width_ = 0;
	height_ = 0;
}

void ST::RenderTarget::setUp(int w, int h, ST::Texture::Format f, ST::Texture::DataType dt, ST::Texture::TextType t){
	width_ = w;
	height_ = h;
	glBindFramebuffer(GL_FRAMEBUFFER, internalID);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("RenderTarget 01 -> OpenGL Error: %d\n", error);
	}

	textureToRender_.init(width_, height_, t, dt, f);
	textureToRender_.bind();

	if (f == ST::Texture::F_DEPTH) {
		renderType_ = RT_Depth;
	}

	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textureToRender_.getDataTypeGL(), textureToRender_.getID(), 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, RenderTypeToGL(renderType_), textureToRender_.getTypeGL(), textureToRender_.getID(), 0);
	textureToRender_.set_data(0);

	error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("RenderTarget 02 -> OpenGL Error: %d\n", error);
	}

	if (renderType_ == RT_Depth) {
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}else {
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width_, height_);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	}
	
	error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("RenderTarget 03 -> OpenGL Error: %d\n", error);
	}

	textureToRender_.unbind();
	//glDrawBuffer(GL_NONE);
	//glReadBuffer(GL_NONE);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint ST::RenderTarget::getID(){
	return internalID;
}

GLuint ST::RenderTarget::textureID(){
	return textureToRender_.getID();
}

void ST::RenderTarget::start() {
	//glViewport(0, 0, width_, height_);
	glBindFramebuffer(GL_FRAMEBUFFER, internalID);
	if (renderType_ == RT_Depth) {
		glClear(GL_DEPTH_BUFFER_BIT);
	}else {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	//glActiveTexture(GL_TEXTURE0);
	
	//glBindTexture(GL_TEXTURE_2D, woodTexture);
	//renderScene(simpleDepthShader);
	
	//Renderizamos la Escena
}

void ST::RenderTarget::end(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Vigilar si hay problemas con esto, se comenta
	// porque ya se hace solo en la camara.
	
	// Reset viewport
	//glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

ST::RenderTarget::~RenderTarget(){
	glDeleteRenderbuffers(1, &rbo);
	glDeleteFramebuffers(1, &internalID);
}

ST::RenderTarget::RenderTarget(const RenderTarget& o){

}
