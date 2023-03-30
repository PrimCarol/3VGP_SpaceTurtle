#ifndef _SPACE_TURTLE_LIGHT_H_
#define _SPACE_TURTLE_LIGHT_H_ 1

#include <vec3.hpp>

namespace ST {

	enum LightType{
		Directional,
		Point,
		Spot,
	};

	class LightComponent {
	public:
		LightComponent();

		void set_Color(const glm::vec3 c);
		void set_Color(const float r, const float g, const float b);

		LightType type_;

		// ---- Light Intensity ----
		float constant_;
		float linear_;
		float quadratic_;

		// ---- Light Colors ----
		glm::vec3 ambient_;
		glm::vec3 diffuse_;
		glm::vec3 specular_;

		// ---- Spotlight ----
		float cutOff_;
		float outerCutOff_;

		glm::vec3 color_;

		~LightComponent();
	private:
	};
}

#endif