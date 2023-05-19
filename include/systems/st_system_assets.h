#ifndef _SPACE_TURTLE_SYSTEM_ASSETS_H_
#define _SPACE_TURTLE_SYSTEM_ASSETS_H_ 1

#include <unordered_map>
#include <memory>

#include <st_texture.h>

enum class TextureToChange{
	TTC_None,
	TTC_Albedo,
	TTC_Normal,
	TTC_Specular,
	TTC_Roughness,
	TTC_Metallic,
};

namespace ST {

	class Mesh;
	class RenderComponent;
	class Material;

	class SytemAssets {
	public:
		SytemAssets();
		
		// ------ Textures ------
		void saveTexture(std::string path, bool fliped = false,
			ST::Texture::TextType t = ST::Texture::TextType::T_2D);
		void saveTextureCubeMap(std::string name, std::vector<std::string> paths);

		ST::Texture* getTexture(std::string name);

		// ---- Texture Selector ----
		void openTextureSelector(ST::Material& mat, TextureToChange ttc);
		void closeTextureSelector();
		void popUpTextureSelector();
		

		// ------ Mesh ------
		void saveMesh(std::string path);
		ST::Mesh* getMesh(std::string name);

		// ---- Mesh Selector ----
		void openMeshSelector(ST::RenderComponent& render);
		void closeMeshSelector();
		void popUpMeshSelector();

		~SytemAssets();
	private:

		// ---- Texture Selector ----
		bool itsTextureSelectorOpened;
		ST::Material* materialToChangeTexture;
		TextureToChange ttc_;

		// ---- Mesh Selector ----
		bool itsMeshSelectorOpened;
		ST::RenderComponent* renderToChangeMesh;

		// ------ Map data ------
		std::unordered_map<std::string, std::shared_ptr<ST::Texture>> textures;
		std::unordered_map<std::string, std::shared_ptr<ST::Mesh>> meshes;

		SytemAssets(const SytemAssets& o);
	};
}

#endif