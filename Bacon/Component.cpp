#include "stdafx.h"
#include "Component.h"

Component::Component () {}

Component::~Component () {}

std::string Component::ComponentName () {
	return _componentName;
}
