//
//  MenuButton.hpp
//  BoxesGame
//
//  Created by Daniel Lima on 14/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#pragma once

#include "GameObject.hpp"
#include "TextureManager.hpp"
#include "SoundManager.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"

class MenuButton : public GameObject
{
public:
    
    MenuButton(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();
    
    void setCallback(void(*callback)()) { m_callback = callback;}
    int getCallbackID() { return m_callbackID; }
    
private:
    
    bool m_bReleased;
    int m_callbackID;
    void (*m_callback)();
};
