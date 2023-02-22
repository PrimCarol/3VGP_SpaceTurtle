#ifndef _SPACE_TURTLE_TEXTURE_H_
#define _SPACE_TURTLE_TEXTURE_H_ 1

#include <glad.h>

namespace ST {

	class Texture{
	public:

        enum TextType{
            T_Invalid,
            T_1D,
            T_2D,
            T_3D,
            T_CUBEMAP
        };

        enum Format {
            F_None,
            F_R,
            F_RG,
            F_RGB,
            F_BGR,
            F_BGRA,
            F_RGBA,
            F_DEPTH,
            F_DEPTH32
        };

        enum Filter {
            //valid for minification & magnification
            F_NEAREST,
            F_LINEAR,

            F_NEAREST_MIPMAP_NEAREST,
            F_LINEAR_MIPMAP_NEAREST,
            F_NEAREST_MIPMAP_LINEAR,
            F_LINEAR_MIPMAP_LINEAR
        };

        enum Wrap {
            W_REPEAT,
            W_MIRRORED_REPEAT,
            W_CLAMP_TO_EDGE
        };

		Texture();
		
		bool loadSource(const char* shaderText, TextType t = TextType::T_2D, int mipmaps = 0);
		
        void set_min_filter(Filter f) { min_filter_ = f; }
        void set_mag_filter(Filter f) { mag_filter_ = f; }
        void set_wrap_s(Wrap c) { wrap_s_ = c; }
        void set_wrap_t(Wrap c) { wrap_t_ = c; }
        void set_wrap_r(Wrap c) { wrap_r_ = c; }

        void setRows(int num);
        void setCols(int num);

        const GLuint getID() const;

        const TextType getType() const;
        const int width() const;
        const int height() const;

        const int getRows() const;
        const int getCols() const;

        bool generateMipmap;
        bool forceNoMipmap;

		~Texture();
	private:
        void set_data(const Format f, const void* data, unsigned int mipmap_LOD = 0);
		GLuint internalID;

        Wrap wrap_s_;
        Wrap wrap_t_;
        Wrap wrap_r_;

        Filter min_filter_;
        Filter mag_filter_;

        TextType type_;
        int width_;
        int height_;
        int depth_;

        int rows;
        int cols;

		Texture(const Texture& o);
	};
}

#endif