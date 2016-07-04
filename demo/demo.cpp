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
#include <glfw3.h>

#include <common/renderer.h>
//#include <common/sprite.h>
#include <common/input.h>
#include <common/print.h>

int main( void )
{
	Renderer renderer;

	if(renderer.SDLinit() == -1){
		printf( "Failed to initialize!\n" );
	} else {
		if(!renderer.loadmedia()){
			printf( "Failed to load media!\n" );
		}
	}

	bool quit = false;

	SDL_Event e;

	do{
		while( SDL_PollEvent( &e ) != 0 ) {

			//User requests quit
			if( e.type == SDL_QUIT ) {
				quit = true;
			} else if( e.type == SDL_KEYDOWN ) { //User presses a key
				//Select surfaces based on key press
				/*switch( e.key.keysym.sym ) {
					case SDLK_UP:
					renderer.changeimage(KEY_PRESS_UP);
					break;

					case SDLK_DOWN:
					renderer.changeimage(KEY_PRESS_DOWN);
					break;

					default:
					renderer.changeimage(KEY_PRESS_DEFAULT);
					break;
				}*/
			}
		}

		renderer.drawSDLwindow();
	} while(!quit);

	renderer.close();

	/*renderer.init();
	Sprite* sprite = new Sprite();

	do {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sprite->rotZ(sprite->rotZ() + 0.01);
		renderer.renderSprite(sprite);

		// Swap buffers
		glfwSwapBuffers(renderer.window());
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(renderer.window(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(renderer.window()) == 0 );

	delete sprite;*/

	return 0;
}
