#include "st_texture.h"
#include <assert.h>

#include "stb_image.h"
#include <memory>

ST::Texture::Texture(){
	glGenTextures(1, &internalID);
    rows = 1;
    cols = 1;
    width_ = 0;
    height_ = 0;
    depth_ = 1; // <---- ???
    type_ = T_Invalid;

    generateMipmap = false;
    forceNoMipmap = false;

    set_min_filter(Filter::F_NEAREST);
    set_mag_filter(Filter::F_NEAREST);
    set_wrap_s(Wrap::W_CLAMP_TO_EDGE);
    set_wrap_t(Wrap::W_CLAMP_TO_EDGE);
    set_wrap_r(Wrap::W_CLAMP_TO_EDGE);
}

bool ST::Texture::loadSource(const char* filePath, TextType t, int mipmaps){

    unsigned char* image_data = stbi_load(filePath, &width_, &height_, NULL, 4);
    if (image_data == NULL)
        return false;

    type_ = t;
    set_data(F_RGBA, (const void*)image_data, mipmaps);

    stbi_image_free(image_data);

	return true;
}

void ST::Texture::setRows(int num){
    if (num > 0) {
        rows = num;
    }
}

void ST::Texture::setCols(int num){
    if(num > 0){
        cols = num;
    }
}

GLenum formatToGl(const ST::Texture::Format f) {
    GLenum aux = GL_NONE;
    switch (f) {
    case ST::Texture::F_None:
        aux = GL_NONE;
        break;
    case ST::Texture::F_R:
        aux = GL_R;
        break;
    case ST::Texture::F_RG:
        aux = GL_RG;
        break;
    case ST::Texture::F_RGB:
        aux = GL_RGB;
        break;
    case ST::Texture::F_BGR:
        aux = GL_BGR;
        break;
    case ST::Texture::F_BGRA:
        aux = GL_BGRA;
        break;
    case ST::Texture::F_RGBA:
        aux = GL_RGBA;
        break;
    case ST::Texture::F_DEPTH:
        aux = GL_DEPTH_COMPONENT;
        break;
    case ST::Texture::F_DEPTH32:
        aux = GL_DEPTH_STENCIL;
        break;
    default:
        printf("Texture Data >> Invalid Format");
        break;
    }

    return aux;
}

GLenum textureTypeToGl(const ST::Texture::TextType f) {
    GLenum aux = GL_NONE;
    switch (f) {
    case ST::Texture::T_Invalid:
        aux = GL_NONE;
        break;
    case ST::Texture::T_1D:
        aux = GL_TEXTURE_1D;
        break;
    case ST::Texture::T_2D:
        aux = GL_TEXTURE_2D;
        break;
    case ST::Texture::T_3D:
        aux = GL_TEXTURE_3D;
        break;
    default:
        printf("Texture Type >> Invalid Format");
        break;
    }

    return aux;
}

GLint filterToGl(const ST::Texture::Filter f) {
    GLint aux;
    switch (f) {
    case ST::Texture::Filter::F_LINEAR:
        aux = GL_LINEAR;
        break;
    case ST::Texture::Filter::F_LINEAR_MIPMAP_LINEAR:
        aux = GL_LINEAR_MIPMAP_LINEAR;
        break;
    case ST::Texture::Filter::F_LINEAR_MIPMAP_NEAREST:
        aux = GL_LINEAR_MIPMAP_NEAREST;
        break;
    case ST::Texture::Filter::F_NEAREST:
        aux = GL_NEAREST;
        break;
    case ST::Texture::Filter::F_NEAREST_MIPMAP_LINEAR:
        aux = GL_NEAREST_MIPMAP_LINEAR;
        break;
    case ST::Texture::Filter::F_NEAREST_MIPMAP_NEAREST:
        aux = GL_NEAREST_MIPMAP_NEAREST;
        break;
    default:
        printf("Filter >> Invalid Format");
        break;
    }

    return aux;
}

GLint wrapToGl(const ST::Texture::Wrap w) {
    GLint aux;
    switch (w) {
    case ST::Texture::Wrap::W_CLAMP_TO_EDGE:
        aux = GL_CLAMP_TO_EDGE;
        break;
    case ST::Texture::Wrap::W_MIRRORED_REPEAT:
        aux = GL_MIRRORED_REPEAT;
        break;
    case ST::Texture::Wrap::W_REPEAT:
        aux = GL_REPEAT;
        break;
    default:
        printf("Wrap >> Invalid Format");
        break;
    }

    return aux;
}

void ST::Texture::set_data(const Format f, const void* data, unsigned int mipmap_LOD) {
    //GLenum data_type;

    //glBindTexture(GL_TEXTURE_2D, internalID);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterToGl(min_filter_));
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterToGl(mag_filter_));
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapToGl(wrap_s_));
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapToGl(wrap_t_));
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, wrapToGl(wrap_r_));


    //glTexImage2D(GL_TEXTURE_2D, mipmap_LOD, GL_RGBA, width(), height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    //glBindTexture(GL_TEXTURE_2D, 0); 

    switch (type_) {
    case TextType::T_1D:
        glBindTexture(GL_TEXTURE_1D, internalID);
       
        if (forceNoMipmap) {
            //glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_BASE_LEVEL, 0);
            glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAX_LEVEL, 0);
        }
       
        glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, filterToGl(min_filter_));
        glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, filterToGl(mag_filter_));
        
        glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, wrapToGl(wrap_s_));

        glTexImage1D(GL_TEXTURE_1D, mipmap_LOD, formatToGl(f), width(), 0, formatToGl(f), GL_UNSIGNED_BYTE, data);

        if (generateMipmap) {
            glGenerateMipmap(GL_TEXTURE_1D);
        }

        glBindTexture(GL_TEXTURE_1D, 0);

        break;
    case TextType::T_2D:
        glBindTexture(GL_TEXTURE_2D, internalID);

        
        if (forceNoMipmap) {
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterToGl(min_filter_));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterToGl(mag_filter_));
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapToGl(wrap_s_));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapToGl(wrap_t_));

        glTexImage2D(GL_TEXTURE_2D, mipmap_LOD, formatToGl(f), width(), height(), 0, formatToGl(f), GL_UNSIGNED_BYTE, data);

        if (generateMipmap) {
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        glBindTexture(GL_TEXTURE_2D, 0);

        break;
    case TextType::T_3D:
        glBindTexture(GL_TEXTURE_3D, internalID);

        if (forceNoMipmap) {
            //glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_BASE_LEVEL, 0);
            glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAX_LEVEL, 0);
        }

        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, filterToGl(min_filter_));
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, filterToGl(mag_filter_));
        
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, wrapToGl(wrap_s_));
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, wrapToGl(wrap_t_));
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, wrapToGl(wrap_r_));

        glTexImage3D(GL_TEXTURE_3D, mipmap_LOD, formatToGl(f), width(), height(), depth_, 0, formatToGl(f), GL_UNSIGNED_BYTE, data);
        
        if (generateMipmap) {
            glGenerateMipmap(GL_TEXTURE_3D);
        }
        
        glBindTexture(GL_TEXTURE_3D, 0);

        break;
    default:
        printf("Set Data to Texture >> Invalid Type");
        break;
    }

    assert(glGetError() == GL_NO_ERROR);
}

const GLuint ST::Texture::getID() const{
	return internalID;
}

const ST::Texture::TextType ST::Texture::getType() const{
    return type_;
}

const int ST::Texture::width() const{
    return width_;
}

const int ST::Texture::height() const{
    return height_;
}

const int ST::Texture::getRows() const{
    return rows;
}

const int ST::Texture::getCols() const{
    return cols;
}

ST::Texture::~Texture(){
    glDeleteTextures(1, &internalID);
}
