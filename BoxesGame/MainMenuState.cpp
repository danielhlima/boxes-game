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
#include "MenuButton.hpp"
#include "NPCObject.hpp"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::s_menuToPlay()
{
//    Game::Instance()->getStateMachine()->changeState(new PlayState());
    std::cout<<"Play state"<<std::endl;
}

void MainMenuState::s_menuToSettings()
{
    std::cout<<"Settings state"<<std::endl;
}

void MainMenuState::s_menuToCredits()
{
    std::cout<<"Credits state"<<std::endl;
}

void MainMenuState::s_exitFromMenu()
{
    std::cout<<"Quit state"<<std::endl;
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
    m_callbacks.push_back(s_menuToSettings);
    m_callbacks.push_back(s_menuToCredits);
    m_callbacks.push_back(s_exitFromMenu);
    
    if(!TextureManager::Instance()->load("assets/menu/fundo.png", "fundo", Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    if(!TextureManager::Instance()->load("assets/menu/menu_play.png", "play_button", Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    if(!TextureManager::Instance()->load("assets/menu/menu_settings.png", "settings_button", Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    if(!TextureManager::Instance()->load("assets/menu/menu_credits.png", "credits_button", Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    if(!TextureManager::Instance()->load("assets/menu/menu_quit.png", "quit_button", Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    GameObject* fundo = new NPCObject(new LoaderParams(0, 0, 1024, 768, "fundo", 1, 0, 0));
    
    GameObject* playButton = new MenuButton(new LoaderParams(17, 539, 200, 150, "play_button", 1, 1, 0));
    
    GameObject* settingsButton = new MenuButton(new LoaderParams(280, 539, 200, 150, "settings_button", 1, 2, 0));
    
    GameObject* creditsButton = new MenuButton(new LoaderParams(546, 539, 200, 150, "credits_button", 1, 3, 0));
    
    GameObject* quitButton = new MenuButton(new LoaderParams(806, 539, 200, 150, "quit_button", 1, 4, 0));
    
    m_gameObjects.push_back(fundo);
    m_gameObjects.push_back(playButton);
    m_gameObjects.push_back(settingsButton);
    m_gameObjects.push_back(creditsButton);
    m_gameObjects.push_back(quitButton);
    
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
            if(dynamic_cast<MenuButton*>(m_gameObjects[i]))
            {
                MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
                pButton->setCallback(callbacks[pButton->getCallbackID()]);
            }
        }
    }
}









