#ifndef     __PLAY_SCENE__
#define     __PLAY_SCENE__

#include "Scene.hpp"

class PlayScene : public Scene {
    public:
        ~PlayScene() override = default;

        void enter() override;
        void handleInput() override;
        void update(float dt) override;
        void render(SDL_Renderer* renderer) override;
        void exit() override;

    private:

};





#endif