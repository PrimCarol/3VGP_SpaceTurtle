#include <st_drawobj.h>

ST::DrawObj::DrawObj() {
	
	setName("DrawObject");
	
	material = new Material();
	mesh = NULL;
}

void ST::DrawObj::draw(){
	if (material) {
		material->getProgram()->use();
		GLuint u_m_trans = material->getProgram()->getUniform("u_m_trans");
		glUniformMatrix4fv(u_m_trans, 1, GL_FALSE, &m_transform_[0][0]);
		
		GLuint u_color = material->getProgram()->getUniform("u_color");;
		//glm::vec3 c = material->getSettings()->getColor();
		glm::vec3 c = material->getColor();
		glUniform3fv(u_color, 1, &c[0]);
	}
	if (mesh) {
		mesh->render();
	}
}

void ST::DrawObj::setMesh(ST::Mesh* m){
	mesh = m;
}

void ST::DrawObj::setMaterial(ST::Material *m){
	material = m;
}

ST::Material* ST::DrawObj::getMaterial(){
	return material;
}

ST::DrawObj::~DrawObj(){
	
}
