#ifndef     __TITLE_SCENE__
#define     __TITLE_SCENE__

#include "Scene.hpp"

// TitleScene.hpp
class TitleScene : public Scene {
    public:
        ~TitleScene() override = default;

        void enter() override;
        void handleInput() override;
        void update(float dt) override;
        void render(SDL_Renderer* renderer) override;
        void exit() override;

    private:

};



#endif