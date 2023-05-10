#include <components/st_render.h>

ST::RenderComponent::RenderComponent(){
	mesh = nullptr;

	visible_ = true;
	castShadow_ = true;

	thiscullmode_ = ST::kCull_Back;
	thisdepthmode_ = ST::kDepth_LessEqual;
	//material = nullptr;
	//// esto no me deja hacerlo por el optional.
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
