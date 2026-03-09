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
        void setInitialShootTimer(float t);
        void setSpeed(float s);
        static void loadSharedTexture(SDL_Renderer* renderer);
        static void unloadSharedTexture();

        static constexpr float baseWidth = 40.0f;
        static constexpr float baseHeight = 20.0f;
        static constexpr float baseSpeed = 175.0f;
        static constexpr float baseShootCooldown = 1.2f;
        static constexpr float baseInitialShootTimer = 0.5f;

    private:
        // Per-enemy movement/fire timing plus one shared enemy sprite texture.
        float speed = baseSpeed;
        float shootCooldown = baseShootCooldown;
        float shootTimer = 0.0f;
        static SDL_Texture* enemyTexture;




};





#endif
