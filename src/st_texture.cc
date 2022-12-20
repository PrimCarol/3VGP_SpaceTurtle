#include "st_texture.h"
#include <assert.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <memory>

ST::Texture::Texture(){
	glGenTextures(1, &internalID);
}

bool ST::Texture::loadSource(const char* filePath){

    unsigned char* image_data = stbi_load(filePath, &width_, &height_, NULL, 4);
    if (image_data == NULL)
        return false;

    set_data(F_RGBA, (const void*)image_data);

    stbi_image_free(image_data);

	return true;
}

void ST::Texture::createChecker(const unsigned int w, const unsigned int h){
    auto argb = std::make_unique<unsigned int[]>(w * h);
    int x, y;
    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            argb[x + y * w] = (x ^ y);
        }
    }
    width_ = w;
    height_ = h;

    set_data(F_RGBA, (const void*)argb.get());
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

const int ST::Texture::width(){
    return width_;
}

const int ST::Texture::height(){
    return height_;
}

ST::Texture::~Texture(){
    glDeleteTextures(1, &internalID);
}
