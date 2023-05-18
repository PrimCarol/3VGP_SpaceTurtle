#ifndef _SPACE_TURTLE_SYSTEM_ASSETS_H_
#define _SPACE_TURTLE_SYSTEM_ASSETS_H_ 1

#include <unordered_map>
#include <string>
#include <memory>

#include <st_texture.h>

namespace ST {

	class Mesh;

	class SytemAssets {
	public:
		SytemAssets();
		
		// ------ Textures ------
		void saveTexture(std::string path, bool fliped = false,
			ST::Texture::TextType t = ST::Texture::TextType::T_2D);
		void saveTextureCubeMap(std::string name, std::vector<std::string> paths);

		ST::Texture* getTexture(std::string name);

		// ------ Mesh ------
		void saveMesh(std::string path);
		ST::Mesh* getMesh(std::string name);

		~SytemAssets();
	private:

		std::unordered_map<std::string, std::shared_ptr<ST::Texture>> textures;
		std::unordered_map<std::string, std::shared_ptr<ST::Mesh>> meshes;

		SytemAssets(const SytemAssets& o);
	};
}

#endif