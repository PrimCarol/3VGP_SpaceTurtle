#ifndef _SPACE_TURTLE_AUDIO_H_
#define _SPACE_TURTLE_AUDIO_H_ 1

#include <st_texture.h>
#include <vector>
#include <memory>


namespace ST {

	class Program;

	class RenderTarget {
	public:

		enum RenderType {
			RT_Color,
			RT_Depth,
			RT_Stencil
		};

		RenderTarget();
		
		void addTexture(int w, int h,
			ST::Texture::Format f = ST::Texture::Format::F_RGBA,
			ST::Texture::DataType dt = ST::Texture::DT_U_BYTE,
			ST::Texture::TextType t = ST::Texture::TextType::T_2D);
		int textureCount();

		/*void setUp(int w, int h,
			ST::Texture::Format f = ST::Texture::Format::F_RGBA,
			ST::Texture::DataType dt = ST::Texture::DT_U_BYTE,
			ST::Texture::TextType t = ST::Texture::TextType::T_2D);
			*/

		void nextVisualMode();

		void createQuadToRender();
		void renderOnScreen(ST::Program& Shader);

		GLuint getID();
		GLuint textureID(int index);

		//RenderType renderType_;

		void start();
		void end();

		RenderTarget(const RenderTarget& o);
		~RenderTarget();
	private:
		int width_;
		int height_;

		int visualMode;

		GLint last_viewport[4];

		std::vector<std::shared_ptr<ST::Texture>> textureToRender_;
		std::vector<unsigned int> texturesTypeRender_;

		GLuint internalID;
		unsigned int rbo;

		GLuint quadID;
	};
}

#endif