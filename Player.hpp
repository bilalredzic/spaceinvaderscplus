#ifndef     __PLAYER_HPP__
#define     __PLAYER_HPP__ 

#include "GameObject.hpp"
#include <SDL3/SDL.h>


class Player : public GameObject {
    public:
        ~Player() override = default;

        void update(float dt) override;
        void render(SDL_Renderer* renderer) override;



};







#endif