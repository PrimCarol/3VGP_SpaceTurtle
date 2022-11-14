#ifndef _SPACE_TURTLE_TEXTURE_H_
#define _SPACE_TURTLE_TEXTURE_H_ 1

#include <glad.h>

namespace ST {

	class Texture{
	public:

        enum Type {
            T_Invalid,
            //T_1D,
            T_2D,
            //T_3D,
            //T_CUBEMAP
        };

        enum Format {
            F_None,
            //F_R,
            //F_RG,
            F_RGB,
            //F_BGR,
            //F_BGRA,
            F_RGBA,
            F_DEPTH,
            //F_DEPTH32,
        };

        /*enum Filter {
            //valid for minification & magnification
            F_NEAREST,
            F_LINEAR,

            //F_NEAREST_MIPMAP_NEAREST,
            //F_LINEAR_MIPMAP_NEAREST,
            //F_NEAREST_MIPMAP_LINEAR,
            //F_LINEAR_MIPMAP_LINEAR,
        };

        enum Wrap {
            W_REPEAT,
            W_MIRRORED_REPEAT,
            W_CLAMP_TO_EDGE,
        };*/

		Texture();
		
		bool loadSource(const char* shaderText);
		GLuint getID();

		~Texture();
	private:
		GLuint internalID;

		Texture(const Texture& o);
	};
}

#endif