#ifndef _SPACE_TURTLE_SYSTEM_ASSETS_H_
#define _SPACE_TURTLE_SYSTEM_ASSETS_H_ 1

#include <unordered_map>
#include <memory>

#include <st_texture.h>

/**
*@brief Internal Texture type to change
*/
enum class TextureToChange{
	TTC_None,
	TTC_Albedo,
	TTC_Normal,
	TTC_Specular,
	TTC_Roughness,
	TTC_Metallic,
};

namespace ST {

	class GameObj_Manager;
	class Mesh;
	class RenderComponent;
	class Material;

	class SytemAssets {
	public:
		/**
		*@brief Constructor
		*/
		SytemAssets();
		
		// ------ Textures ------
		/**
		* @brief Save texture
		* @param std::string path the path of the file
		* @param bool fliped is want to flip texture
		*/
		void saveTexture(std::string path, bool fliped = false,
			ST::Texture::TextType t = ST::Texture::TextType::T_2D);
		/**
		*@brief Save texture CubeMap
		*/
		void saveTextureCubeMap(std::string name, std::vector<std::string> paths);

		/**
		*@brief Get the texture with the name
		*/
		ST::Texture* getTexture(std::string name);
		/**
		*@brief Get the texture cubeMap with the name
		*/
		ST::Texture* getCubeMap(std::string name);

		// ---- Texture Selector ----
		void openTextureSelector(ST::Material& mat, TextureToChange ttc);
		void closeTextureSelector();
		void popUpTextureSelector();
		
		// ---- CubeMap Selector ----
		void openCubeMapSelector();
		void closeCubeMapSelector();
		void popUpCubeMapSelector(GameObj_Manager& gm);

		// ------ Mesh ------
		/**
		* @brief Save Mesh
		* @param std::string path the path of the file
		*/
		void saveMesh(std::string path);
		/**
		*@brief Get the mesh with the name
		*/
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

		// ---- CubeMap Selector ----
		bool itsCubeMapSelectorOpened;

		// ---- Mesh Selector ----
		bool itsMeshSelectorOpened;
		ST::RenderComponent* renderToChangeMesh;

		// ------ Map data ------
		std::unordered_map<std::string, std::shared_ptr<ST::Texture>> textures;
		std::unordered_map<std::string, std::shared_ptr<ST::Texture>> cubeMaps;
		std::unordered_map<std::string, std::shared_ptr<ST::Mesh>> meshes;

		SytemAssets(const SytemAssets& o);
	};
}

#endif