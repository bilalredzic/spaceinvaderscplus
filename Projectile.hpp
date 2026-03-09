#ifndef     __PROJECTILE_HPP__
#define     __PROJECTILE_HPP__

#include "GameObject.hpp"
#include <SDL3/SDL.h>

// Distinguishes player bullets from enemy bullets for art and collision behavior.
enum class ProjectileType {
    PlayerBasic,
    EnemyBasic
};

// Lightweight projectile object with shared textures for each projectile type.
class Projectile : public GameObject {
    public:
        ~Projectile() override = default;

        void update(float dt) override;
        void render(SDL_Renderer* renderer) override;
        void setDirection(float dir);
        void setSpeed(float s);
        void setType(ProjectileType t);
        ProjectileType getType() const;
        static void loadSharedTextures(SDL_Renderer* renderer);
        static void unloadSharedTextures();

        static constexpr float baseSpeed = 500.0f;
        static constexpr float basePlayerWidth = 6.0f;
        static constexpr float basePlayerHeight = 14.0f;
        static constexpr float baseEnemyWidth = 6.0f;
        static constexpr float baseEnemyHeight = 14.0f;

        

    private:
        // Per-projectile movement/type state plus shared textures for each bullet style.
        float speed = baseSpeed;
        float dirY = -1.0f;
        ProjectileType type = ProjectileType::PlayerBasic;
        static SDL_Texture* playerTexture;
        static SDL_Texture* enemyTexture;


};






#endif
