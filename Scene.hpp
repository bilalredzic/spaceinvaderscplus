#ifndef         __SCENE_HPP__
#define         __SCENE_HPP__

#include <SDL3/SDL.h>

// Base interface for every game scene (title, play, credits).
class Scene {
    public:
        // Required for proper cleanup through a Scene pointer.
        virtual ~Scene() = default;
        // Handle per-frame input for this scene.
        virtual void handleInput() = 0;
        // Advance scene logic by delta time.
        virtual void update(float dt) = 0;
        // Draw scene contents.
        virtual void render(SDL_Renderer* r) = 0;
        // Called once when scene becomes active.
        virtual void enter() = 0;
        // Called once before scene is replaced.
        virtual void exit() = 0;
};





#endif
