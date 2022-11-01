#ifndef _SPACE_TURTLE_COMPONENTS_H_
#define _SPACE_TURTLE_COMPONENTS_H_ 1

namespace ST {

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
		MaterialComponent(const MaterialComponent& o);
	};

	class TransformComponent : public Components {
	public:
		TransformComponent();
		~TransformComponent();
	private:
		TransformComponent(const TransformComponent& o);
	};

	class MeshComponent : public Components {
	public:
		MeshComponent();
		~MeshComponent();
	private:
		MeshComponent(const MeshComponent& o);
	};
}

#endif