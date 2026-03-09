#ifndef			__HPP_ENGINE__
#define			__HPP_ENGINE__

#include <SDL3/SDL.h>


class Scene;

// Singleton pattern to ensure we only have one
// instance of Engine at a time.
class Engine {
	public:
		// Returns the instance.
		static Engine& instance(){
			static Engine instance;
			return instance;
		}

		// Delete copy operators.  No copies!
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;

		SDL_Renderer* getRenderer();
		void setScene(Scene* scene);
		void run();

		Engine();
		~Engine() = default;

		bool init();

		void shutdown();

		SDL_Window* window;
		SDL_Renderer* renderer;
		bool running = false;
		// Notice that we are storing copies of the
		// events, not pointers or references.
		static const bool* keyState;
		Scene* scene = nullptr;
};

#endif
