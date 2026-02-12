#ifndef     __CREDIT_SCENE__
#define     __CREDIT_SCENE__

#include "Scene.hpp"

class CreditScene : public Scene {
    public:
        ~CreditScene() override = default;

        void enter() override;
        void handleInput() override;
        void update(float dt) override;
        void render(SDL_Renderer* renderer) override;
        void exit() override;

    private:
    
};





#endif