//
//  MainMenuState.cpp
//  BoxesGame
//
//  Created by Daniel Lima on 14/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#include "MainMenuState.hpp"
#include <iostream>
#include "TextureManager.hpp"
#include "InputHandler.hpp"
#include "Game.hpp"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::s_menuToPlay()
{
//    Game::Instance()->getStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
    Game::Instance()->quit();
}

void MainMenuState::update()
{
    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
    {
        //pause
    }
    
    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
    {
        //play
    }
    
    if(!m_gameObjects.empty())
    {
        for(int i=0; i<m_gameObjects.size(); i++)
        {
            if(m_gameObjects[i] != NULL)
            {
                m_gameObjects[i]->update();
            }
        }
    }
}

void MainMenuState::render()
{
    if (m_loadingComplete && !m_gameObjects.empty())
    {
        for(int i=0; i<m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->draw();
        }
    }
}

bool MainMenuState::onEnter()
{
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_exitFromMenu);
    
    setCallbacks(m_callbacks);
    
    m_loadingComplete = true;
    std::cout<<"Entering MenuState"<<std::endl;
    return true;
}

bool MainMenuState::onExit()
{
    m_exiting = true;
    
    if(m_loadingComplete && !m_gameObjects.empty())
    {
        m_gameObjects.back()->clean();
        m_gameObjects.pop_back();
    }
    
    m_gameObjects.clear();
    
    InputHandler::Instance()->reset();
    
    std::cout<<"Exiting MenuState"<<std::endl;
    return true;
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
    // go through the game objects
    if(!m_gameObjects.empty())
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            // if they are of type MenuButton then assign a callback based on the id passed in from the file
//            if(dynamic_cast<MenuButton*>(m_gameObjects[i]))
//            {
//                MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
//                pButton->setCallback(callbacks[pButton->getCallbackID()]);
//            }
        }
    }
}









