#ifndef __AUDIO_MANAGER_HPP__
#define __AUDIO_MANAGER_HPP__

#include "miniaudio.h"

// Centralized audio controller for loading and playing shared game sounds.
class AudioManager {
    public:
        // Access the single shared audio manager instance used by the whole game.
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

        bool loadMusic(const char* filepath);
        void playMusic();

        void stopMusic();


    private:
        AudioManager() = default;
        ~AudioManager() = default;

        // miniaudio engine plus one reusable sound object per effect/music track.
        ma_engine engine;
        ma_sound shootSound;
        ma_sound enemyShootSound;
        ma_sound playerHitSound;
        ma_sound enemyHitSound;
        ma_sound levelUpSound;
        ma_sound gameOverSound;
        ma_sound music;
        bool musicLoaded = false;
        bool enemyShootLoaded = false;
        bool playerHitLoaded = false;
        bool enemyHitLoaded = false;
        bool levelUpLoaded = false;
        bool gameOverLoaded = false;
        bool initialized = false;
        bool shootLoaded = false;
};

#endif
