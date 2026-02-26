#ifndef     __PROJECTILE_HPP__
#define     __PROJECTILE_HPP__

#include "GameObject.hpp"
#include <SDL3/SDL.h>

enum class ProjectileType {
    PlayerBasic,
    EnemyBasic
};

class Projectile : public GameObject {
    public:
        ~Projectile() override = default;

        void update(float dt) override;
        void render(SDL_Renderer* renderer) override;
        void setDirection(float dir);
        void setSpeed(float s);
        void setType(ProjectileType t);
        ProjectileType getType() const;
        

    private:
        float speed = 500.0f;
        float dirY = -1.0f;
        ProjectileType type = ProjectileType::PlayerBasic;

};






#endif