#pragma once

#include "Transform.h"
#include "Component.h"
#include <list>

class GameObject {
public:
	GameObject ();
	~GameObject ();

	std::string name;
	Transform transform;
	std::list<Component> _components;
private:
};