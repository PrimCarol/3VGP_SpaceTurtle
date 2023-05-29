#ifndef _SPACE_TURTLE_NAME_H_
#define _SPACE_TURTLE_NAME_H_ 1

namespace ST {

	class NameComponent {
	public:
		NameComponent();

		/**
		* @brief Set Name of GameObj
		*/
		void setName(const char* name);
		/**
		* @brief Get Name of GameObj
		*/
		const char* getName() const;

		~NameComponent();
	private:
		char name_[50];
	};
}

#endif