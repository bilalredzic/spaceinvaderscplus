#include "TitleScene.hpp"
#include "Engine.hpp"
#include "PlayScene.hpp"
#include <SDL3/SDL_keyboard.h>
#include "AudioManager.hpp"

// Initialize title-specific state/resources here.
void TitleScene::enter() {
    AudioManager::instance().playMusic();
}
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
    std::string title = "SPACE INVADERS";
    std::string prompt = "PRESS SPACE TO START";

    float scale = 2.0f;

    float titleWidth = title.size() * 8.0f * scale;
    float promptWidth = prompt.size() * 8.0f * scale;

    float titleX = (800.0f - titleWidth) * 0.5f;
    float promptX = (800.0f - promptWidth) * 0.5f;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_SetRenderScale(renderer, scale, scale);
    SDL_RenderDebugText(renderer, titleX / scale, 180.0f / scale, title.c_str());
    SDL_RenderDebugText(renderer, promptX / scale, 280.0f / scale, prompt.c_str());
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}
// Release title-specific state/resources here.
void TitleScene::exit() {}
