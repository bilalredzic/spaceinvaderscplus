#ifndef     __PLAYER_HPP__
#define     __PLAYER_HPP__ 

#include "GameObject.hpp"
#include <SDL3/SDL.h>

class Player : public GameObject {
    public:
        ~Player() override = default;
        Player();

        void update(float dt) override;
        void render(SDL_Renderer* renderer) override;
        
        void moveLeft(float dt);
        void moveRight(float dt);
        void moveUp(float dt);
        void moveDown(float dt);
        int getHP();
        void loseLife();
    private:
        SDL_FRect* rect;
        float speed = 500.0f;
        int lives = 3;
};







#endif