#include "Enemy.hpp"

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
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &r);
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