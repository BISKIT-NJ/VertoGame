/* 
*	Following along YouTube series "Learn Game Programming in C" -VertoStudio3D
*	by Carlos "BISKIT" Garcia 2022
*/

#include "SDL.h"
#include <stdio.h>

#pragma warning(disable: 26451) // Disable warning about Arithmetic overflow in SDL header

typedef struct {

	int x, y;
	short life;
	char* name;

} Man;

int ProcessEvents(SDL_Window *window, Man *man) {
	SDL_Event event;
	int done = 0;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_WINDOWEVENT_CLOSE: {
			if (window) {
				SDL_DestroyWindow(window);
				window = NULL;
				done = 1;
			}
		}
		break;
		case SDL_KEYDOWN: {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				done = 1;
				break;
			case SDLK_RIGHT:
				man->x += 10;
				break;
			case SDLK_LEFT:
				man->x -= 10;
				break;
			}
		}
		break;
		case SDL_QUIT:
			//quit out of the game
			done = 1;
			break;
		}
	}

	return done;
}

void Do_Renderer(SDL_Renderer* renderer, Man *man) {

	// set the drawing color to blue
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	//Clear the screen to blue
	SDL_RenderClear(renderer);

	// Set the drawing color to white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Rect rect = { man->x, man->y, 200, 200 };
	SDL_RenderFillRect(renderer, &rect);

	// We are done drawing, "present" or show to the screen what we've drawn
	SDL_RenderPresent(renderer);
}

int main(int argc, char* args[]) {
	
	SDL_Window* window;				// Declare a window
	SDL_Renderer* renderer;			// Declare a renderer

	SDL_Init(SDL_INIT_VIDEO);		// Initialize SDL2

	Man man;
	man.x = 220;
	man.y = 240;

	//Create an application window with the following settings:
	window = SDL_CreateWindow("Game Window", // window title
		SDL_WINDOWPOS_UNDEFINED,			// initial x position
		SDL_WINDOWPOS_UNDEFINED,			// initial y position
		640,								// width, in pixels
		480,								// height, in pixels
		0);									// flags

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// The window is open:enter program loop
	int done = 0;

	// Event loop
	while (!done) {

		//check for events
		if (ProcessEvents(window, &man) == 1) {
			done = 1;
		}

		// Render display
		Do_Renderer(renderer, &man);
		
		// dont burn up the cpu
		SDL_Delay(100);
	}

	//Close and destroy the window
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	//Clean up
	SDL_Quit();
	return 0;
}