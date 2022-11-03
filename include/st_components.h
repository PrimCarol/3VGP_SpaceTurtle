#ifndef _SPACE_TURTLE_COMPONENTS_H_
#define _SPACE_TURTLE_COMPONENTS_H_ 1

#include <transform.hpp>

namespace ST {

	// --------------------------- Struct Comps ID ----------------------------
	enum CompType {
		kComp_None,
		kComp_Trans,
		kComp_Mesh,
		kComp_Material,
	};

	struct ComponentId {
		size_t value = 0;
		CompType type = ST::kComp_None;
	};

	struct TransformComponentId : ComponentId {	};
	struct MeshComponentId : ComponentId {};
	struct MaterialComponentId : ComponentId {};

	// --------------------------- Usability ----------------------------

	class Components{
	public:
		Components();
		~Components();
	private:
		//Components(const Components& o);
	};

	class MaterialComponent : public Components{
	public:
		MaterialComponent();
		~MaterialComponent();
	private:
		//MaterialComponent(const MaterialComponent& o);
	};

	class TransformComponent : public Components {
	public:
		TransformComponent();

		//----------------- Transforms ------------------
		/*Moves based on your current position*/
		void Move(glm::vec3 newPos);
		void RotateX(float r);
		void RotateY(float r);
		void RotateZ(float r);

		/*Set a forced position*/
		void setPosition(const glm::vec3 pos);
		/*Set a forced scale*/
		void setScale(const glm::vec3 newScale);

		glm::vec3 getPosition();
		glm::vec3 getScale();
		glm::vec3 getRotation();

		~TransformComponent();
	private:
		glm::mat4 m_transform_;
		//TransformComponent(const TransformComponent& o);
	};

	class MeshComponent : public Components {
	public:
		MeshComponent();
		~MeshComponent();
	private:
		//MeshComponent(const MeshComponent& o);
	};
}

#endif