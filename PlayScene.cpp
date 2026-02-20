#include "PlayScene.hpp"
#include "Engine.hpp"
#include <SDL3/SDL_keyboard.h>


// Initialize gameplay state/resources here.
void PlayScene::enter() {
    player.setPosition(100.0f, 500.0f);
    player.setSize(60.0f, 20.0f);
    this->objects.push_back(&player);
};
// Read keys/buttons that belong to gameplay.
void PlayScene::handleInput() {
    const float dt = targetFrameTime/1000.0f; // ms-> seconds
    const bool* keys = SDL_GetKeyboardState(nullptr);

    if (keys[SDL_SCANCODE_A]) player.moveLeft(dt);
    if (keys[SDL_SCANCODE_D]) player.moveRight(dt);
    if (keys[SDL_SCANCODE_W]) player.moveUp(dt);
    if (keys[SDL_SCANCODE_S]) player.moveDown(dt);

    if (keys[SDL_SCANCODE_SPACE] && shootTimer <=0.0f) {
        Projectile* p = new Projectile();
            
            const SDL_FRect& pr = player.getRect();
            p->setSize(6.0f, 14.0f);
            p->setPosition(pr.x + (pr.w*0.5f) - 3.0f, pr.y - 14.0f);

            projectiles.push_back(p);
            objects.push_back(p);
            
            shootTimer = shootCooldown;
        }
    

    // for (size_t i = 0; i< Engine::keyEvents.size(); i++) {
    //     if (Engine::keyEvents[i].key.key == SDLK_SPACE) {
    //         Projectile* p = new Projectile();
            
    //         const SDL_FRect& pr = player.getRect();
    //         p->setSize(6.0f, 14.0f);
    //         p->setPosition(pr.x + (pr.w*0.5f) - 3.0f, pr.y - 14.0f);

    //         projectiles.push_back(p);
    //         objects.push_back(p);
    //     }
    // }
};
// Update gameplay logic here.
void PlayScene::update(float dt) {
    size_t length = this->objects.size();
    for (size_t i = 0; i < length; i++) {
        if (this->objects[i]->isActive())
            this->objects[i]->update(dt);
        } 
    //no i++ in loop because we only increment when we don't erase
    for (size_t i = 0; i<projectiles.size();) {
        if (!projectiles[i]->isActive()){
            GameObject* dead = projectiles[i];

            for (size_t j = 0; j<objects.size(); j++) {
                if (objects[j] == dead) {
                    objects.erase(objects.begin() + j);
                    break;
                }
            }
            delete projectiles[i];
            projectiles.erase(projectiles.begin() + i);
        } else {
            i++;
        }
    }

    shootTimer -= dt;
    if (shootTimer < 0.0f) shootTimer = 0.0f;
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
    for (size_t i = 0; i < projectiles.size(); i++) {
        delete projectiles[i];
    }
    projectiles.clear();
    objects.clear();

};
