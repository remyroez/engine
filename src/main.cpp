#include <SDL2/SDL.h>
#include "hex/hex.hpp"

int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_VIDEO);

	hex::sdl2::Window window(
		"test window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_SHOWN
	);

	bool running = true;
	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN:
					running = false;
					break;
			}
		}
		SDL_Delay(1);
	}

	window.destroy();

	SDL_Quit();
	return 0;
}
