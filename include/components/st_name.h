#ifndef _SPACE_TURTLE_NAME_H_
#define _SPACE_TURTLE_NAME_H_ 1

namespace ST {

	class NameComponent {
	public:
		NameComponent();

		void setName(const char* name);
		const char* getName() const;

		~NameComponent();
	private:
		char name_[50];
	};
}

#endif