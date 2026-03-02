#include "Player.hpp"
#include "Engine.hpp"

#include <SDL3_image/SDL_image.h>

Player::Player()
{
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

    if (keys[SDL_SCANCODE_A]) moveLeft(dt);
    if (keys[SDL_SCANCODE_D]) moveRight(dt);
    if (keys[SDL_SCANCODE_W]) moveUp(dt);
    if (keys[SDL_SCANCODE_S]) moveDown(dt);

    if (hitFlashTimer > 0.0f) hitFlashTimer -= dt;
    if (hitFlashTimer < 0.0f) hitFlashTimer = 0.0f;

};

void Player::render(SDL_Renderer* renderer) {
    const SDL_FRect& r = getRect();

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

    if (hitFlashTimer > 0.0f) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    }
    
    SDL_RenderTexture(renderer, texture, nullptr, &r);

};

void Player::moveLeft(float dt) {
    const SDL_FRect& r = getRect();
    float newX = r.x - speed*dt;
    float maxX = 800.0f - r.w;
    if (newX < 0.0f) newX = 0.0f;
    if (newX > maxX) newX = maxX;
    setPosition(newX, r.y);
};

void Player::moveRight(float dt) {
    const SDL_FRect& r = getRect();
    float newX = r.x + speed * dt;
    float maxX = 800.0f - r.w;

    if (newX < 0.0f) newX = 0.0f;
    if (newX > maxX) newX = maxX;

    setPosition(newX, r.y);
}

void Player::moveUp(float dt) {
    const SDL_FRect& r = getRect();
    float newY = r.y - speed * dt;
    float maxY = 600.0f - r.h;

    if (newY < 0.0f) newY = 0.0f;
    if (newY > maxY) newY = maxY;

    setPosition(r.x, newY);
}

void Player::moveDown(float dt) {
    const SDL_FRect& r = getRect();
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
    loseLife();
    hitFlashTimer = hitFlashDuration;
}

Player::~Player() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void Player::reset() {
    lives = 3;
    hitFlashTimer = 0.0f;
}