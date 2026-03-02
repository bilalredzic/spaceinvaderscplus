#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "AudioManager.hpp"
#include <SDL3/SDL.h>

bool AudioManager::init() {
    // Initialize the audio engine once before any sounds are loaded or played.
    if (initialized) return true;

    if (ma_engine_init(nullptr, &engine) != MA_SUCCESS) {
        SDL_Log("miniaudio engine init failed");
        return false;
    }

    initialized = true;
    return true;
}

void AudioManager::shutdown() {
    // Unload each sound resource before shutting down the audio engine itself.
    if (shootLoaded) {
        ma_sound_uninit(&shootSound);
        shootLoaded = false;
    }

    if (enemyShootLoaded) {
        ma_sound_uninit(&enemyShootSound);
        enemyShootLoaded = false;
    }

    if (playerHitLoaded) {
        ma_sound_uninit(&playerHitSound);
        playerHitLoaded = false;
    }

    if (enemyHitLoaded) {
        ma_sound_uninit(&enemyHitSound);
        enemyHitLoaded = false;
    }   

    if (levelUpLoaded) {
        ma_sound_uninit(&levelUpSound);
        levelUpLoaded = false;
    }

    if (gameOverLoaded) {
        ma_sound_uninit(&gameOverSound);
        gameOverLoaded = false;
    }   

    if (musicLoaded) {
        ma_sound_uninit(&music);
        musicLoaded = false;
    }

    if (projectileClashLoaded) {
        ma_sound_uninit(&projectileClashSound);
        projectileClashLoaded = false;
    }



    if (initialized) {
        ma_engine_uninit(&engine);
        initialized = false;
    }
}

bool AudioManager::loadShootSound(const char* filepath) {
    // Load the player's firing sound so it can be reused each time the player shoots.
    if (!initialized) return false;

    if (ma_sound_init_from_file(&engine, filepath, 0, nullptr, nullptr, &shootSound) != MA_SUCCESS) {
        SDL_Log("Failed to load shoot sound: %s", filepath);
        return false;
    }

    shootLoaded = true;
    return true;
}

void AudioManager::playShoot() {
    // Restart the sound from the beginning each time the player fires.
    if (!shootLoaded) return;

    ma_sound_stop(&shootSound);
    ma_sound_seek_to_pcm_frame(&shootSound, 0);
    ma_sound_start(&shootSound);
}

bool AudioManager::loadEnemyShootSound(const char* filepath) {
    // Load the enemy firing sound so each enemy shot can reuse the same resource.
    if (!initialized) return false;

    if (ma_sound_init_from_file(&engine, filepath, 0, nullptr, nullptr, &enemyShootSound) != MA_SUCCESS) {
        SDL_Log("Failed to load enemy shoot sound: %s", filepath);
        return false;
    }

    enemyShootLoaded = true;
    return true;
}

void AudioManager::playEnemyShoot() {
    // Restart the sound from the beginning each time an enemy fires.
    if (!enemyShootLoaded) return;

    ma_sound_stop(&enemyShootSound);
    ma_sound_seek_to_pcm_frame(&enemyShootSound, 0);
    ma_sound_start(&enemyShootSound);
}

bool AudioManager::loadPlayerHitSound(const char* filepath) {
    // Load the sound played when the player takes damage.
    if (!initialized) return false;

    if (ma_sound_init_from_file(&engine, filepath, 0, nullptr, nullptr, &playerHitSound) != MA_SUCCESS) {
        SDL_Log("Failed to load player hit sound: %s", filepath);
        return false;
    }

    playerHitLoaded = true;
    return true;
}

void AudioManager::playPlayerHit() {
    // Restart the player-hit sound for each damage event.
    if (!playerHitLoaded) return;

    ma_sound_stop(&playerHitSound);
    ma_sound_seek_to_pcm_frame(&playerHitSound, 0);
    ma_sound_start(&playerHitSound);
}

bool AudioManager::loadEnemyHitSound(const char* filepath) {
    // Load the sound played when an enemy is destroyed.
    if (!initialized) return false;

    if (ma_sound_init_from_file(&engine, filepath, 0, nullptr, nullptr, &enemyHitSound) != MA_SUCCESS) {
        SDL_Log("Failed to load enemy hit sound: %s", filepath);
        return false;
    }

    enemyHitLoaded = true;
    return true;
}

void AudioManager::playEnemyHit() {
    // Restart the enemy-hit sound for each enemy destroyed.
    if (!enemyHitLoaded) return;

    ma_sound_stop(&enemyHitSound);
    ma_sound_seek_to_pcm_frame(&enemyHitSound, 0);
    ma_sound_start(&enemyHitSound);
}

bool AudioManager::loadLevelUpSound(const char* filepath) {
    // Load the sound used when the player advances to the next level.
    if (!initialized) return false;

    if (ma_sound_init_from_file(&engine, filepath, 0, nullptr, nullptr, &levelUpSound) != MA_SUCCESS) {
        SDL_Log("Failed to load level up sound: %s", filepath);
        return false;
    }

    levelUpLoaded = true;
    return true;
}

void AudioManager::playLevelUp() {
    // Restart the level-up sound each time progression occurs.
    if (!levelUpLoaded) return;

    ma_sound_stop(&levelUpSound);
    ma_sound_seek_to_pcm_frame(&levelUpSound, 0);
    ma_sound_start(&levelUpSound);
}

bool AudioManager::loadGameOverSound(const char* filepath) {
    // Load the sound played when the run ends.
    if (!initialized) return false;

    if (ma_sound_init_from_file(&engine, filepath, 0, nullptr, nullptr, &gameOverSound) != MA_SUCCESS) {
        SDL_Log("Failed to load game over sound: %s", filepath);
        return false;
    }

    gameOverLoaded = true;
    return true;
}

void AudioManager::playGameOver() {
    // Restart the game-over sound when the player loses all lives.
    if (!gameOverLoaded) return;

    ma_sound_stop(&gameOverSound);
    ma_sound_seek_to_pcm_frame(&gameOverSound, 0);
    ma_sound_start(&gameOverSound);
}

bool AudioManager::loadMusic(const char* filepath) {
    // Load the background music track and configure it to loop continuously.
    if (!initialized) return false;

    if (ma_sound_init_from_file(&engine, filepath, 0, nullptr, nullptr, &music) != MA_SUCCESS) {
        SDL_Log("Failed to load music: %s", filepath);
        return false;
    }

    ma_sound_set_looping(&music, MA_TRUE);
    musicLoaded = true;
    return true;
}

void AudioManager::playMusic() {
    // Restart the background music from the beginning whenever a scene wants it to play.
    if (!musicLoaded) return;

    ma_sound_stop(&music);
    ma_sound_seek_to_pcm_frame(&music, 0);
    ma_sound_start(&music);
}

void AudioManager::stopMusic() {
    // Stop the background music without unloading the music resource.
    if (!musicLoaded) return;
    ma_sound_stop(&music);
}

bool AudioManager::loadProjectileClashSound(const char* filepath) {
    // Load the sound played when projectiles clash.
    if (!initialized) return false;

    if (ma_sound_init_from_file(&engine, filepath, 0, nullptr, nullptr, &projectileClashSound) != MA_SUCCESS) {
        SDL_Log("Failed to load projectile clash sound: %s", filepath);
        return false;
    }

    projectileClashLoaded = true;
    return true;
}

void AudioManager::playProjectileClash() {
    // Restart the projectile clash sound whenever opposing bullets collide.
    if (!projectileClashLoaded) return;

    ma_sound_stop(&projectileClashSound);
    ma_sound_seek_to_pcm_frame(&projectileClashSound, 0);
    ma_sound_start(&projectileClashSound);
}
