#ifndef _SPACE_TURTLE_NODE_H_
#define _SPACE_TURTLE_NODE_H_ 1

#include <glm.hpp>
#include <transform.hpp>

namespace ST {

	class Node{
	public:
	
		void Move(glm::vec3 newPos);
		void Scale(glm::vec3 newScale);
		void RotateX(float r);
		void RotateY(float r);
		void RotateZ(float r);

		glm::vec3 getPosition();
		glm::vec3 getScale();
		glm::vec3 getRotation();
	
	protected:

		Node();
		~Node();

		glm::mat4 m_transform;
	private:
		Node(const Node& o);


		//Node* childs;
		//std:vector<Node> childs;
	};
}

#endif