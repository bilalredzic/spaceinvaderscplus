#include "PlayScene.hpp"
#include "Engine.hpp"
#include "CreditScene.hpp"

#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>
#include "AudioManager.hpp"


#include <random>

static bool overlaps(const SDL_FRect& a, const SDL_FRect& b) {
    if (a.x + a.w <= b.x) return false;
    if (b.x + b.w <= a.x) return false;
    if (a.y + a.h <= b.y) return false;
    if (b.y + b.h <= a.y) return false;
    return true;
}

// Initialize gameplay state/resources here.
void PlayScene::enter() {
    exit();

    Projectile::loadSharedTextures(Engine::instance().getRenderer());
    Enemy::loadSharedTexture(Engine::instance().getRenderer());

    isGameOver = false;
    shootTimer = shootCooldown;
    enemySpawnTimer = 0.0f;
    enemySpawnCooldown = baseEnemySpawnCooldown;
    currentLevel = 1;
    killsThisLevel = 0;
    totalKills = 0;
    killsRequired = baseKillsRequired;

    player.reset();
    player.setPosition(100.0f, 500.0f);
    player.setSize(50.0f, 40.0f);
    this->objects.push_back(&player);
    if (backgroundTexture == nullptr) {
    SDL_Surface* surface = IMG_Load("assets/background.png");
    if (!surface) {
        SDL_Log("IMG_Load failed for background.png: %s", SDL_GetError());
    } else {
        backgroundTexture = SDL_CreateTextureFromSurface(Engine::instance().getRenderer(), surface);
        SDL_DestroySurface(surface);

        if (!backgroundTexture) {
            SDL_Log("SDL_CreateTextureFromSurface failed for background.png: %s", SDL_GetError());
        }
    }
}
};
// Read keys/buttons that belong to gameplay.
void PlayScene::handleInput() {
    const float dt = targetFrameTime/1000.0f; // ms-> seconds
    const bool* keys = Engine::keyState;

    if (keys[SDL_SCANCODE_SPACE] && shootTimer <=0.0f) {
        Projectile* p = new Projectile();
        p->setDirection(-1.0f);
        p->setType(ProjectileType::PlayerBasic);
        const SDL_FRect& pr = player.getRect();
        p->setSize(6.0f, 14.0f);
        p->setPosition(pr.x + (pr.w*0.5f) - 3.0f, pr.y - 14.0f);

        projectiles.push_back(p);
        objects.push_back(p);
        AudioManager::instance().playShoot();

            
        shootTimer = shootCooldown;
        }
    

    // for (size_t i = 0; i< Engine::keyEvents.size(); i++) {
    //     if (Engine::keyEvents[i].key.key == SDLK_SPACE) {
    //         Projectile* p = new Projectile();
            
    //         const SDL_FRect& pr = player.getRect();
    //         p->setSize(6.0f, 14.0f);
    //         p->setPosition(pr.x + (pr.w*0.5f) - 3.0f, pr.y - 14.0f);

    //         projectiles.push_back(p);
    //         objects.push_back(p);
    //     }
    // }
};
// Update gameplay logic here.
void PlayScene::update(float dt) {
    if (isGameOver) {
        return;
    }
    for (size_t i = 0; i < objects.size(); i++) {
        if (this->objects[i]->isActive())
            this->objects[i]->update(dt);
        } 
    
    for (size_t i = 0; i < projectiles.size(); i++) {
        if (!projectiles[i]->isActive()) continue;
        if (projectiles[i]->getType() != ProjectileType::PlayerBasic) continue;

        const SDL_FRect& pr = projectiles[i]->getRect();

        for (size_t j = 0; j < enemies.size(); j++) {
            if (!enemies[j]->isActive()) continue;

            const SDL_FRect& er = enemies[j]->getRect();

            if (overlaps(pr, er)) {
                projectiles[i]->setActive(false);
                enemies[j]->setActive(false);
                AudioManager::instance().playEnemyHit();
                killsThisLevel++;
                totalKills++;
                if (killsThisLevel >= killsRequired) {
                    currentLevel++;
                    killsThisLevel = 0;
                    killsRequired += 10;
                    AudioManager::instance().playLevelUp();

                    enemySpawnCooldown -= 0.05f;
                    if (enemySpawnCooldown < 0.25f) enemySpawnCooldown = 0.25f;
                }
                break;
            }
        }
    }

    const SDL_FRect& playerRect = player.getRect();
    for (size_t i = 0; i<projectiles.size(); i++) {
        if (!projectiles[i]->isActive()) continue;
        if (projectiles[i]->getType() != ProjectileType::EnemyBasic) continue;

        const SDL_FRect& pr = projectiles[i]->getRect();
        if (overlaps(pr, playerRect)) {
            projectiles[i]->setActive(false);
            player.onHit();
            AudioManager::instance().playPlayerHit();

            if (player.getHP() <= 0) {
                isGameOver = true;
                SDL_Log("Game Over");
                AudioManager::instance().playGameOver();
                AudioManager::instance().stopMusic();
                static CreditScene creditScene;
                Engine::instance().setScene(&creditScene);
                return;
            }
        }

    }
    for (size_t i = 0; i < enemies.size(); i++) {
        if (!enemies[i]->isActive()) continue;

        const SDL_FRect& er = enemies[i]->getRect();

        if (overlaps(er, playerRect)) {
            enemies[i]->setActive(false);
            player.onHit();
            AudioManager::instance().playPlayerHit();

            if (player.getHP() <= 0) {
                isGameOver = true;
                SDL_Log("Game Over");
                AudioManager::instance().playGameOver();
                AudioManager::instance().stopMusic();
                static CreditScene creditScene;
                Engine::instance().setScene(&creditScene);
                return;
            }
        }
    }
    
    //no i++ in loop because we only increment when we don't erase
    for (size_t i = 0; i<projectiles.size();) {
        if (!projectiles[i]->isActive()){
            GameObject* dead = projectiles[i];

            for (size_t j = 0; j<objects.size(); j++) {
                if (objects[j] == dead) {
                    objects.erase(objects.begin() + j);
                    break;
                }
            }
            delete projectiles[i];
            projectiles.erase(projectiles.begin() + i);
        } else {
            i++;
        }
    }

    for (size_t i = 0; i < enemies.size();) {
    if (!enemies[i]->isActive()) {
        GameObject* dead = enemies[i];

        for (size_t j = 0; j < objects.size(); j++) {
            if (objects[j] == dead) {
                objects.erase(objects.begin() + j);
                break;
            }
        }

        delete enemies[i];
        enemies.erase(enemies.begin() + i);
    } else {
        i++;
    }
    }

    shootTimer -= dt;
    if (shootTimer < 0.0f) shootTimer = 0.0f;
    enemySpawnTimer -=dt;
    if (enemySpawnTimer <= 0.0f) {
        static std::mt19937 rng(std::random_device{}());
        float enemyW = 40.0f;
        float enemyH = 20.0f;
        float spawnY = -enemyH;

        std::uniform_real_distribution<float> xDist(0.0f, 800.0f - enemyW);
        float spawnX = xDist(rng);

        Enemy* e = new Enemy();
        float enemyMoveSpeed = 220.0f + 20.0f*(currentLevel - 1);
        e->setSpeed(enemyMoveSpeed);

        e->setSize(enemyW, enemyH);
        e->setPosition(spawnX, spawnY);

        e->setShootCooldown(1.2f);
        std::uniform_real_distribution<float> initialShot(0.0f, 2.5f);
        e->setInitialShootTimer(initialShot(rng));

        enemies.push_back(e);
        objects.push_back(e);
        
        enemySpawnTimer = enemySpawnCooldown;
    }

    
    for (size_t i = 0; i<enemies.size();i++) {
        Enemy* e = enemies[i];
        if (!e->isActive()) {
            continue;
        }
        if (e->canShoot(dt)) {
            spawnEnemyProjectile(e);
        }
    }
};

// Draw gameplay objects here.
void PlayScene::render(SDL_Renderer* renderer) {
    if (backgroundTexture != nullptr) {
        SDL_FRect bgRect{0.0f, 0.0f, 800.0f, 600.0f};
        SDL_RenderTexture(renderer, backgroundTexture, nullptr, &bgRect);
    }
    for (size_t i = 0; i < this->objects.size(); i++) {
        if (this->objects[i]->isActive()) {
            this->objects[i]->render(renderer);
        }
    }
    std::string hud = "LEVEL " + std::to_string(currentLevel) + "   KILLS " + std::to_string(totalKills);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDebugText(renderer, 10.0f, 10.0f, hud.c_str());

    std::string livesText = "LIVES";
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDebugText(renderer, 680.0f, 15.0f, livesText.c_str());

    // one red box per life (top-right placeholder for hearts)
    int hp = player.getHP();
    for (int i = 0; i < hp; i++) {
        SDL_FRect lifeBox{800.0f - 10.0f - (i + 1) * 22.0f, 10.0f, 18.0f, 18.0f};
        SDL_SetRenderDrawColor(renderer, 255, 60, 60, 255);
        SDL_RenderFillRect(renderer, &lifeBox);
}
};

// Release gameplay state/resources here.
void PlayScene::exit() {
    for (size_t i = 0; i < projectiles.size(); i++) {
        delete projectiles[i];
    }
    for (size_t i = 0; i<enemies.size(); i++) {
        delete enemies[i];
    }
    projectiles.clear();
    objects.clear();
    enemies.clear();
};

void PlayScene::spawnEnemyProjectile(Enemy* e) {
    Projectile* p = new Projectile();
    
    const float levelSpeed = enemyProjectileBaseSpeed + enemyProjectileSpeedPerLevel * (currentLevel - 1);

    p->setDirection(1.0f);
    p->setType(ProjectileType::EnemyBasic);
    p->setSpeed(levelSpeed);

    const SDL_FRect& er = e->getRect();
    p->setSize(6.0f, 14.0f);
    p->setPosition(er.x + (er.w * 0.5f) - 3.0f, er.y + er.h);

    projectiles.push_back(p);
    objects.push_back(p);

    AudioManager::instance().playEnemyShoot();
}
