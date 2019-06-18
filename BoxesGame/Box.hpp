//
//  Box.hpp
//  BoxesGame
//
//  Created by Daniel Lima on 15/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#pragma once

#include "GameObject.hpp"
#include "PlayState.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"

class Box : public GameObject
{
public:

    Box(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();
    
    int m_xIndex;
    int m_yIndex;

private:
    
    bool m_bReleased;
};
