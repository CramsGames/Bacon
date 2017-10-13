#pragma once
#include <string>
#include <sdl2\SDL.h>
#undef main

class Window {
public:
	Window (int width = 1280, int height = 720, std::string title = "Bacon Project", bool windowed = true);
	virtual ~Window ();

	void Clear (float r, float g, float b, float a);
	void SwapBuffers ();
	void Update ();

	bool GetKey (int scanCode);
	bool GetKeyDown (int scanCode);
	bool GetKeyUp (int scanCode);

	inline bool IsOpen () {
		return _isOpen;
	};

private:
	SDL_Window* _window;
	SDL_GLContext _glContext;
	bool _isOpen;
	bool _inputFocus;
	bool _keysHeld [512] = {false};
	bool _keysDown [512] = {false};
	bool _keysUp [512] = {false};
};