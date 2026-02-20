#ifndef     __ENEMY_HPP__
#define     __ENEMY_HPP__

#include "GameObject.hpp"
#include <SDL3/SDL.h>


class Enemy : public GameObject {
    public:
        ~Enemy() override = default;

        void update(float dt) override;
        void render(SDL_Renderer* renderer) override;
    private:
        float speed = 250.0f;


};





#endif