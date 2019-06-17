//
//  PlayStateBase.hpp
//  BoxesGame
//
//  Created by Daniel Lima on 15/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#pragma once

#include "GameState.hpp"
#include "GameObject.hpp"

class PlayStateBase : public GameState
{
public:
    
    virtual ~PlayStateBase(){}
    
protected:
    
    std::vector<GameObject*> m_gameObjects;
    
    int level;
};
