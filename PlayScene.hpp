#ifndef     __PLAY_SCENE__
#define     __PLAY_SCENE__

#include "Scene.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "Enemy.hpp"
#include <vector>


class PlayScene : public Scene {
    public:
        ~PlayScene() override = default;

        // Called when gameplay starts.
        void enter() override;
        // Handles gameplay input.
        void handleInput() override;
        // Updates gameplay state.
        void update(float dt) override;
        // Renders gameplay scene.
        void render(SDL_Renderer* renderer) override;
        // Called when leaving gameplay.
        void exit() override;

    private:
        std::vector<GameObject*> objects;
        std::vector<Projectile*> projectiles;
        std::vector<Enemy*> enemies;
        Player player;
        float shootCooldown = 0.12f;
        float shootTimer = 0.0f;
        float enemySpawnCooldown = 0.8f;
        float enemySpawnTimer = 0.0f;
        float enemyShootCooldown = 0.7f;
        float enemyShootTimer = 0.0f;
        int currentLevel = 1;
        float enemyProjectileBaseSpeed = 300.0f;
        float enemyProjectileSpeedPerLevel = 35.0f;
        void spawnEnemyProjectile(Enemy* e);
};





#endif
