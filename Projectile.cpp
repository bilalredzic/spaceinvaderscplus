#include "Projectile.hpp"
#include <SDL3_image/SDL_image.h>
#include "Engine.hpp"

// Shared projectile textures are loaded once and reused by every projectile instance.
SDL_Texture* Projectile::playerTexture = nullptr;
SDL_Texture* Projectile::enemyTexture = nullptr;


void Projectile::update(float dt) {
    const SDL_FRect& r = getRect();
    // Move vertically according to projectile direction and speed.
    float newY = r.y + dirY * speed * dt;
    setPosition(r.x, newY);
    // Deactivate projectiles once they leave the screen bounds.
    if (newY + r.h < 0.0f || newY > 600.0f) setActive(false);
};

void Projectile::render(SDL_Renderer* renderer) {
    const SDL_FRect& r = getRect();

    // Choose the shared projectile texture that matches this projectile's type.
    SDL_Texture* currentTexture = nullptr;

    if (type == ProjectileType::PlayerBasic) {
        currentTexture = playerTexture;
    } else if (type == ProjectileType::EnemyBasic) {
        currentTexture = enemyTexture;
    }

    // Render the shared sprite if it is available.
    if (currentTexture != nullptr) {
        SDL_RenderTexture(renderer, currentTexture, nullptr, &r);
        return;
    }

    // Fall back to a simple colored rectangle if no texture was loaded.
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
    // Load the player projectile sprite once and keep it for future bullets.
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

    // Load the enemy projectile sprite once and keep it for future bullets.
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
    // Release both shared projectile textures during engine shutdown.
    if (playerTexture != nullptr) {
        SDL_DestroyTexture(playerTexture);
        playerTexture = nullptr;
    }

    if (enemyTexture != nullptr) {
        SDL_DestroyTexture(enemyTexture);
        enemyTexture = nullptr;
    }
}
