#ifndef _SPACE_TURTLE_COMPONENTS_H_
#define _SPACE_TURTLE_COMPONENTS_H_ 1

namespace ST {

	class Component{
	protected:
		Component();
		~Component();
	private:
		Component(const Component& o);
	};

	class MaterialComponent : public Component{
	public:
		MaterialComponent();
		~MaterialComponent();
	private:
		MaterialComponent(const MaterialComponent& o);
	};

	class TransformComponent : public Component {
	public:
		TransformComponent();
		~TransformComponent();
	private:
		TransformComponent(const TransformComponent& o);
	};

	class MeshComponent : public Component {
	public:
		MeshComponent();
		~MeshComponent();
	private:
		MeshComponent(const MeshComponent& o);
	};
}

#endif