#include "GameObject.hpp"

// Expose the object's rectangle so scenes and derived classes can read it.
const SDL_FRect& GameObject::getRect() const { 
    return rect; 
}

void GameObject::setPosition(float x, float y) {
    // Update only the rectangle position while preserving its current size.
    rect.x = x;
    rect.y = y;
};

void GameObject::setSize(float w, float h) {
    // Update only the rectangle size while preserving its current position.
    rect.w = w;
    rect.h = h;
};

bool GameObject::isActive() const {
    // Active objects participate in update/render; inactive ones are ready for cleanup.
    return active;
};

void GameObject::setActive(bool active) {
    // Toggle whether this object should still be treated as alive in the scene.
    this->active = active;
};
