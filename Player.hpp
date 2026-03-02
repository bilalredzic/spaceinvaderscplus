#ifndef     __PLAYER_HPP__
#define     __PLAYER_HPP__ 

#include "GameObject.hpp"
#include <SDL3/SDL.h>

class Player : public GameObject {
    public:
        ~Player() override;
        Player();

        void update(float dt) override;
        void render(SDL_Renderer* renderer) override;
        
        void moveLeft(float dt);
        void moveRight(float dt);
        void moveUp(float dt);
        void moveDown(float dt);
        int getHP();
        void loseLife();
        void onHit();
        void reset();
    private:
        SDL_Texture* texture = nullptr;
        float speed = 450.0f;
        int lives = 3;
        float hitFlashTimer = 0.0f;
        float hitFlashDuration = 0.15f;

};







#endif