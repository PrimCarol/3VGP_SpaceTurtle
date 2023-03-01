#include "st_rendertarget.h"

ST::RenderTarget::RenderTarget(int w, int h){
	glGenFramebuffers(1, &internalID);
	width_ = w;
	height_ = h;
	textureToRender_.init(width_, height_, ST::Texture::T_2D, ST::Texture::DT_FLOAT, ST::Texture::F_DEPTH);
	//textureToRender_.set_wrap_s(ST::Texture::W_MIRRORED_REPEAT);
	//textureToRender_.set_wrap_t(ST::Texture::W_MIRRORED_REPEAT);
	textureToRender_.set_data(nullptr);

	glBindFramebuffer(GL_FRAMEBUFFER, internalID);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureToRender_.getID(), 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

ST::RenderTarget::~RenderTarget(){

}

ST::RenderTarget::RenderTarget(const RenderTarget& o){

}
