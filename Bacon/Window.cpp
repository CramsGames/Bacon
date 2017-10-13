#include "stdafx.h"
#include "Window.h"

#include <iostream>
#include <gl/glew.h>
#include <assert.h>

Window::Window (int width, int height, std::string title, bool windowed) {
	SDL_GL_SetAttribute (SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute (SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute (SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute (SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute (SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute (SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);

	if (SDL_Init (SDL_INIT_EVENTS | SDL_INIT_VIDEO) < 0) {
		std::cerr << "Error when initializing SDL: " << SDL_GetError () << std::endl;
		SDL_Quit ();
		return;
	}

	_window = SDL_CreateWindow (title.c_str (), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, windowed ? SDL_WINDOW_OPENGL : SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
	_glContext = SDL_GL_CreateContext (_window);


	GLenum status = glewInit ();
	if (status != GLEW_OK) {
		std::cerr << "Glew failed to initialize: " << glewGetErrorString (status) << std::endl;
		SDL_GL_DeleteContext (_glContext);
		SDL_DestroyWindow (_window);
		SDL_Quit ();
		return;
	}

	_isOpen = true;
	glFrontFace (GL_CCW);
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_CULL_FACE);
	glCullFace (GL_BACK);
}

Window::~Window () {
	SDL_GL_DeleteContext (_glContext);
	SDL_DestroyWindow (_window);
	SDL_Quit ();
}

void Window::Clear (float r, float g, float b, float a) {
	glClearColor (r, g, b, a);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::SwapBuffers () {
	SDL_GL_SwapWindow (_window);
}

void Window::Update () {
	SDL_Event event;


	std::fill (_keysDown, _keysDown + sizeof (_keysDown), false);
	std::fill (_keysUp, _keysUp + sizeof (_keysUp), false);

	while (SDL_PollEvent (&event)) {
		switch (event.type) {
			case SDL_QUIT:
				_isOpen = false;
				break;
			case SDL_WINDOWEVENT:
				switch (event.window.event) {
					case SDL_WINDOWEVENT_FOCUS_GAINED:
						_inputFocus = true;
						break;
					case SDL_WINDOWEVENT_FOCUS_LOST:
						_inputFocus = false;
						break;
					default:
						break;
				}
				break;
			case SDL_KEYDOWN:
				_keysHeld [event.key.keysym.scancode] = true;
				_keysDown [event.key.keysym.scancode] = true;
				break;
			case SDL_KEYUP:
				_keysHeld [event.key.keysym.scancode] = false;
				_keysUp [event.key.keysym.scancode] = true;
				break;
		}
	}
}

bool Window::GetKey (int scanCode) {
	assert (scanCode < 512);
	return _keysHeld [scanCode];
}

bool Window::GetKeyDown (int scanCode) {
	assert (scanCode < 512);
	return _keysDown [scanCode];
}

bool Window::GetKeyUp (int scanCode) {
	assert (scanCode < 512);
	return _keysUp [scanCode];
}