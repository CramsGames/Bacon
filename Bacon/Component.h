#pragma once

#include <string>

class Component {
public:
	Component ();
	~Component ();

	std::string ComponentName ();

private:
	std::string _componentName;
};