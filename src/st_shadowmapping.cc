#include "st_shadowmapping.h"

ST::ShadowMapping::ShadowMapping(){
	glGenFramebuffers(1, &internalID);
	glGetIntegerv(GL_VIEWPORT, last_viewport);

	width_ = 0;
	height_ = 0;

	destroy = true;
}

void ST::ShadowMapping::setUp(int w, int h, ST::Texture::TextType textureType){
	width_ = w;
	height_ = h;

	glBindFramebuffer(GL_FRAMEBUFFER, internalID);

	shadowMap = std::make_shared<ST::Texture>();
	shadowMap->init(width_, height_, textureType, ST::Texture::DT_FLOAT, ST::Texture::F_DEPTH, ST::Texture::F_DEPTH);
	shadowMap->set_wrap_s(ST::Texture::W_CLAMP_TO_BORDER);
	shadowMap->set_wrap_t(ST::Texture::W_CLAMP_TO_BORDER);
	shadowMap->bind();

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowMap->getID(), 0);
	shadowMap->set_data(0);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

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
	
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("ShadowMapping Start 1-> OpenGL Error: %d\n", error);
	}

	glClear(GL_DEPTH_BUFFER_BIT);

	error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("ShadowMapping Start 2-> OpenGL Error: %d\n", error);
	}

	glGetIntegerv(GL_VIEWPORT, last_viewport);

	error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("ShadowMapping Start 3-> OpenGL Error: %d\n", error);
	}

	glViewport(0, 0, width_, height_);

	error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("ShadowMapping Start 4-> OpenGL Error: %d\n", error);
	}
}

void ST::ShadowMapping::end(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Reset viewport
	glViewport(last_viewport[0], last_viewport[1], last_viewport[2], last_viewport[3]);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("ShadowMapping End -> OpenGL Error: %d\n", error);
	}
}

ST::ShadowMapping::~ShadowMapping(){
	//glDeleteRenderbuffers(1, &rbo);
	if (destroy) {
		//glDeleteFramebuffers(1, &internalID);
	}
}

ST::ShadowMapping::ShadowMapping(const ShadowMapping& o){
	height_ = o.height_;
	width_ = o.width_;

	shadowMap = o.shadowMap;

	last_viewport[0] = o.last_viewport[0];
	last_viewport[1] = o.last_viewport[1];
	last_viewport[2] = o.last_viewport[2];
	last_viewport[3] = o.last_viewport[3];

	internalID = o.internalID;
}

//ST::ShadowMapping::ShadowMapping(ShadowMapping&& o) noexcept {
//	internalID = o.internalID;
//
//	height_ = o.height_;
//	width_ = o.width_;
//
//	shadowMap = o.shadowMap;
//
//	//last_viewport[0] = o.last_viewport[0];
//	//last_viewport[1] = o.last_viewport[1];
//	//last_viewport[2] = o.last_viewport[2];
//	//last_viewport[3] = o.last_viewport[3];
//
//	o.destroy = false;
//}
//
//ST::ShadowMapping& ST::ShadowMapping::operator=(ShadowMapping&& o) noexcept{
//	internalID = o.internalID;
//
//	height_ = o.height_;
//	width_ = o.width_;
//
//	shadowMap = o.shadowMap;
//
//	//last_viewport[0] = o.last_viewport[0];
//	//last_viewport[1] = o.last_viewport[1];
//	//last_viewport[2] = o.last_viewport[2];
//	//last_viewport[3] = o.last_viewport[3];
//
//	o.destroy = false;
//	return *this;
//}
