//
//  SoundManager.hpp
///  BoxesGame
//
//  Created by Daniel Lima on 14/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#pragma once

#include <iostream>
#include <map>
#include <string>
#include <SDL2/SDL_mixer.h>
#include "SettingsState.hpp"

enum sound_type
{
    SOUND_MUSIC = 0,
    SOUND_SFX = 1
};

class SoundManager
{
public:
    
    static SoundManager* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new SoundManager();
            return s_pInstance;
        }
        return s_pInstance;
    }
    
    bool load(std::string fileName, std::string id, sound_type type);
    
    void playSound(std::string id, int loop);
    void playMusic(std::string id, int loop);
    void stopTheMusic();
    void pauseMusic();
    void resumeMusic();
    bool isPlaying();
    void quit();
    
private:
    
    static SoundManager* s_pInstance;
    
    std::map<std::string, Mix_Chunk*> m_sfxs;
    std::map<std::string, Mix_Music*> m_music;
    
    SoundManager();
    ~SoundManager();
    
    SoundManager(const SoundManager&);
	SoundManager& operator=(const SoundManager&);
};
