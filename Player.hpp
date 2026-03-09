#ifndef     __PLAYER_HPP__
#define     __PLAYER_HPP__ 

#include "GameObject.hpp"
#include <SDL3/SDL.h>

// Player-controlled ship with movement, lives, and sprite rendering state.
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

        static constexpr float baseWidth = 50.0f;
        static constexpr float baseHeight = 40.0f;
        static constexpr float baseSpeed = 450.0f;
    private:
        // Sprite, movement, and life-flash state for the player ship.
        SDL_Texture* texture = nullptr;
        float speed = baseSpeed;
        int baseLives = 3;
        int lives = baseLives;
        float hitFlashTimer = 0.0f;
        float hitFlashDuration = 0.15f;

};







#endif
