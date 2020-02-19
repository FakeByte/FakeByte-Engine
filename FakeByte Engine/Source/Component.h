#pragma once
#include <typeinfo>

//Base class for Components
struct Component {
	size_t getType() const {
		// must dereference the pointer to get at the polymorphic type.
		return typeid(*this).hash_code();
	}

protected:
	virtual ~Component() = default;
};