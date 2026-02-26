#include "Projectile.hpp"

void Projectile::update(float dt) {
    const SDL_FRect& r = getRect();
    float newY = r.y + dirY * speed * dt;
    setPosition(r.x, newY);
    if (newY + r.h < 0.0f || newY > 600.0f) setActive(false);
};

void Projectile::render(SDL_Renderer* renderer) {
    const SDL_FRect& r = getRect();

    if (type == ProjectileType::PlayerBasic) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    } else if (type == ProjectileType::EnemyBasic) {
        SDL_SetRenderDrawColor(renderer, 255, 80, 80, 255);
    }

    SDL_RenderFillRect(renderer, &r);
};

void Projectile::setDirection(float dir) {
    dirY = dir;
}

void Projectile::setSpeed(float s) {
    speed = s;
}

void Projectile::setType(ProjectileType t) {
    type = t;
}

ProjectileType Projectile::getType() const {
    return type;
}
