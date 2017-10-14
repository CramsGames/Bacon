// Bacon.cpp : Defines the entry point for the console application.

// Header
#include "stdafx.h"

// Defines for quick testing
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "Bacon Project"
#define WINDOW_WINDOWED true

#define CAMERA_NEAR 0.01
#define CAMERA_FAR 10000.0

#define CAMERA_SPEED 10.0
#define CAMERA_ROT 4.0

// Includes
#include "Window.h"
#include "Time.h"
#include "Mesh.h"
#include "Model.h"
#include "PerspCamera.h"
#include "UnlitShader.h"
#include "LambertShader.h"
#include "Texture.h"

// Entry - lowercase because... Windows
int main () {
	// Create window and camera
	Window window = Window (WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, WINDOW_WINDOWED);
	Transform cameraTransform = Transform ();
	PerspCamera camera = PerspCamera (&cameraTransform, WINDOW_WIDTH, WINDOW_HEIGHT, glm::half_pi<double> (), CAMERA_NEAR, CAMERA_FAR);

	// Create mesh
	/*
	glm::vec3 *position = new glm::vec3 [3] { // Positional coordinates follow the right hand rule. +X is left, +Y is up, +Z is forward
		glm::vec3 (0.5f, 0.5f, 0.0f),
		glm::vec3 (0.5f, -0.5f, 0.0f),
		glm::vec3 (-0.5f, -0.5f, 0.0f)
	};

	glm::vec2 *texcoord = new glm::vec2 [3] { // Texture coordinates follow the ST system
		glm::vec2 (0.0f, 0.0f),
		glm::vec2 (0.0f, 1.0f),
		glm::vec2 (1.0f, 1.0f)
	};

	glm::vec3 *normal = new glm::vec3 [3] { // Follows the right hand rule. +X is left, +Y is up, +Z is forward
		glm::vec3 (0.0f, 0.0f, 1.0f),
		glm::vec3 (0.0f, 0.0f, 1.0f),
		glm::vec3 (0.0f, 0.0f, 1.0f)
	};

	unsigned int *indices = new unsigned int [3] {
		0, 1, 2
	};

	Mesh mesh = Mesh::Mesh (position, texcoord, normal, 3, indices, 3);
	*/

	Mesh mesh = Model::Load ("res\\models\\ship.obj").ToMesh ();

	// Mesh transform
	Transform meshTransform = Transform (glm::vec3 (0, 0, 10));

	// Mesh texture
	Texture texture = Texture ("res\\textures\\mc_atlas.png");

	// Shader used to render
	//UnlitShader shader = UnlitShader ("res\\shaders\\unlit");
	LambertShader shader = LambertShader ("res\\shaders\\lambert");

	// Game loop
	while (window.IsOpen ()) {
		// Tick the game timer - calculates DeltaTime
		Time::Tick ();

		// Get updates from Windows
		window.Update ();

		// Clear the window
		window.Clear (0.0f, 0.4f, 0.6f, 1.0f);

		// Simple movement for camera
		glm::dvec3 moveVec;
		moveVec += cameraTransform.LeftD () * (double)window.GetKey (SDL_SCANCODE_A);
		moveVec += cameraTransform.RightD () * (double)window.GetKey (SDL_SCANCODE_D);
		moveVec += cameraTransform.UpD () * (double)window.GetKey (SDL_SCANCODE_SPACE);
		moveVec += cameraTransform.DownD () * (double)window.GetKey (SDL_SCANCODE_LCTRL);
		moveVec += cameraTransform.ForwardD () * (double)window.GetKey (SDL_SCANCODE_W);
		moveVec += cameraTransform.BackD () * (double)window.GetKey (SDL_SCANCODE_S);
		cameraTransform.position += moveVec * Time::DeltaTime () * CAMERA_SPEED;

		cameraTransform.Rotate (glm::dvec3 (1, 0, 0), window.GetKey (SDL_SCANCODE_DOWN) * Time::DeltaTime () * CAMERA_ROT);
		cameraTransform.Rotate (glm::dvec3 (-1, 0, 0), window.GetKey (SDL_SCANCODE_UP) * Time::DeltaTime () * CAMERA_ROT);
		cameraTransform.Rotate (glm::dvec3 (0, 1, 0), window.GetKey (SDL_SCANCODE_LEFT) * Time::DeltaTime () * CAMERA_ROT);
		cameraTransform.Rotate (glm::dvec3 (0, -1, 0), window.GetKey (SDL_SCANCODE_RIGHT) * Time::DeltaTime () * CAMERA_ROT);
		cameraTransform.Rotate (glm::dvec3 (0, 0, 1), window.GetKey (SDL_SCANCODE_E) * Time::DeltaTime () * CAMERA_ROT);
		cameraTransform.Rotate (glm::dvec3 (0, 0, -1), window.GetKey (SDL_SCANCODE_Q) * Time::DeltaTime () * CAMERA_ROT);

		// Set the texture to be used
		texture.Bind (0);

		// Set the shader to render with
		shader.Bind ();

		// Update shader information - pass to GPU

		glm::vec3 ambient = glm::vec3 (0.2f, 0.2f, 0.2f);
		glm::vec3 lightPos = cameraTransform.position;
		glm::vec3 lightColor = glm::vec3 (1.0f, 1.0f, 1.0f);
		shader.Update (meshTransform, camera, ambient, glm::vec4 (lightPos, 1), lightColor);

		// Draw the mesh
		mesh.Draw ();

		// Double buffered, show the window we just rendered to
		window.SwapBuffers ();
	}

	// Tell Windows we exited correctly
	return 0;
}