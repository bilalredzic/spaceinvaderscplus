#ifndef     __PROJECTILE_HPP__
#define     __PROJECTILE_HPP__

#include "GameObject.hpp"
#include <SDL3/SDL.h>

class Projectile : public GameObject {
    public:
        ~Projectile() override = default;

        void update(float dt) override;
        void render(SDL_Renderer* renderer) override;

        

    private:
        float speed = 500.0f;
        float dirY = -1.0f;

};






#endif