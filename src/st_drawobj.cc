#include <st_drawobj.h>

#include <st_utilities.h>
#include <st_shader.h>

ST::DrawObj::DrawObj() {
	
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

	mesh = NULL;
}

void ST::DrawObj::draw(){
	if (program) {
		program->use();
		GLuint uniform = 0;
		glGetUniformLocation(uniform, "u_m_trans");
		glUniformMatrix4fv(uniform, 1, GL_FALSE, &m_transform[0][0]);
	}
	if (mesh) {
		mesh->render();
	}
}

void ST::DrawObj::setMesh(ST::Mesh* m){
	mesh = m;
}

void ST::DrawObj::setMaterial(ST::Program *p){
	program = p;
}

ST::DrawObj::~DrawObj(){
	
}
