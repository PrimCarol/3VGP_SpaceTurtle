#ifndef _SPACE_TURTLE_EMPTYOBJ_H_
#define _SPACE_TURTLE_EMPTYOBJ_H_ 1

#include <st_node.h>

namespace ST {

	class EmptyObj : public Node {
	public:
		EmptyObj();


		~EmptyObj();

	private:
		EmptyObj(const EmptyObj& o);
	};
}

#endif