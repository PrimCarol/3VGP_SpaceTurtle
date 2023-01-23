#include "st_material.h"

#include <st_utilities.h>
#include <st_shader.h>
#include <st_program.h>

ST::Material::Material(){


	//settings_ = new Settings();
	//settings_ = NULL;
	//color = { 1.0f,0.8f,0.9f };
	color = { 1.0f,1.0f,1.0f };
	haveAlbedo = false;
}

/*void ST::Material::setSettings(Settings* s) {
	settings_ = new Settings();
	settings_->setColor(s->getColor());
}

ST::Material::Settings* ST::Material::getSettings() const{
	return settings_;
}*/

void ST::Material::setColor(glm::vec3 rgb) {
	color = rgb;
}

void ST::Material::setColor(float r, float g, float b) {
	color.r = r;
	color.g = g;
	color.b = b;
}

const glm::vec3 ST::Material::getColor() {
	return color;
}

const ST::Program* ST::Material::getProgram(){
	return program.get();
}

void ST::Material::setProgram(std::shared_ptr<ST::Program>& p){
	if (p) {
		program = p;
	}
}

ST::Texture* ST::Material::getAlbedo(){
	return albedo;
}

void ST::Material::setTexture_Albedo(ST::Texture* texAlbedo){
	if (texAlbedo) {
		albedo = texAlbedo;
		haveAlbedo = true;
	}
}

ST::Material::~Material(){
	
}