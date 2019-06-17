//
//  SettingsState.hpp
//  BoxesGame
//
//  Created by Daniel Lima on 17/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#pragma once

#include "MenuState.hpp"
#include "GameObject.hpp"
#include <vector>
#include <iostream>
#include "TextureManager.hpp"
#include "InputHandler.hpp"
#include "Game.hpp"
#include "MenuButton.hpp"
#include "NPCObject.hpp"
#include "SoundManager.hpp"
#include "MainMenuState.hpp"

class SettingsState : public MenuState
{
public:
    
    virtual ~SettingsState(){};
    
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    
    virtual std::string getStateID() const
    {
        return s_gamesettingsID;
    }
    
    static bool getSoundEnabled() { return soundEnabled; }
    
private:
    
    static const std::string s_gamesettingsID;
    static void s_resumeGame();
    static void s_settingsToMainMenu();
    static void s_settingsSound();
    
    virtual void setCallbacks(const std::vector<Callback>& callbacks);
    
    std::vector<GameObject*> m_gameObjects;
    static GameObject* soundButton;
    static bool soundEnabled;
};

