#include "PlayScene.hpp"
#include "Engine.hpp"

// Initialize gameplay state/resources here.
void PlayScene::enter() {
    player.setPosition(100.0f, 500.0f);
    player.setSize(60.0f, 20.0f);
    this->objects.push_back(&player);
};
// Read keys/buttons that belong to gameplay.
void PlayScene::handleInput() {
    const float dt = targetFrameTime/1000.0f; // ms-> seconds
    size_t length = Engine::keyEvents.size();
    for (size_t i = 0; i< length; i++) {
        if (Engine::keyEvents[i].key.key == SDLK_A) {
            player.moveLeft(dt);
        } else if (Engine::keyEvents[i].key.key == SDLK_D) {
            player.moveRight(dt);
        }
    }
};
// Update gameplay logic here.
void PlayScene::update(float dt) {
    size_t length = this->objects.size();
    for (int i = 0; i < length; i++) {
        if (this->objects[i]->isActive())
            this->objects[i]->update(dt);
    };
};
// Draw gameplay objects here.
void PlayScene::render(SDL_Renderer* renderer) {
    for (size_t i = 0; i < this->objects.size(); i++) {
        if (this->objects[i]->isActive()) {
            this->objects[i]->render(renderer);
        }
    }
};

// Release gameplay state/resources here.
void PlayScene::exit() {
    this->objects.clear();
};
