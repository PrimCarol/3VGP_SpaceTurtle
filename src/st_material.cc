#include "st_material.h"

#include <st_utilities.h>
#include <st_shader.h>
#include <st_program.h>

ST::Material::Material(){
	ST::Shader vertex(E_VERTEX_SHADER);

	GLchar* textVertex = (GLchar*)readFile("../shaders/vertex.vert");
	vertex.loadSource(textVertex);

	ST::Shader fragment(E_FRAGMENT_SHADER);

	GLchar* textFragment = (GLchar*)readFile("../shaders/fragment.frag");
	fragment.loadSource(textFragment);

	program = new ST::Program();
	program->attach(vertex);
	program->attach(fragment);
	program->link();

	color = {1.0f,0.0f,1.0f};
}

void ST::Material::setColor(glm::vec3 rgb){
	color = rgb;
}

const glm::vec3 ST::Material::getColor(){
	return color;
}

const ST::Program* ST::Material::getProgram(){
	return program;
}

ST::Material::Material(const Material& o){
	color = o.color;
	program = o.program;
}

ST::Material::~Material(){
	
}