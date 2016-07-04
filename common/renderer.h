#ifndef RENDERER_H
#define RENDERER_H

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string>

// Include GLEW
#include <GL/glew.h>

//Includs SDL
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

// Include GLFW
//#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <common/shader.h>
#include <common/sprite.h>
#include <common/texture.h>
#include <common/camera.h>
#include <common/input.h>
#include <common/print.h>

class Renderer
{
	public:

		Renderer();
		virtual ~Renderer();

		int SDLinit();
		bool loadmedia();
		void drawSDLwindow();
		void close();
		void changeimage(KeyPressSurfaces key);
		SDL_Surface* StretchSurface( SDL_Surface surface);

		//int init();

		void renderSprite(Sprite* sprite);
		//GLFWwindow* window() { return _window; };

	private:
		SDL_Window* sdlwindow;
		SDL_Surface* screensurface;
		SDL_Surface* surfaces[ KEY_PRESS_TOTAL ];
		SDL_Surface* currentsurface;
		SDL_Surface* loadSurface(std::string path);

		//Load Texture Tutorial
		SDL_Renderer* gRenderer = NULL;
		SDL_Texture* gTexture = NULL;
		SDL_Texture* loadTexture(std::string path);

		//GLFWwindow* _window;
		int window_width;
		int window_height;

		std::string fragment_shader;
		std::string vertex_shader;

		GLuint programID;
		GLuint vertexPosition_modelspaceID;
		GLuint vertexUVID;
		GLuint matrixID;
		GLuint textureID;

		glm::mat4 ProjectionMatrix;
};

#endif /* RENDERER_H */
