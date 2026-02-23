#include "Engine.hpp"
#include "Scene.hpp"

#include <SDL3/SDL.h>

// Want to share these.  Easiest (and quick) way
// is with a static data structure.
const bool* Engine::keyState = nullptr;

Engine::Engine() { init(); }

SDL_Renderer* Engine::getRenderer() { return this->renderer; };

void Engine::setScene(Scene *scene) {
	if (this->scene != nullptr) {
		this->scene->exit();
	}
	this->scene = scene;
	if (this->scene != nullptr) {
		this->scene->enter();
	}
}
void Engine::run() {
	running = true;
	while (running) {
		// Clear the events from the last frame first.
		Engine::keyState = SDL_GetKeyboardState(nullptr);
        SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				    SDL_Log("Shutting down...");
				    running = false;
			    }
			}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		if (scene != nullptr) {
			scene->handleInput();
			scene->update(targetFrameTime/1000.0f);
			scene->render(renderer);
		}
		SDL_RenderPresent(renderer);
		// Naive delay that doesn't take into account
		// how long the loop ran.
		SDL_Delay(targetFrameTime);
    }
}

bool Engine::init() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("SDL_Init failed: %s", SDL_GetError());
		return false;
	}

	// Gotta draw somewhere....
	window = SDL_CreateWindow("RGB Color Cycle", 800, 600, 0);

	if (!window) {
		SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
		SDL_Quit();
		return false;
	}

	// Who is in charge of drawing?
	renderer = SDL_CreateRenderer(window, NULL);
	if (!renderer) {
		SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return false;
	}

	SDL_SetRenderVSync(renderer, 0);

	return true;
}

void Engine::shutdown() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
