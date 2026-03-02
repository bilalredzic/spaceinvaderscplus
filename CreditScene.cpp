#include "CreditScene.hpp"
#include "Engine.hpp"
#include "TitleScene.hpp"
#include <SDL3/SDL_keyboard.h>

// Initialize credits-specific state/resources here.
void CreditScene::enter() {}
// Read keys/buttons that belong to the credits screen.
void CreditScene::handleInput() {
    const bool* keys = Engine::keyState;
    // Return to the title screen when the player presses R.
    if (keys[SDL_SCANCODE_R]) {
        static TitleScene titleScene;
        Engine::instance().setScene(&titleScene);
    }
}
// Update credits screen animation/state here.
void CreditScene::update(float) {}
// Draw credits screen contents here.
void CreditScene::render(SDL_Renderer* renderer) {
    // Center the game-over text and restart prompt using debug-text width estimates.
    std::string gameOver = "GAME OVER";
    std::string prompt = "PRESS R TO RETURN TO TITLE";

    float scale = 2.0f;

    float gameOverWidth = gameOver.size() * 8.0f * scale;
    float promptWidth = prompt.size() * 8.0f * scale;

    float gameOverX = (800.0f - gameOverWidth) * 0.5f;
    float promptX = (800.0f - promptWidth) * 0.5f;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_SetRenderScale(renderer, scale, scale);
    SDL_RenderDebugText(renderer, gameOverX / scale, 180.0f / scale, gameOver.c_str());
    SDL_RenderDebugText(renderer, promptX / scale, 280.0f / scale, prompt.c_str());
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}
// Release credits-specific state/resources here.
void CreditScene::exit() {}
