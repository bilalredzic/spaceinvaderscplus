#include "Projectile.hpp"
#include <SDL3_image/SDL_image.h>
#include "Engine.hpp"

SDL_Texture* Projectile::playerTexture = nullptr;
SDL_Texture* Projectile::enemyTexture = nullptr;


void Projectile::update(float dt) {
    const SDL_FRect& r = getRect();
    float newY = r.y + dirY * speed * dt;
    setPosition(r.x, newY);
    if (newY + r.h < 0.0f || newY > 600.0f) setActive(false);
};

void Projectile::render(SDL_Renderer* renderer) {
    const SDL_FRect& r = getRect();

    SDL_Texture* currentTexture = nullptr;

    if (type == ProjectileType::PlayerBasic) {
        currentTexture = playerTexture;
    } else if (type == ProjectileType::EnemyBasic) {
        currentTexture = enemyTexture;
    }

    if (currentTexture != nullptr) {
        SDL_RenderTexture(renderer, currentTexture, nullptr, &r);
        return;
    }

    if (type == ProjectileType::PlayerBasic) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
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

void Projectile::loadSharedTextures(SDL_Renderer* renderer) {
    if (playerTexture == nullptr) {
        SDL_Surface* surface = IMG_Load("assets/playerlaser.png");
        if (!surface) {
            SDL_Log("IMG_Load failed for player laser: %s", SDL_GetError());
        } else {
            playerTexture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_DestroySurface(surface);

            if (!playerTexture) {
                SDL_Log("SDL_CreateTextureFromSurface failed for player laser: %s", SDL_GetError());
            }
        }
    }

    if (enemyTexture == nullptr) {
        SDL_Surface* surface = IMG_Load("assets/enemylaser.png");
        if (!surface) {
            SDL_Log("IMG_Load failed for enemy laser: %s", SDL_GetError());
        } else {
            enemyTexture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_DestroySurface(surface);

            if (!enemyTexture) {
                SDL_Log("SDL_CreateTextureFromSurface failed for enemy laser: %s", SDL_GetError());
            }
        }
    }
}

void Projectile::unloadSharedTextures() {
    if (playerTexture != nullptr) {
        SDL_DestroyTexture(playerTexture);
        playerTexture = nullptr;
    }

    if (enemyTexture != nullptr) {
        SDL_DestroyTexture(enemyTexture);
        enemyTexture = nullptr;
    }
}

