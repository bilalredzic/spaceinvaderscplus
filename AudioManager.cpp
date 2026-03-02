#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "AudioManager.hpp"
#include <SDL3/SDL.h>

bool AudioManager::init() {
    if (initialized) return true;

    if (ma_engine_init(nullptr, &engine) != MA_SUCCESS) {
        SDL_Log("miniaudio engine init failed");
        return false;
    }

    initialized = true;
    return true;
}

void AudioManager::shutdown() {
    if (shootLoaded) {
        ma_sound_uninit(&shootSound);
        shootLoaded = false;
    }

    if (initialized) {
        ma_engine_uninit(&engine);
        initialized = false;
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


    if (initialized) {
        ma_engine_uninit(&engine);
        initialized = false;
    }
}

bool AudioManager::loadShootSound(const char* filepath) {
    if (!initialized) return false;

    if (ma_sound_init_from_file(&engine, filepath, 0, nullptr, nullptr, &shootSound) != MA_SUCCESS) {
        SDL_Log("Failed to load shoot sound: %s", filepath);
        return false;
    }

    shootLoaded = true;
    return true;
}

void AudioManager::playShoot() {
    if (!shootLoaded) return;

    ma_sound_stop(&shootSound);
    ma_sound_seek_to_pcm_frame(&shootSound, 0);
    ma_sound_start(&shootSound);
}

bool AudioManager::loadEnemyShootSound(const char* filepath) {
    if (!initialized) return false;

    if (ma_sound_init_from_file(&engine, filepath, 0, nullptr, nullptr, &enemyShootSound) != MA_SUCCESS) {
        SDL_Log("Failed to load enemy shoot sound: %s", filepath);
        return false;
    }

    enemyShootLoaded = true;
    return true;
}

void AudioManager::playEnemyShoot() {
    if (!enemyShootLoaded) return;

    ma_sound_stop(&enemyShootSound);
    ma_sound_seek_to_pcm_frame(&enemyShootSound, 0);
    ma_sound_start(&enemyShootSound);
}

bool AudioManager::loadPlayerHitSound(const char* filepath) {
    if (!initialized) return false;

    if (ma_sound_init_from_file(&engine, filepath, 0, nullptr, nullptr, &playerHitSound) != MA_SUCCESS) {
        SDL_Log("Failed to load player hit sound: %s", filepath);
        return false;
    }

    playerHitLoaded = true;
    return true;
}

void AudioManager::playPlayerHit() {
    if (!playerHitLoaded) return;

    ma_sound_stop(&playerHitSound);
    ma_sound_seek_to_pcm_frame(&playerHitSound, 0);
    ma_sound_start(&playerHitSound);
}

bool AudioManager::loadEnemyHitSound(const char* filepath) {
    if (!initialized) return false;

    if (ma_sound_init_from_file(&engine, filepath, 0, nullptr, nullptr, &enemyHitSound) != MA_SUCCESS) {
        SDL_Log("Failed to load enemy hit sound: %s", filepath);
        return false;
    }

    enemyHitLoaded = true;
    return true;
}

void AudioManager::playEnemyHit() {
    if (!enemyHitLoaded) return;

    ma_sound_stop(&enemyHitSound);
    ma_sound_seek_to_pcm_frame(&enemyHitSound, 0);
    ma_sound_start(&enemyHitSound);
}

bool AudioManager::loadLevelUpSound(const char* filepath) {
    if (!initialized) return false;

    if (ma_sound_init_from_file(&engine, filepath, 0, nullptr, nullptr, &levelUpSound) != MA_SUCCESS) {
        SDL_Log("Failed to load level up sound: %s", filepath);
        return false;
    }

    levelUpLoaded = true;
    return true;
}

void AudioManager::playLevelUp() {
    if (!levelUpLoaded) return;

    ma_sound_stop(&levelUpSound);
    ma_sound_seek_to_pcm_frame(&levelUpSound, 0);
    ma_sound_start(&levelUpSound);
}

bool AudioManager::loadGameOverSound(const char* filepath) {
    if (!initialized) return false;

    if (ma_sound_init_from_file(&engine, filepath, 0, nullptr, nullptr, &gameOverSound) != MA_SUCCESS) {
        SDL_Log("Failed to load game over sound: %s", filepath);
        return false;
    }

    gameOverLoaded = true;
    return true;
}

void AudioManager::playGameOver() {
    if (!gameOverLoaded) return;

    ma_sound_stop(&gameOverSound);
    ma_sound_seek_to_pcm_frame(&gameOverSound, 0);
    ma_sound_start(&gameOverSound);
}

bool AudioManager::loadMusic(const char* filepath) {
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
    if (!musicLoaded) return;
    ma_sound_start(&music);
}

void AudioManager::stopMusic() {
    if (!musicLoaded) return;
    ma_sound_stop(&music);
}
