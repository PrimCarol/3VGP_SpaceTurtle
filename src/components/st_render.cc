#include <components/st_render.h>


// -------------------- Mesh ---------------------
ST::RenderComponent::RenderComponent(){
	printf("Create Component: Render\n");
	mesh = nullptr;
	material = nullptr;

	mesh = new ST::Circle();
	material = new ST::Material();
}

void ST::RenderComponent::setMesh(ST::Mesh* m){
	mesh = m;
}

void ST::RenderComponent::setMaterial(ST::Material* m){
	material = m;
}

ST::RenderComponent::~RenderComponent(){
	//printf("Destroy Component: Render\n");
}
