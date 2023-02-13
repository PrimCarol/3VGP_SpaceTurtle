#include <components/st_light.h>

ST::LightComponent::LightComponent(){
	color_ = glm::vec3(1.0f);
	
	ambient_ = color_;
	diffuse_ = color_;
	specular_ = color_;

	// -----> Temporal <----
	dirLight_ = { 0.0f,0.0f,0.0f };
	ambient_ = { 0.1f,0.1f,0.1f };
	diffuse_ = { 1.0f,1.0f,1.0f };
	specular_ = { 1.0f,1.0f,1.0f };

	constant_ = 1.0f;
	linear_ = 0.005f;
	quadratic_ = 0.002f;

	cutOff_ = 0.9f;
	outerCutOff_ = 0.7f;

	type_ = Point;
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

ST::LightComponent::~LightComponent(){

}
