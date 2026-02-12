#ifndef     __TITLE_SCENE__
#define     __TITLE_SCENE__

#include "Scene.hpp"

// Title screen state.
class TitleScene : public Scene {
    public:
        ~TitleScene() override = default;

        // Called when entering title screen.
        void enter() override;
        // Handles title-screen controls.
        void handleInput() override;
        // Updates title-screen state.
        void update(float dt) override;
        // Renders title-screen visuals.
        void render(SDL_Renderer* renderer) override;
        // Called before leaving title screen.
        void exit() override;

    private:

};



#endif
