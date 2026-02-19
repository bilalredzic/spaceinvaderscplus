#include "PlayScene.hpp"

// Initialize gameplay state/resources here.
void PlayScene::enter() {
    this->objects.push_back(&player);
}
// Read keys/buttons that belong to gameplay.
void PlayScene::handleInput() {}
// Update gameplay logic here.
void PlayScene::update(float dt) {
    int length = this->objects.size();
    for (int i = 0; i < length; i++) {
        if (this->objects[i]->isActive())
            this->objects[i]->update(dt);
    };
}
// Draw gameplay objects here.
void PlayScene::render(SDL_Renderer* renderer) {
    for (size_t i = 0; i < this->objects.size(); i++) {
        if (this->objects[i]->isActive()) {
            this->objects[i]->render(renderer);
        }
    }
}

// Release gameplay state/resources here.
void PlayScene::exit() {
    this->objects.clear();
}
