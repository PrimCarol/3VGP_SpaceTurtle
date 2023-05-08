#include "st_shadowmapping.h"

ST::ShadowMapping::ShadowMapping(){
	glGenFramebuffers(1, &internalID);
	//glGenRenderbuffers(1, &rbo);
	glGetIntegerv(GL_VIEWPORT, last_viewport);

	width_ = 0;
	height_ = 0;
}

void ST::ShadowMapping::setUp(int w, int h, ST::Texture::TextType textureType){
	width_ = w;
	height_ = h;

	glBindFramebuffer(GL_FRAMEBUFFER, internalID);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("ShadowMap 01 -> OpenGL Error: %d\n", error);
	}

	shadowMap = std::make_shared<ST::Texture>();
	shadowMap->init(width_, height_, textureType, ST::Texture::DT_FLOAT, ST::Texture::F_DEPTH, ST::Texture::F_DEPTH);
	shadowMap->set_wrap_s(ST::Texture::W_CLAMP_TO_BORDER);
	shadowMap->set_wrap_t(ST::Texture::W_CLAMP_TO_BORDER);
	shadowMap->bind();
	
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowMap->getID(), 0);
	shadowMap->set_data(0);
	
	error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("ShadowMap 02 -> OpenGL Error: %d\n", error);
	}

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	
	error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("ShadowMap 03 -> OpenGL Error: %d\n", error);
	}

	shadowMap->unbind();
	//glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint ST::ShadowMapping::getID(){
	return internalID;
}

GLuint ST::ShadowMapping::textureID(){
	return shadowMap->getID();
}

void ST::ShadowMapping::start() {
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

void ST::ShadowMapping::end(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Reset viewport
	glViewport(last_viewport[0], last_viewport[1], last_viewport[2], last_viewport[3]);
}

ST::ShadowMapping::~ShadowMapping(){
	//glDeleteRenderbuffers(1, &rbo);
	glDeleteFramebuffers(1, &internalID);
}

ST::ShadowMapping::ShadowMapping(const ShadowMapping& o){
	height_ = o.height_;
	width_ = o.width_;
	
	//last_viewport[0] = o.last_viewport[0];
	//last_viewport[1] = o.last_viewport[1];
	//last_viewport[2] = o.last_viewport[2];
	//last_viewport[3] = o.last_viewport[3];

	shadowMap = o.shadowMap;

	internalID = o.internalID;
	//rbo = o.rbo;
}
