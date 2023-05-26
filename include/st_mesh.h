#ifndef _SPACE_TURTLE_MESH_H_
#define _SPACE_TURTLE_MESH_H_ 1

#include <glad.h>
#include <vector>
#include <string>
#include <transform.hpp>

namespace ST {

	struct VertexInfo {
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 uv;
		glm::vec3 tangent;
		glm::vec3 bitangent;

		bool VertexInfo::operator==(const VertexInfo& other) const {
			return (pos == other.pos && normal == other.normal && uv == other.uv);
		}
	};

	struct InstanceInfo {
		glm::mat4 matrix;
		glm::vec4 color;
		glm::ivec2 textureIndex;
		float roughness;
		float metallic;
	};

	enum CullMode{
		kCull_Disable,
		kCull_Front,
		kCull_Back,
		kCull_Both
	};
	enum DepthMode {
		kDepth_Nothing,
		kDepth_Disable,
		kDepth_Always,
		kDepth_Never,
		kDepth_Less,
		kDepth_Equal,
		kDepth_LessEqual,
		kDepth_Greater,
		kDepth_NoEqual,
		kDepth_GreaterEqual
	};

	// ------------------- BASE -------------------
	class Mesh{

	public:
		Mesh();
		const GLuint getID();

		const char* getName();
		void setName(char* n);

		glm::vec3 getMinPoint() const;
		glm::vec3 getMaxPoint() const;

		virtual void setInstanceData(const std::vector<InstanceInfo>& data);
		virtual void render();

		std::vector<VertexInfo> vertices_;
		std::vector<unsigned int> indices_;

		bool operator==(const Mesh& rhs);

		CullMode cullmode_;
		DepthMode depthmode_;

		~Mesh();
		//Mesh(const Mesh& o);
	protected:

		void CalculateTangentBitangent();

		std::string name_;
		GLuint internalId;

		GLuint instanceBuffer;
		int numInstances;
	};

	// ------------------- Basics 2D -------------------
	class Triangle : public Mesh{
	public:
		Triangle();
		void render() override;
		void setInstanceData(const std::vector<InstanceInfo>& data) override;
		~Triangle();
	};

	class Quad : public Mesh {
	public:
		Quad();
		void render() override;
		void setInstanceData(const std::vector<InstanceInfo>& data) override;
		~Quad();
	};

	class Circle : public Mesh {
	public:
		Circle();
		void render() override;
		void setInstanceData(const std::vector<InstanceInfo>& data) override;

		void changeRebolutions(int r);
		int getRebolutions();
		~Circle();
	private:
		int rebolutions_;
	};

	// ------------------- 3D -------------------
	
	// ------- Cube -------
	class Cube : public Mesh {
	public:
		Cube();
		void render() override;
		void setInstanceData(const std::vector<InstanceInfo>& data) override;
		~Cube();
	};

	// ------- Geometry -------
	class Geometry : public Mesh {
	public:
		Geometry();
	
		bool loadFromFile(const char* path);
		void render() override;
		void setInstanceData(const std::vector<InstanceInfo>& data) override;
	
		~Geometry();
	};
}

#endif