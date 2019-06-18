//
//  NPCObject.hpp
//  BoxesGame
//
//  Created by Daniel Lima on 15/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#pragma once
#include "GameObject.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"

class NPCObject : public GameObject
{
public:
    
    NPCObject(const LoaderParams* pParams);
    
    virtual void draw();
    virtual void update();
    virtual void clean();
};

