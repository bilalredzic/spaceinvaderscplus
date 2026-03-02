#ifndef     __ENEMY_HPP__
#define     __ENEMY_HPP__

#include "GameObject.hpp"
#include <SDL3/SDL.h>


// Basic enemy ship that moves downward and fires on its own cooldown.
class Enemy : public GameObject {
    public:
        ~Enemy() override = default;

        void update(float dt) override;
        void render(SDL_Renderer* renderer) override;

        bool canShoot(float dt);
        void setShootCooldown(float cooldown);
        void setInitialShootTimer(float t);
        void setSpeed(float s);
        static void loadSharedTexture(SDL_Renderer* renderer);
        static void unloadSharedTexture();

    private:
        // Per-enemy movement/fire timing plus one shared enemy sprite texture.
        float speed = 175.0f;
        float shootCooldown = 2.5f;
        float shootTimer = 0.0f;
        static SDL_Texture* enemyTexture;




};





#endif
