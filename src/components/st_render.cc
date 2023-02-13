#include <components/st_render.h>


// -------------------- Mesh ---------------------
ST::RenderComponent::RenderComponent(){
	//printf("Create Component: Render\n");
	mesh = nullptr;
	//material = nullptr;

	visible_ = true;
	//mesh = new ST::Circle();
	//material = std::make_unique<ST::Material>();
}

void ST::RenderComponent::setMesh(ST::Mesh* m){
	mesh = m;
}

//void ST::RenderComponent::setMaterial(std::unique_ptr<ST::Material>& m){
//	//material = std::move(m);
//}

ST::RenderComponent::~RenderComponent(){
	//printf("Destroy Component: Render\n");
}
