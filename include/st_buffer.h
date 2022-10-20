#ifndef _SPACE_TURTLE_BUFFER_H_
#define _SPACE_TURTLE_BUFFER_H_ 1

#include <glad.h>

namespace ST {

	class Buffer{
	public:

		Buffer();
		
		enum Target {
			E_TARGET_VERTEX,
			E_TARGET_ELEMENTS
		};

		void init(unsigned int size);
		void bind(const Target t) const;
		unsigned int size() const;
		void uploadData(const void* data, unsigned int size, unsigned int offset = 0);

		GLuint getID();

		~Buffer();
	private:
		GLuint internalID;
		unsigned int sizeData;

		Buffer(const Buffer& o);
	};
}

#endif