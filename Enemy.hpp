#ifndef     __ENEMY_HPP__
#define     __ENEMY_HPP__

#include "GameObject.hpp"
#include <SDL3/SDL.h>


class Enemy : public GameObject {
    public:
        ~Enemy() override = default;

        void update(float dt) override;
        void render(SDL_Renderer* renderer) override;

        bool canShoot(float dt);
        void setShootCooldown(float cooldown);
        void setInitialShootTimer(float t);
    private:
        float speed = 175.0f;
        float shootCooldown = 2.5f;
        float shootTimer = 0.0f;



};





#endif