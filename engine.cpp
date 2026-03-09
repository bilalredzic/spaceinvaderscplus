#include "Engine.hpp"
#include "Scene.hpp"
#include "Projectile.hpp"
#include "Enemy.hpp"
#include "AudioManager.hpp"


#include <SDL3/SDL.h>
// Want to share these.  Easiest (and quick) way
// is with a static data structure.
const bool* Engine::keyState = nullptr;

Engine::Engine() { init(); }

SDL_Renderer* Engine::getRenderer() { return this->renderer; };

void Engine::setScene(Scene *scene) {
	// Cleanly exit the current scene before activating the next one.
	if (this->scene != nullptr) {
		this->scene->exit();
	}
	this->scene = scene;
	// Let the new scene perform its setup as soon as it becomes active.
	if (this->scene != nullptr) {
		this->scene->enter();
	}
}
void Engine::run() {
	running = true;
	// Track when the previous frame started so we can compute real delta time.
	Uint64 lastFrameTime = SDL_GetPerformanceCounter(); //hardware level ticks, better than ticks
	Uint64 performanceFrequency = SDL_GetPerformanceFrequency();
	while (running) {
		// Measure how much real time passed since the previous frame.
		Uint64 currentFrameTime = SDL_GetPerformanceCounter();
		// Convert elapsed milliseconds into seconds as a float for movement/update math.
		float dt = static_cast<float>(currentFrameTime - lastFrameTime) / performanceFrequency;
		// Store this frame time so the next loop can measure against it.
		lastFrameTime = currentFrameTime;
		if (dt > 0.033f) dt = 0.033f; // cap dt to maximum of 0.033 seconds, rougly one fram at 30 fps.
		// Snapshot current keyboard state before handing input to the active scene.
		Engine::keyState = SDL_GetKeyboardState(nullptr);
        SDL_Event event;
		// Poll SDL events so the window can close and input stays responsive.
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				    SDL_Log("Shutting down...");
				    running = false;
			    }
			}

		// Clear the frame, run the active scene, then present the finished image.
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		if (scene != nullptr) {
			scene->handleInput();
			scene->update(dt);
			scene->render(renderer);
		}
		SDL_RenderPresent(renderer);
    }
}

bool Engine::init() {
	// Initialize SDL video before creating the game window and renderer.
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("SDL_Init failed: %s", SDL_GetError());
		return false;
	}

	// Gotta draw somewhere....
	window = SDL_CreateWindow("Space Invaders", 800, 600, 0);

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
	// Initialize audio and load the shared sound effects and music for the game.
	AudioManager::instance().init();
	AudioManager::instance().loadShootSound("assets/playerlaser.wav");
	AudioManager::instance().loadEnemyShootSound("assets/enemylaser.wav");
	AudioManager::instance().loadPlayerHitSound("assets/playerhit.wav");
	AudioManager::instance().loadEnemyHitSound("assets/enemyhit.wav");
	AudioManager::instance().loadLevelUpSound("assets/levelup.wav");
	AudioManager::instance().loadGameOverSound("assets/gameover.wav");
	AudioManager::instance().loadProjectileClashSound("assets/collision.wav");
	AudioManager::instance().loadMusic("assets/backgroundmusic.wav");
	AudioManager::instance().playMusic();



	SDL_SetRenderVSync(renderer, 0);

	return true;
}

void Engine::shutdown() {
	// Release renderer/window resources and unload shared textures and audio before quitting SDL.
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Projectile::unloadSharedTextures();
	Enemy::unloadSharedTexture();
	AudioManager::instance().shutdown();


	SDL_Quit();
}
