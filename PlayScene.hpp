#ifndef     __PLAY_SCENE__
#define     __PLAY_SCENE__

#include "Scene.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "Enemy.hpp"
#include <vector>
#include <string>



// Main gameplay scene that owns the player, active enemies, projectiles, and HUD state.
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
        // Active objects are split by role so update, collision, and cleanup stay manageable.
        std::vector<GameObject*> objects;
        std::vector<Projectile*> projectiles;
        std::vector<Enemy*> enemies;
        Player player;

        // Base/default values used to reset gameplay cleanly for a new run.
        float shootCooldown = 0.20f;
        float baseEnemySpawnCooldown = 0.8f;
        int baseKillsRequired = 15;

        float playerSpawnX = 100.0f;
        float playerSpawnY = 500.0f;
        float enemySpawnY = -20.0f;

        // Runtime timers and progression state that change during gameplay.
        float shootTimer = 0.0f;
        float enemySpawnCooldown = 0.8f;
        float enemySpawnTimer = 0.0f;
        int currentLevel = 1;
        int killsThisLevel = 0;
        int killsRequired = 15;
        float enemyProjectileBaseSpeed = 300.0f;
        float enemyProjectileSpeedPerLevel = 35.0f;
        float baseEnemyMoveSpeed = 220.0f;
        float enemyMoveSpeedPerLevel = 20.0f;

        // Helper for spawning one enemy projectile from a specific enemy ship.
        void spawnEnemyProjectile(Enemy* e);

        // Run-state flags and counters used for HUD display and scene transitions.
        bool isGameOver = false;
        int totalKills = 0;

        // Background texture rendered behind all gameplay objects.
        SDL_Texture* backgroundTexture = nullptr;


};





#endif
