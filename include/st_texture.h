#ifndef _SPACE_TURTLE_TEXTURE_H_
#define _SPACE_TURTLE_TEXTURE_H_ 1

#include <glad.h>

namespace ST {

	class Texture{
	public:

        enum TextType {
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
		
        void setRows(int num);
        void setCols(int num);

        const GLuint getID() const;

        const TextType getType() const;
        const int width() const;
        const int height() const;

        const int getRows() const;
        const int getCols() const;

		~Texture();
	private:
        void set_data(const Format f, /* const Type t,*/ const void* data, unsigned int mipmap_LOD = 0);
		GLuint internalID;

        TextType type_;
        int width_;
        int height_;

        int rows;
        int cols;

        //unsigned int* texChecker;

		Texture(const Texture& o);
	};
}

#endif