#include "GameObject.hpp"

const SDL_FRect& GameObject::getRect() const { 
    return rect; 
}

void GameObject::setPosition(float x, float y) {
    rect.x = x;
    rect.y = y;
};

void GameObject::setSize(float w, float h) {
    rect.w = w;
    rect.h = h;
};

bool GameObject::isActive() const {
    return active;
};

void GameObject::setActive(bool active) {
    this->active = active;
};
