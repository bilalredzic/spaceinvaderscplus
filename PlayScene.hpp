#ifndef     __PLAY_SCENE__
#define     __PLAY_SCENE__

#include "Scene.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
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
        Player player;
        float shootCooldown = 0.12f;
        float shootTimer = 0.0f;
};





#endif
