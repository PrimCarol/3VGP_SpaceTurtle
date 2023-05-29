#include <components/st_light.h>

ST::LightComponent::LightComponent(){
	color_ = glm::vec3(1.0f);
	
	ambient_ = color_;
	diffuse_ = color_;
	specular_ = color_;

	ambient_ = { 1.0f,1.0f,1.0f };
	diffuse_ = { 1.0f,1.0f,1.0f };
	specular_ = { 1.0f,1.0f,1.0f };

	linear_ = 0.1f;
	quadratic_ = 0.5f;

	cutOff_ = 0.9f;
	outerCutOff_ = 0.7f;

	type_ = Point;

	haveShadow_ = false;
}

void ST::LightComponent::set_Color(const glm::vec3 c){
	color_ = c;
	ambient_ = color_;
	diffuse_ = color_;
	specular_ = color_;
}

void ST::LightComponent::set_Color(const float r, const float g, const float b){
	color_.r = r; color_.g = g; color_.b = b;
	ambient_ = color_;
	diffuse_ = color_;
	specular_ = color_;
}

void ST::LightComponent::activeShadows(){
	if (!haveShadow_) {
		haveShadow_ = true;

		shadowHighRadius_ = 50.0f;
		shadowHigh = std::make_shared<ST::ShadowMapping>();
		shadowHigh->setUp(4096, 4096);

		shadowMediumRadius_ = 100.0f;
		shadowMedium = std::make_shared<ST::ShadowMapping>();
		shadowMedium->setUp(1024, 1024);

		shadowLowRadius_ = 200.0f;
		shadowLow = std::make_shared<ST::ShadowMapping>();
		shadowLow->setUp(512, 512);
	}
}

ST::LightComponent::~LightComponent(){

}
