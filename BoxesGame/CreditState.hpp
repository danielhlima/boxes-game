//
//  CreditState.hpp
//  BoxesGame
//
//  Created by Daniel Lima on 15/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#pragma once

#include <vector>
#include <iostream>
#include "MenuState.hpp"
#include "MainMenuState.hpp"
#include "MenuButton.hpp"
#include "GameObject.hpp"
#include "TextureManager.hpp"
#include "InputHandler.hpp"
#include "Game.hpp"
#include "NPCObject.hpp"

class CreditState : public MenuState
{
public:
    
    virtual ~CreditState(){}
    
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
    
    static void s_backToMainMenu();
    
    static const std::string s_menuID;
    
    std::vector<GameObject*> m_gameObjects;
};



