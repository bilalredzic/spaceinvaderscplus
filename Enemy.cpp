#include "Enemy.hpp"
#include <SDL3_image/SDL_image.h>
#include "Engine.hpp"

SDL_Texture* Enemy::enemyTexture = nullptr;

void Enemy::update(float dt) {
    const SDL_FRect& r = getRect();
    float newY = r.y + speed * dt;
    setPosition(r.x, newY);
    
    if (newY > 600.0f) {
        setActive(false);
    }
};

void Enemy::render(SDL_Renderer* renderer) {
    const SDL_FRect& r = getRect();

    if (enemyTexture != nullptr) {
        SDL_RenderTexture(renderer, enemyTexture, nullptr, &r);
        return;
    }
};

bool Enemy::canShoot(float dt) {
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
    if (enemyTexture != nullptr) {
        SDL_DestroyTexture(enemyTexture);
        enemyTexture = nullptr;
    }
}
