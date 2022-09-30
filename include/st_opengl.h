#ifndef _SPACE_TURTLE_OPENGL_H_
#define _SPACE_TURTLE_OPENGL_H_ 1

#include <glad.h>

/*

Cambiar el nombre de este fichero a GPUManager? y que se encargue de menos cosas?

Que haya un tipo de obj que sea OBJ, que tenga Mesh y Material
El mesh tendra con el buffer la info de los puntos
Material tendra el shader y program para luego poder decir OBJ.draw
o Drawn(obj), porque dentro tendra toda la informacion necesaria para pintarlo.

Crear una base padre GameObj o Nodo, parecido a Unity, para que cualquier cosa
sea un obj/nodo y se pueda recorrer todo de mejor manera, podiendo tener
nodos vacios que hagan de modificador de punto central de los objetos dentro.

Si, todo esto parecido al EDK.  �\_(-_-)_/�

*/

namespace ST {

	class OpenGl{

		enum ShaderType{
			SHADER_VERTEX,
			SHADER_FRAGMENT
		};

	public:	
		static OpenGl& instance() {
			static OpenGl* instance = new OpenGl();
			return *instance;
		}

		GLuint loadShader(const char* path, ShaderType t);
		// Suponiendo que te los pasen bien.
		// Crear una clase shader donde dentro sepa de que tipo de shader es,
		// para las validaciones??
		GLuint loadProgram(GLuint vertex_shader, GLuint fragment_shader);

	private:
		OpenGl();
		~OpenGl();
	
		GLuint basic_program_shader;
		GLuint basic_vertex_shader;
		GLuint basic_fragment_shader;
	};	
}

#endif