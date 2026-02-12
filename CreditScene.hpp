#ifndef     __CREDIT_SCENE__
#define     __CREDIT_SCENE__

#include "Scene.hpp"

class CreditScene : public Scene {
    public:
        ~CreditScene() override = default;

        // Called when credits screen is shown.
        void enter() override;
        // Handles credits-screen input.
        void handleInput() override;
        // Updates credits-screen state.
        void update(float dt) override;
        // Renders credits-screen visuals.
        void render(SDL_Renderer* renderer) override;
        // Called before leaving credits screen.
        void exit() override;

    private:
    
};





#endif
