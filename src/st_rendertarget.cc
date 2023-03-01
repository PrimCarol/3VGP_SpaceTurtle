#include "st_rendertarget.h"

ST::RenderTarget::RenderTarget(){
	glGenFramebuffers(1, &internalID);
	width_ = 0;
	height_ = 0;
}

void ST::RenderTarget::setUp(int w, int h, ST::Texture::TextType t, ST::Texture::DataType dt, ST::Texture::Format f){
	width_ = w;
	height_ = h;
	glBindFramebuffer(GL_FRAMEBUFFER, internalID);

	textureToRender_.set_dataType(dt);

	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textureToRender_.getDataTypeGL(), textureToRender_.getID(), 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureToRender_.getDataTypeGL(), textureToRender_.getID(), 0);
	
	textureToRender_.init(width_, height_, t, dt, f);
	//textureToRender_.set_wrap_s(ST::Texture::W_MIRRORED_REPEAT);
	//textureToRender_.set_wrap_t(ST::Texture::W_MIRRORED_REPEAT);
	//textureToRender_.set_data(0);

	/*unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width_, height_);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);*/
	

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

void ST::RenderTarget::start(){
	//glViewport(0, 0, width_, height_);
	glBindFramebuffer(GL_FRAMEBUFFER, internalID);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
	glDeleteFramebuffers(1, &internalID);
}

ST::RenderTarget::RenderTarget(const RenderTarget& o){

}
