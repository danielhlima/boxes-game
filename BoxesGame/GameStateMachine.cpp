//
//  GameStateMachine.cpp
//  BoxesGame
//
//  Created by Daniel Lima on 14/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#include "GameStateMachine.hpp"

void GameStateMachine::clean()
{
    if(!m_gameStates.empty())
    {
        m_gameStates.back()->onExit();
        delete m_gameStates.back();
        m_gameStates.clear();
    }
}

void GameStateMachine::update()
{
    if(!m_gameStates.empty())
    {
        m_gameStates.back()->update();
    }
}

void GameStateMachine::render()
{
    if(!m_gameStates.empty())
    {
        m_gameStates.back()->render();
    }
}

void GameStateMachine::pushState(GameState* pState)
{
    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
}

void GameStateMachine::popState()
{
    if(!m_gameStates.empty())
    {
        m_gameStates.back()->onExit();
        m_gameStates.pop_back();
        m_gameStates.back()->resume();
    }
}

void GameStateMachine::changeState(GameState* pState)
{
    if(!m_gameStates.empty())
    {
        if(m_gameStates.back()->getStateID() == pState->getStateID())
        {
            return;
        }
        while(!m_gameStates.empty())
        {
            m_gameStates.back()->onExit();
            m_gameStates.pop_back();
        }
    }
    
    pState->onEnter();
    m_gameStates.push_back(pState);
}
