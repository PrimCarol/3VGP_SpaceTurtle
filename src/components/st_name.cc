#include <components/st_name.h>

#include <iostream>

ST::NameComponent::NameComponent(){
	snprintf(name_, 50, "GameObj");
}

void ST::NameComponent::setName(const char* name) {
	snprintf(name_, 50, name);
}

const char* ST::NameComponent::getName() const {
	return &name_[0];
}

ST::NameComponent::~NameComponent(){

}
