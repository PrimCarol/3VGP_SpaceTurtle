#include "st_material.h"

#include <st_utilities.h>
#include <st_shader.h>
#include <st_program.h>

ST::Material::Material(){

	color = { 1.0f,1.0f,1.0f,1.0f };

	haveAlbedo = false;
	haveNormal = false;
	haveSpecular = false;

	albedo = nullptr;
	normal = nullptr;
	specular = nullptr;

	translucent = false;
	texIndex_ = { 0,0 };
}

/*void ST::Material::setSettings(Settings* s) {
	settings_ = new Settings();
	settings_->setColor(s->getColor());
}

ST::Material::Settings* ST::Material::getSettings() const{
	return settings_;
}*/

void ST::Material::setColor(glm::vec4 rgb) {
	color = rgb;
}

void ST::Material::setColor(float r, float g, float b, float a) {
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}

const glm::vec4 ST::Material::getColor() const{
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

ST::Texture* ST::Material::getNormal(){
	return normal;
}

void ST::Material::setTexture_Normal(ST::Texture* texNormal){
	if (texNormal) {
		normal = texNormal;
		haveNormal = true;
	}
}

ST::Texture* ST::Material::getSpecular(){
	return specular;
}

void ST::Material::setTexture_Specular(ST::Texture* texSpecular){
	if (texSpecular) {
		specular = texSpecular;
		haveSpecular = true;
	}
}

const glm::ivec2 ST::Material::getTexIndex() const{
	return texIndex_;
}

void ST::Material::setTexIndex(glm::ivec2 texIndex){
	texIndex_.x = texIndex.x > 0 ? texIndex.x : 0;
	texIndex_.y = texIndex.y > 0 ? texIndex.y : 0;
}

ST::Material::~Material(){
	
}