//
//  MainMenuState.hpp
//  BoxesGame
//
//  Created by Daniel Lima on 14/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#pragma once

#include <vector>
#include <iostream>
#include "MenuState.hpp"
#include "GameObject.hpp"
#include "SettingsState.hpp"
#include "TextureManager.hpp"
#include "InputHandler.hpp"
#include "Game.hpp"
#include "MenuButton.hpp"
#include "NPCObject.hpp"
#include "CreditState.hpp"
#include "SoundManager.hpp"
#include "PlayState.hpp"

class MainMenuState : public MenuState
{
public:

    virtual ~MainMenuState(){}

    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const
    {
        return s_menuID;
    }

private:

    virtual void setCallbacks(const std::vector<Callback>& callbacks);

    static void s_menuToPlay();
    static void s_exitFromMenu();
    static void s_menuToSettings();
    static void s_menuToCredits();

    static const std::string s_menuID;

    std::vector<GameObject*> m_gameObjects;
};
