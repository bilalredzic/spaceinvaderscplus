#ifndef         __SCENE_HPP__
#define         __SCENE_HPP__

#include <SDL3/SDL.h>

class Scene {
    public:
        virtual ~Scene() = default;
        virtual void handleInput() = 0;
        virtual void update(float dt) = 0;
        virtual void render(SDL_Renderer* r) = 0;
        virtual void enter() = 0;
        virtual void exit() = 0;
};





#endif