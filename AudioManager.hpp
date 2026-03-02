#ifndef __AUDIO_MANAGER_HPP__
#define __AUDIO_MANAGER_HPP__

#include "miniaudio.h"

class AudioManager {
    public:
        static AudioManager& instance() {
            static AudioManager instance;
            return instance;
        }

        AudioManager(const AudioManager&) = delete;
        AudioManager& operator=(const AudioManager&) = delete;

        bool init();
        void shutdown();

        bool loadShootSound(const char* filepath);
        void playShoot();

        bool loadEnemyShootSound(const char* filepath);
        void playEnemyShoot();

        bool loadPlayerHitSound(const char* filepath);
        void playPlayerHit();

        bool loadEnemyHitSound(const char* filepath);
        void playEnemyHit();

        bool loadLevelUpSound(const char* filepath);
        void playLevelUp();

        bool loadGameOverSound(const char* filepath);
        void playGameOver();


    private:
        AudioManager() = default;
        ~AudioManager() = default;

        ma_engine engine;
        ma_sound shootSound;
        ma_sound enemyShootSound;
        bool enemyShootLoaded = false;

        bool initialized = false;
        bool shootLoaded = false;
};

#endif
