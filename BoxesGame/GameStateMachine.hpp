//
//  GameStateMachine.hpp
//  BoxesGame
//
//  Created by Daniel Lima on 14/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#pragma once

#include <vector>
#include "GameState.hpp"

class GameStateMachine
{
public:
    
    GameStateMachine() {}
    ~GameStateMachine() {}
    
    void update();
    void render();
    
    void pushState(GameState* pState);
    void changeState(GameState* pState);
    void popState();
    
    void clean();
    
    std::vector<GameState*>getGameStates()
    {
        return m_gameStates;
    }
    
private:
    
    std::vector<GameState*> m_gameStates;
};

