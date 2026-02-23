#include "Player.hpp"
#include "Engine.hpp"

Player::Player()
{
    // auto* spriteComponent = addComponent<SpriteComponent>();
    // spriteComponent->loadSprite(Engine::instance().getRenderer(), "sprite.png");
    // rect = spriteComponent->getRect();
}

void Player::update(float dt)
{
    const bool *keys = Engine::keyState;

    if (keys[SDL_SCANCODE_A]) moveLeft(dt);
    if (keys[SDL_SCANCODE_D]) moveRight(dt);
    if (keys[SDL_SCANCODE_W]) moveUp(dt);
    if (keys[SDL_SCANCODE_S]) moveDown(dt);
};

void Player::render(SDL_Renderer* renderer) {
    const SDL_FRect& r = getRect();
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &r);
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