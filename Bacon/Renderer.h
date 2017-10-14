#pragma once

#include "Scene.h"

class Renderer {
public:
	Renderer ();
	~Renderer ();

	void Render (Scene scene);

	enum RenderType {
		FORWARD,
		DEFERRED
	};
};