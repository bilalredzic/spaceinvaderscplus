#include "Player.hpp"
#include "Engine.hpp"

#include <SDL3_image/SDL_image.h>

Player::Player()
{
    // Load the player ship sprite once when the player object is constructed.
    SDL_Surface* surface = IMG_Load("assets/player.png");
    if (!surface) {
        SDL_Log("IMG_Load failed for player.png: %s", SDL_GetError());
        return;
    }

    texture = SDL_CreateTextureFromSurface(Engine::instance().getRenderer(), surface);
    SDL_DestroySurface(surface);

    if (!texture) {
        SDL_Log("SDL_CreateTextureFromSurface failed for player.png: %s", SDL_GetError());
        return;
    }

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}

void Player::update(float dt)
{
    const bool *keys = Engine::keyState;

    // Move continuously while the corresponding movement keys are held.
    if (keys[SDL_SCANCODE_A]) moveLeft(dt);
    if (keys[SDL_SCANCODE_D]) moveRight(dt);
    if (keys[SDL_SCANCODE_W]) moveUp(dt);
    if (keys[SDL_SCANCODE_S]) moveDown(dt);

    // Count down the hit-flash timer and clamp it at zero.
    if (hitFlashTimer > 0.0f) hitFlashTimer -= dt;
    if (hitFlashTimer < 0.0f) hitFlashTimer = 0.0f;

};

void Player::render(SDL_Renderer* renderer) {
    const SDL_FRect& r = getRect();

    // Prefer the loaded sprite texture and tint it red briefly after a hit.
    if (texture != nullptr) {
        if (hitFlashTimer > 0.0f) {
            SDL_SetTextureColorMod(texture, 255, 80, 80);
        } else {
            SDL_SetTextureColorMod(texture, 255, 255, 255);
        }
        SDL_SetTextureAlphaMod(texture, 255);

        SDL_RenderTexture(renderer, texture, nullptr, &r);
        return;
    }

    // Fall back to a simple colored shape if the sprite could not be loaded.
    if (hitFlashTimer > 0.0f) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    }
    
    SDL_RenderFillRect(renderer, &r);

};

void Player::moveLeft(float dt) {
    const SDL_FRect& r = getRect();
    // Move left and clamp the player inside the window bounds.
    float newX = r.x - speed*dt;
    float maxX = 800.0f - r.w;
    if (newX < 0.0f) newX = 0.0f;
    if (newX > maxX) newX = maxX;
    setPosition(newX, r.y);
};

void Player::moveRight(float dt) {
    const SDL_FRect& r = getRect();
    // Move right and clamp the player inside the window bounds.
    float newX = r.x + speed * dt;
    float maxX = 800.0f - r.w;

    if (newX < 0.0f) newX = 0.0f;
    if (newX > maxX) newX = maxX;

    setPosition(newX, r.y);
}

void Player::moveUp(float dt) {
    const SDL_FRect& r = getRect();
    // Move up and clamp the player inside the window bounds.
    float newY = r.y - speed * dt;
    float maxY = 600.0f - r.h;

    if (newY < 0.0f) newY = 0.0f;
    if (newY > maxY) newY = maxY;

    setPosition(r.x, newY);
}

void Player::moveDown(float dt) {
    const SDL_FRect& r = getRect();
    // Move down and clamp the player inside the window bounds.
    float newY = r.y + speed * dt;
    float maxY = 600.0f - r.h;

    if (newY < 0.0f) newY = 0.0f;
    if (newY > maxY) newY = maxY;

    setPosition(r.x, newY);
}

int Player::getHP()
{
    return lives;
}

void Player::loseLife()
{
    lives--;
}

void Player::onHit() {
    // Losing a life also starts the temporary red flash effect.
    loseLife();
    hitFlashTimer = hitFlashDuration;
}

Player::~Player() {
    // Release the player texture when the player object is destroyed.
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void Player::reset() {
    // Restore the player to a fresh state for a new run.
    lives = baseLives;
    hitFlashTimer = 0.0f;
}
