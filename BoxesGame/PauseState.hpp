//
//  PauseState.hpp
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

class PauseState : public MenuState
{
public:
    
    virtual ~PauseState(){};
    
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    
    virtual std::string getStateID() const
    {
        return s_gamepauseID;
    }
    
private:
    
    static const std::string s_gamepauseID;
    static void s_resumeGame();
    
    virtual void setCallbacks(const std::vector<Callback>& callbacks);
    
    std::vector<GameObject*> m_gameObjects;
};

