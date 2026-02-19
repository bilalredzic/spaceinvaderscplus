#ifndef     __GAME_OBJECT_HPP__
#define     __GAME_OBJECT_HPP__

#include <SDL3/SDL.h>

class GameObject {
    public:
        virtual ~GameObject() = default;

        virtual void update(float dt) = 0;
        virtual void render(SDL_Renderer* renderer) = 0;

        const SDL_FRect& getRect() const;
        void setPosition(float x, float y);
        void setSize(float w, float h);

        bool isActive() const;
        void setActive(bool active);
    private:
        SDL_FRect rect {0.f, 0.f, 0.f, 0.f};
        bool active = true;

};




#endif