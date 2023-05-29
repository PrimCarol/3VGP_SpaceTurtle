#ifndef _SPACE_TURTLE_LIGHT_H_
#define _SPACE_TURTLE_LIGHT_H_ 1

#include <vec3.hpp>
#include <vec2.hpp>
#include <mat4x4.hpp>

#include <st_shadowmapping.h>

namespace ST {

	/**
	* @brief Light Type
	*/
	enum LightType{
		Directional,
		Point,
		Spot,
	};

	class LightComponent {
	public:
		/**
		* @brief Constructor
		*/
		LightComponent();

		/**
		* @brief Set Color Light
		*/
		void set_Color(const glm::vec3 c);
		/**
		* @brief Set Color Light
		*/
		void set_Color(const float r, const float g, const float b);

		LightType type_;

		// Directional - Spot
		glm::vec3 position_;
		glm::vec3 direction_;

		// ---- Light Intensity ----
		float linear_;
		float quadratic_;

		// ---- Light Colors ----
		glm::vec3 ambient_;
		glm::vec3 diffuse_;
		glm::vec3 specular_;

		// ---- Spotlight ----
		float cutOff_;
		float outerCutOff_;

		// ---- Shadows -----
		float shadowHighRadius_;
		std::shared_ptr<ST::ShadowMapping> shadowHigh;
		glm::mat4 matrixlighShadowHigh_;

		float shadowMediumRadius_;
		std::shared_ptr<ST::ShadowMapping> shadowMedium;
		glm::mat4 matrixlighShadowMedium_;

		float shadowLowRadius_;
		std::shared_ptr<ST::ShadowMapping> shadowLow;
		glm::mat4 matrixlighShadowLow_;

		bool haveShadow_;
		void activeShadows();

		glm::vec3 color_;

		~LightComponent();
	private:
	};
}

#endif