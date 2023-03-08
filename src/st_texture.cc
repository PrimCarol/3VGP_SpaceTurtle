#include "st_texture.h"
#include <assert.h>

#include "stb_image.h"
#include <memory>


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

GLenum dataTypeToGl(const ST::Texture::DataType dt) {
    GLenum aux = GL_NONE;
    switch (dt) {
    case ST::Texture::DT_U_BYTE:
        aux = GL_UNSIGNED_BYTE;
        break;
    case ST::Texture::DT_BYTE:
        aux = GL_BYTE;
        break;
    case ST::Texture::DT_U_SHORT:
        aux = GL_UNSIGNED_SHORT;
        break;
    case ST::Texture::DT_SHORT:
        aux = GL_SHORT;
        break;
    case ST::Texture::DT_U_INT:
        aux = GL_UNSIGNED_INT;
        break;
    case ST::Texture::DT_FLOAT:
        aux = GL_FLOAT;
        break;
    default:
        printf("Data Type >> Invalid Format");
        break;
    }

    return aux;
}

GLenum textureTypeToGl(const ST::Texture::TextType f) {
    GLenum aux = GL_NONE;
    switch (f) {
    /*case ST::Texture::T_Invalid:
        aux = GL_NONE;
        break;*/
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


ST::Texture::Texture(){
    //gladLoadGL();
    glGenTextures(1, &internalID);
    
    rows = 1;
    cols = 1;
    width_ = 0;
    height_ = 0;
    depth_ = 1; // <---- ???
    type_ = T_2D;
    dataType_ = DT_U_BYTE;
    format_ = F_RGBA;

    generateMipmap = false;
    forceNoMipmap = false;

    set_min_filter(Filter::F_NEAREST);
    set_mag_filter(Filter::F_NEAREST);
    set_wrap_s(Wrap::W_CLAMP_TO_EDGE);
    set_wrap_t(Wrap::W_CLAMP_TO_EDGE);
    set_wrap_r(Wrap::W_CLAMP_TO_EDGE);
}

bool ST::Texture::loadSource(const char* filePath, TextType t, Format f/*, int mipmaps*/) {
    //glGenTextures(1, &internalID);

    unsigned char* image_data = stbi_load(filePath, &width_, &height_, NULL, 4);
    if (image_data == NULL)
        return false;
    
    format_ = f;
    type_ = t;
    set_data((const void*)image_data);

    stbi_image_free(image_data);

	return true;
}

void ST::Texture::init(int width, int height, TextType t, DataType dt, Format f) {
    //glGenTextures(1, &internalID);

    width_ = width;
    height_ = height;
    type_ = t;
    dataType_ = dt;
    format_ = f;
}

void ST::Texture::bind(){
    glBindTexture(getTypeGL(), internalID);
}

void ST::Texture::unbind(){
    glBindTexture(getTypeGL(), 0);
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



void ST::Texture::set_data(const void* data/*, unsigned int mipmap_LOD*/) {
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

    /*
    
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    
    */

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

        glTexImage1D(GL_TEXTURE_1D, 0, formatToGl(format_), width(), 0, formatToGl(format_), dataTypeToGl(dataType_), data);

        if (generateMipmap) {
            glGenerateMipmap(GL_TEXTURE_1D);
        }

        //glBindTexture(GL_TEXTURE_1D, 0);

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

        glTexImage2D(GL_TEXTURE_2D, 0, formatToGl(format_), width(), height(), 0, formatToGl(format_), dataTypeToGl(dataType_), data);

        if (generateMipmap) {
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        //glBindTexture(GL_TEXTURE_2D, 0);

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

        glTexImage3D(GL_TEXTURE_3D, 0, formatToGl(format_), width(), height(), depth_, 0, formatToGl(format_), dataTypeToGl(dataType_), data);
        
        if (generateMipmap) {
            glGenerateMipmap(GL_TEXTURE_3D);
        }
        
        //glBindTexture(GL_TEXTURE_3D, 0);

        break;
    default:
        printf("Set Data to Texture >> Invalid Type");
        break;
    }

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("OpenGL Error: %d\n", error);
    }

    //assert(glGetError() == GL_NO_ERROR);
}

const GLuint ST::Texture::getID() const{
	return internalID;
}

const ST::Texture::TextType ST::Texture::getType() const{
    return type_;
}

const GLenum ST::Texture::getTypeGL() const{
    return textureTypeToGl(type_);
}

const ST::Texture::Format ST::Texture::getFormat() const{
    return format_;
}

const GLenum ST::Texture::getFormatGL() const{
    return formatToGl(format_);
}

const ST::Texture::DataType ST::Texture::getDataType() const{
    return dataType_;
}

const GLenum ST::Texture::getDataTypeGL() const{
    return dataTypeToGl(dataType_);
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

ST::Texture::Texture(const Texture& o){
    internalID = o.internalID;

    rows = o.rows;
    cols = o.cols;
    width_ = o.width_;
    height_ = o.height_;
    depth_ = o.depth_; // <---- ???
    type_ = o.type_;
    dataType_ = o.dataType_;
    format_ = o.format_;

    generateMipmap = o.generateMipmap;
    forceNoMipmap = o.forceNoMipmap;

    set_min_filter(Filter::F_NEAREST);
    set_mag_filter(Filter::F_NEAREST);
    set_wrap_s(Wrap::W_CLAMP_TO_EDGE);
    set_wrap_t(Wrap::W_CLAMP_TO_EDGE);
    set_wrap_r(Wrap::W_CLAMP_TO_EDGE);
}
