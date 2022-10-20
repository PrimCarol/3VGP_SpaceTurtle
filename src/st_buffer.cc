#include "st_buffer.h"

ST::Buffer::Buffer(){
	gladLoadGL();
	sizeData = 0;
	glGenBuffers(1, &internalID);
}

void ST::Buffer::init(unsigned int size) {
	sizeData = size;
	glBindBuffer(GL_ARRAY_BUFFER, internalID);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ST::Buffer::bind(const Target t) const {
	switch (t) {
	case E_TARGET_VERTEX:
		glBindBuffer(GL_ARRAY_BUFFER, internalID);
		break;
	case E_TARGET_ELEMENTS:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, internalID);
		break;
	}
}

unsigned int ST::Buffer::size() const {
	return sizeData;
}

void ST::Buffer::uploadData(const void* data, unsigned int size, unsigned int offset) {
	if (data != nullptr) {
		glBindBuffer(GL_ARRAY_BUFFER, internalID);
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint ST::Buffer::getID(){
	return internalID;
}

ST::Buffer::~Buffer(){
	glDeleteBuffers(1, &internalID);
}
