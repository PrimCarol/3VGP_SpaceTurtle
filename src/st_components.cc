#include <st_components.h>
#include <stdio.h>

// -------------------- Parent ---------------------
ST::Components::Components(){
	printf("Component: Parent\n");
}

ST::Components::~Components(){ }

// -------------------- Mesh ---------------------
ST::MeshComponent::MeshComponent(){
	printf("Component: Mesh\n");
}

ST::MeshComponent::~MeshComponent(){ }

// -------------------- Transform ---------------------
ST::TransformComponent::TransformComponent(){
	printf("Component: Transform\n");
}

ST::TransformComponent::~TransformComponent(){ }

// -------------------- Material ---------------------
ST::MaterialComponent::MaterialComponent(){
	printf("Component: Material\n");
}

ST::MaterialComponent::~MaterialComponent(){ }
