#include "Player.hpp"

void Player::update(float dt){
    
};

void Player::render(SDL_Renderer* renderer) {
    const SDL_FRect& r = getRect();
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &r);
};

void Player::moveLeft(float dt) {
    const SDL_FRect& r = getRect();
    setPosition(r.x - (speed * dt), r.y);

};

void Player::moveRight(float dt) {
    const SDL_FRect& r = getRect();
    setPosition(r.x + (speed * dt), r.y);
}