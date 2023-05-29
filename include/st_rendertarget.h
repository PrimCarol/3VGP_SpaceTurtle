#ifndef _SPACE_TURTLE_RENDERTARGET_H_
#define _SPACE_TURTLE_RENDERTARGET_H_ 1

#include <st_texture.h>
#include <vector>
#include <vec3.hpp>
#include <memory>


namespace ST {

	class GameObj_Manager;
	class Program;
	struct LightsStruct;

	/**
	* @class RenderTarget
	* @brief A class for handling the rendering target in the Space Turtle project.
	*/
	class RenderTarget {
	public:

		/**
		* @enum RenderType
		* @brief Type of rendering: color, depth, stencil.
		*/
		enum RenderType {
			RT_Color,
			RT_Depth,
			RT_Stencil
		};

		/**
		* @brief Constructor.
		*/
		RenderTarget();
		
		/**
		* @brief Adds texture to the render target.
		* @param int w is the witdh of Texture
		* @param int h is the height of Texture
		* @param ST::Texture::Format f is the channels do you want
		* @param ST::Texture::Format internalf is the internal channels do you want
		* @param ST::Texture::DataType dt the datatype of the Texture
		* @param ST::Texture::TextType t the TextureType of the Texture
		*/
		void addTexture(int w, int h, const char* name,
			ST::Texture::Format f = ST::Texture::Format::F_RGBA,
			ST::Texture::Format internalf = ST::Texture::Format::F_RGBA,
			ST::Texture::DataType dt = ST::Texture::DT_U_BYTE,
			ST::Texture::TextType t = ST::Texture::TextType::T_2D);

		/**
		* @brief Returns the count of textures.
		*/
		int textureCount();

		/**
		* @brief Switches to the next visual mode.
		*/
		void nextVisualMode();
		
		/**
	    * @brief Activates or deactivates SSAO.
	    */
		void activateSSAO(bool a);

		/**
		* @brief Renders on the screen.
		* @parem ST::GameObj_Manager the gameManager
		* @parem ST::Program the shader used.
		*/
		void renderOnScreen(ST::GameObj_Manager& gm,
							std::vector<ST::LightsStruct>* lights);

		/**
		* @brief Returns the ID of the render target.
		*/
		GLuint getID();
		/**
		* @brief Returns the ID of a texture at a specified index.
		* @param index of the texture
		*/
		GLuint textureID(int index);

		/**
		* @brief Starts rendering.
		*/
		void start();
		/**
		* @brief Ends rendering.
		*/
		void end();

		/**
		* @brief Copy constructor.
		*/
		RenderTarget(const RenderTarget& o);
		/**
		* @brief Destructor.
		*/
		~RenderTarget();
	private:
		void createQuadToRender();

		int width_;
		int height_;

		int visualMode;
		bool ssaoActive;

		GLint last_viewport[4];

		std::vector<std::shared_ptr<ST::Texture>> textureToRender_;
		std::vector<unsigned int> texturesTypeRender_;
		std::vector<const char*> texturesUniformName_;

		GLuint internalID;

		// SSAO
		std::vector<glm::vec3> ssaoKernel;
		unsigned int noiseTexture;

		GLuint quadID;
	};
}

#endif