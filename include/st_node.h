#ifndef _SPACE_TURTLE_NODE_H_
#define _SPACE_TURTLE_NODE_H_ 1

#include <glm.hpp>
#include <vector>

#include <transform.hpp>

namespace ST {

	class Node{
	public:
		//----------------- Info ------------------
		void setName(const char* n);
		const char* getName();

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
	
		//----------------- Childs/Parents ------------------
		ST::Node* getParent() const;
		int getChildCount() const;
		ST::Node* getChild(int index) const;
		void addChild(Node* n);

	protected:

		Node();
		~Node();

		glm::mat4 m_transform_;
	private:
		Node(const Node& o);

		const char* name_;
		Node* parent_;
		std::vector<Node*> child_;
	};
}

#endif