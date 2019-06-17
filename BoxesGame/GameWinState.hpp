//
//  GameWinState.hpp
//  BoxesGame
//
//  Created by Daniel Lima on 17/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#pragma once

#include "MenuState.hpp"
#include "MainMenuState.hpp"
#include "GameObject.hpp"
#include <vector>
#include <iostream>
#include "TextureManager.hpp"
#include "InputHandler.hpp"
#include "Game.hpp"
#include "MenuButton.hpp"
#include "NPCObject.hpp"
#include "SoundManager.hpp"
#include "PlayState.hpp"

class GameWinState : public MenuState
{
public:
    
    virtual ~GameWinState(){}
    
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    
    virtual std::string getStateID() const
    {
        return s_gamewinID;
    }
    
private:
    
    static const std::string s_gamewinID;
    static void s_exitMenu();
    static void s_menuToPlay();
    
    virtual void setCallbacks(const std::vector<Callback>& callbacks);
    
    std::vector<GameObject*> m_gameObjects;
};
