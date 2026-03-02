#ifndef     __GAME_OBJECT_HPP__
#define     __GAME_OBJECT_HPP__

#include <SDL3/SDL.h>

// Shared base type for anything that updates, renders, and occupies a rectangle in the game.
class GameObject {
    public:
        virtual ~GameObject() = default;

        // Every concrete game object must define its own update and render behavior.
        virtual void update(float dt) = 0;
        virtual void render(SDL_Renderer* renderer) = 0;

        // Rectangle helpers used for rendering, positioning, and collision checks.
        const SDL_FRect& getRect() const;
        void setPosition(float x, float y);
        void setSize(float w, float h);

        // Active flag lets scenes skip or delete objects without losing their pointer immediately.
        bool isActive() const;
        void setActive(bool active);
    private:
        // Basic transform and lifetime state shared by every gameplay object.
        SDL_FRect rect {0.f, 0.f, 0.f, 0.f};
        bool active = true;

};




#endif
