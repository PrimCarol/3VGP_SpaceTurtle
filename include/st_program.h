#ifndef _SPACE_TURTLE_PROGRAM_H_
#define _SPACE_TURTLE_PROGRAM_H_ 1

#include <glad.h>
#include <st_shader.h>

namespace ST {

	class Program{
	public:
		Program();
		
		GLuint getID() const;

		void attach(Shader &s);
		bool link();
		void use() const;

		int getAttrib(const char* location) const;
		GLuint getUniform(const char* location) const;

		~Program();
		Program(const Program& o);
	private:
		GLuint internalID;
	};
}

#endif