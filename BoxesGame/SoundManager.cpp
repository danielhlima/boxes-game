//
//  SoundManager.cpp
//  BoxesGame
//
//  Created by Daniel Lima on 14/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//
#include "SoundManager.hpp"

SoundManager* SoundManager::s_pInstance;

SoundManager::SoundManager()
{
    Mix_OpenAudio(22050, AUDIO_S16, 2, (4096 / 2));
}

SoundManager::~SoundManager()
{
    Mix_CloseAudio();
}

bool SoundManager::load(std::string fileName, std::string id, sound_type type)
{
    if(type == SOUND_MUSIC)
    {
        Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());
        if(pMusic == 0)
        {
            std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
            return false;
        }
        
        m_music[id] = pMusic;
        return true;
    }
    else if(type == SOUND_SFX)
    {
        Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());
        if(pChunk == 0)
        {
            std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
            return false;
        }
        
        m_sfxs[id] = pChunk;
        return true;
    }
    return false;
}

void SoundManager::playMusic(std::string id, int loop)
{
    if(SettingsState::getSoundEnabled())
        Mix_PlayMusic(m_music[id], loop);
}

void SoundManager::playSound(std::string id, int loop)
{
    if(SettingsState::getSoundEnabled())
        Mix_PlayChannel(-1, m_sfxs[id], loop);
}

bool SoundManager::isPlaying()
{
    return Mix_Playing(-1);
}

void SoundManager::stopTheMusic()
{
    Mix_HaltMusic();
}

void SoundManager::pauseMusic()
{
    Mix_PauseMusic();
}

void SoundManager::resumeMusic()
{
    Mix_ResumeMusic();
}

void SoundManager::quit()
{
    Mix_HaltMusic();
    Mix_Quit();
}
