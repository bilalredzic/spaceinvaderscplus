#include "Enemy.hpp"
#include <SDL3_image/SDL_image.h>
#include "Engine.hpp"

// All basic enemies reuse the same shared sprite texture.
SDL_Texture* Enemy::enemyTexture = nullptr;

void Enemy::update(float dt) {
    const SDL_FRect& r = getRect();
    // Move the enemy downward each frame based on its current speed.
    float newY = r.y + speed * dt;
    setPosition(r.x, newY);
    
    // Deactivate enemies once they move off the bottom of the screen.
    if (newY > 600.0f) {
        setActive(false);
    }
};

void Enemy::render(SDL_Renderer* renderer) {
    const SDL_FRect& r = getRect();

    // Render the shared enemy sprite when it is available.
    if (enemyTexture != nullptr) {
        SDL_RenderTexture(renderer, enemyTexture, nullptr, &r);
        return;
    }
};

bool Enemy::canShoot(float dt) {
    // Count down this enemy's personal shoot timer and fire when it expires.
    shootTimer -=dt;
    if (shootTimer <= 0.0f) {
        shootTimer = shootCooldown;
        return true;
    }
    return false;
}

void Enemy::setShootCooldown(float cooldown) {
    shootCooldown = cooldown;
}

void Enemy::setInitialShootTimer(float t) {
    shootTimer = t;
}

void Enemy::setSpeed(float s) {
    speed = s;
}

void Enemy::loadSharedTexture(SDL_Renderer* renderer) {
    // Load the enemy sprite once so every enemy instance can reuse it.
    if (enemyTexture == nullptr) {
        SDL_Surface* surface = IMG_Load("assets/enemy.png");
        if (!surface) {
            SDL_Log("IMG_Load failed for enemy.png: %s", SDL_GetError());
        } else {
            enemyTexture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_DestroySurface(surface);

            if (!enemyTexture) {
                SDL_Log("SDL_CreateTextureFromSurface failed for enemy.png: %s", SDL_GetError());
            }
        }
    }
}
void Enemy::unloadSharedTexture() {
    // Release the shared enemy texture during engine shutdown.
    if (enemyTexture != nullptr) {
        SDL_DestroyTexture(enemyTexture);
        enemyTexture = nullptr;
    }
}
