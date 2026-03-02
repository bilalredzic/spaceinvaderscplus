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
