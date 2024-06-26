#ifndef _SPACE_TURTLE_SHADOWMAPPING_H_
#define _SPACE_TURTLE_SHADOWMAPPING_H_ 1

#include <st_texture.h>
#include <vector>
#include <memory>

namespace ST {

	class GameObj_Manager;
	class Program;

	class ShadowMapping {
	public:

		ShadowMapping();
		
		void setUp(int w, int h, ST::Texture::TextType textureType = ST::Texture::TextType::T_2D);

		GLuint getID();
		GLuint textureID();

		void start();
		void end();

		ShadowMapping(const ShadowMapping& o);
		//ShadowMapping& operator=(const ShadowMapping& o) = delete;

		//ShadowMapping(ShadowMapping&& o) noexcept;
		//ShadowMapping& operator=(ShadowMapping&& o) noexcept;

		~ShadowMapping();
	private:
		int width_;
		int height_;

		GLuint internalID;
		std::shared_ptr<ST::Texture> shadowMap;

		GLint last_viewport[4];
		//unsigned int rbo;

		bool destroy;
	};
}

#endif