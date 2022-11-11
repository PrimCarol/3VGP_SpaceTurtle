#include "st_material.h"

#include <st_utilities.h>
#include <st_shader.h>
#include <st_program.h>

ST::Material::Material(){


	//settings_ = new Settings();
	//settings_ = NULL;
	color = { 1.0f,0.8f,0.9f };
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

const glm::vec3 ST::Material::getColor() {
	return color;
}

const ST::Program* ST::Material::getProgram(){
	return program;
}

void ST::Material::setProgram(ST::Program* p){
	if (p) {
		program = p;
	}
}

ST::Material::Material(const Material& o){
	//settings_ = o.settings_;
	program = o.program;
}

ST::Material::~Material(){
	
}


// --------------------------- Settings ---------------------------
/*ST::Material::Settings::Settings() {
	color = { 1.0f,0.0f,1.0f };
}

void ST::Material::Settings::setColor(glm::vec3 rgb){
	color = rgb;
}

const glm::vec3 ST::Material::Settings::getColor(){
	return color;
}

ST::Material::Settings::~Settings(){ }
*/