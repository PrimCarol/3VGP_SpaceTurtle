#include "st_texture.h"
#include <assert.h>

ST::Texture::Texture(){
	glGenTextures(1, &internalID);
    //createChecker(256,256);
}

bool ST::Texture::loadSource(const char* shaderText){
	// ????????????????
	return false;
}

void ST::Texture::createChecker(const unsigned int w, const unsigned int h){
    unsigned int* argb = new unsigned int[w * h];
    int x, y;
    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            argb[x + y * w] = (x ^ y); // | (x << 16) | 0xff000000;
        }
    }
    width_ = w;
    height_ = h;
    //texChecker = argb;

    //set_data(F_RGBA, (const void*)texChecker);
    set_data(F_RGBA, (const void*)argb);
}


void ST::Texture::set_data(const Format f, const void* data, unsigned int mipmap_LOD) {
    GLenum data_type;

    glBindTexture(GL_TEXTURE_2D, internalID);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterToGl(min_filter()));
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterToGl(mag_filter()));
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapToGl(wrap_s()));
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapToGl(wrap_t()));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


    glTexImage2D(GL_TEXTURE_2D, mipmap_LOD, GL_RGBA, width(), height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);

    assert(glGetError() == GL_NO_ERROR);
}

const GLuint ST::Texture::getID(){
	return internalID;
}

const ST::Texture::TextType ST::Texture::getType(){
    return type_;
}

const unsigned int ST::Texture::width(){
    return width_;
}

const unsigned int ST::Texture::height(){
    return height_;
}

ST::Texture::~Texture(){

}
