#include <err.h>
#include <SDL2/SDL.h>

int main() {
	int error;
	int quit;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Surface *surface;
	SDL_Texture *texture;
	SDL_Event event;

	error = 0;
	quit = 0;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		warnx("SDL_Init: %s", SDL_GetError());
		error = 1;
		goto cleanup;
	}

	window = SDL_CreateWindow("Hello World!", 100, 100, 640, 480,
	    SDL_WINDOW_SHOWN);
	if (window == NULL){
		warnx("SDL_CreateWindow: %s", SDL_GetError());
		error = 1;
		goto cleanup;
	}

	renderer = SDL_CreateRenderer(window, -1,
	    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL){
		warnx("SDL_CreateRenderer: %s", SDL_GetError());
		error = 1;
		goto cleanup;
	}

	surface = SDL_LoadBMP("hello.bmp");
	if (surface == NULL){
		warnx("SDL_LoadBMP: %s", SDL_GetError());
		error = 1;
		goto cleanup;
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (texture == NULL){
		warnx("SDL_CreateTextureFromSurface: %s", SDL_GetError());
		error = 1;
		goto cleanup;
	}

	while (!quit) {
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
		
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = 1;
				break;
			}
		}
	}
cleanup:
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return error;
}
