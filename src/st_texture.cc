#include "st_texture.h"
#include <assert.h>

ST::Texture::Texture(){
	glGenTextures(1, &internalID);
}

bool ST::Texture::loadSource(const char* shaderText){
	// ????????????????
	return false;
}

GLuint ST::Texture::getID(){
	return internalID;
}
