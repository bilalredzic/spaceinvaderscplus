#include "Projectile.hpp"

void Projectile::update(float dt) {
    const SDL_FRect& r = getRect();
    float newY = r.y + dirY * speed * dt;
    setPosition(r.x, newY);
    if (newY + r.h < 0.0f) setActive(false);
};

void Projectile::render(SDL_Renderer* renderer) {
    const SDL_FRect& r = getRect();
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &r);
};

