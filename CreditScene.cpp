#include "CreditScene.hpp"
#include "Engine.hpp"
#include "TitleScene.hpp"
#include <SDL3/SDL_keyboard.h>

// Initialize credits-specific state/resources here.
void CreditScene::enter() {}
// Read keys/buttons that belong to the credits screen.
void CreditScene::handleInput() {
    const bool* keys = Engine::keyState;
    if (keys[SDL_SCANCODE_R]) {
        static TitleScene titleScene;
        Engine::instance().setScene(&titleScene);
    }
}
// Update credits screen animation/state here.
void CreditScene::update(float) {}
// Draw credits screen contents here.
void CreditScene::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDebugText(renderer, 320.0f, 260.0f, "GAME OVER");
    SDL_RenderDebugText(renderer, 220.0f, 300.0f, "PRESS R TO RETURN TO TITLE");
}
// Release credits-specific state/resources here.
void CreditScene::exit() {}
