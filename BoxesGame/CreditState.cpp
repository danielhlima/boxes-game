//
//  CreditState.cpp
//  BoxesGame
//
//  Created by Daniel Lima on 15/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#include "CreditState.hpp"
#include <iostream>
#include "TextureManager.hpp"
#include "InputHandler.hpp"
#include "Game.hpp"
#include "MenuButton.hpp"
#include "NPCObject.hpp"
#include "MainMenuState.hpp"

const std::string CreditState::s_menuID = "CREDITS";

void CreditState::s_backToMainMenu()
{
    Game::Instance()->getStateMachine()->changeState(new MainMenuState());
    std::cout<<"Back to main menu"<<std::endl;
}

void CreditState::update()
{
    if(!m_gameObjects.empty() && !m_exiting && m_loadingComplete)
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

void CreditState::render()
{
    if (m_loadingComplete && !m_gameObjects.empty() && !m_exiting)
    {
        for(int i=0; i<m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->draw();
        }
    }
}

bool CreditState::onEnter()
{
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_backToMainMenu);
    
    if(!TextureManager::Instance()->load("assets/credito/credito.png", "credito", Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    if(!TextureManager::Instance()->load("assets/menu/menu_back.png", "back_button", Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    
    GameObject* creditoFundo = new NPCObject(new LoaderParams(0, 0, 1024, 768, "credito", 1, 0, 0));
    
    GameObject* backButton = new MenuButton(new LoaderParams(806, 539, 200, 150, "back_button", 1, 1, 0));
    
    m_gameObjects.push_back(creditoFundo);
    m_gameObjects.push_back(backButton);
    
    setCallbacks(m_callbacks);
    
    m_loadingComplete = true;
    std::cout<<"Entering CreditState"<<std::endl;
    return true;
}

bool CreditState::onExit()
{
    m_exiting = true;
    
    if(m_loadingComplete && !m_gameObjects.empty())
    {
        m_gameObjects.back()->clean();
        m_gameObjects.pop_back();
    }
    
    m_gameObjects.clear();
    
    InputHandler::Instance()->reset();
    
    std::cout<<"Exiting CreditState"<<std::endl;
    return true;
}

void CreditState::setCallbacks(const std::vector<Callback>& callbacks)
{
    // go through the game objects
    if(!m_gameObjects.empty())
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            // if they are of type MenuButton then assign a callback based on the id passed in from the file
            if(dynamic_cast<MenuButton*>(m_gameObjects[i]))
            {
                MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
                pButton->setCallback(callbacks[pButton->getCallbackID()]);
            }
        }
    }
}
