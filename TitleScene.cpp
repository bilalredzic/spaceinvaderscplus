#include "TitleScene.hpp"
#include "Engine.hpp"
#include "PlayScene.hpp"
#include <SDL3/SDL_keyboard.h>

// Initialize title-specific state/resources here.
void TitleScene::enter() {}
// Read keys/buttons that belong to the title screen.
void TitleScene::handleInput() {
    const bool* keys = Engine::keyState;
    if (keys[SDL_SCANCODE_SPACE]) {
        static PlayScene playScene;
        Engine::instance().setScene(&playScene);
    }
}
// Update title screen animation/state here.
void TitleScene::update(float) {}
// Draw title screen contents here.
void TitleScene::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDebugText(renderer, 260.0f, 260.0f, "SPACE INVADERS");
    SDL_RenderDebugText(renderer, 220.0f, 300.0f, "PRESS SPACE TO START");
}
// Release title-specific state/resources here.
void TitleScene::exit() {}
