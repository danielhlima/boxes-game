//
//  PauseState.cpp
//  BoxesGame
//
//  Created by Daniel Lima on 17/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#include "PauseState.hpp"

const std::string PauseState::s_gamepauseID = "GAMEPAUSE";

void PauseState::s_resumeGame()
{
    Game::Instance()->getStateMachine()->popState();
}

void PauseState::s_pauseToMainMenu()
{
    std::cout<<"Play state"<<std::endl;
    Game::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void PauseState::update()
{
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

void PauseState::render()
{
    if (m_loadingComplete && !m_gameObjects.empty())
    {
        for(int i=0; i<m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->draw();
        }
    }
}

bool PauseState::onEnter()
{
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_resumeGame);
    m_callbacks.push_back(s_pauseToMainMenu);
    
    if(!TextureManager::Instance()->load("assets/game/fundo_paused.png", "fundo_paused", Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    if(!TextureManager::Instance()->load("assets/menu/menu_resume.png", "resume_button", Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    if(!TextureManager::Instance()->load("assets/menu/main_menu.png", "main_menu_button", Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    GameObject* fundo = new NPCObject(new LoaderParams(0, 0, 1024, 768, "fundo_paused", 1, 0, 0, 0));
    GameObject* quitButton = new MenuButton(new LoaderParams(806, 539, 200, 150, "resume_button", 1, 0, 1, 0));
    GameObject* playButton = new MenuButton(new LoaderParams(17, 539, 200, 150, "main_menu_button", 1, 0, 2, 0));
    
    
    m_gameObjects.push_back(fundo);
    m_gameObjects.push_back(quitButton);
    m_gameObjects.push_back(playButton);
    
    setCallbacks(m_callbacks);
    
    SoundManager::Instance()->pauseMusic();
    
    m_loadingComplete = true;
    std::cout<<"Entering PauseState"<<std::endl;
    return true;
}

bool PauseState::onExit()
{
    m_exiting = true;
    
    if(m_loadingComplete && !m_gameObjects.empty())
    {
        m_gameObjects.back()->clean();
        m_gameObjects.pop_back();
    }
    
    m_gameObjects.clear();
    
    InputHandler::Instance()->reset();
    TextureManager::Instance()->clearFromTextureMap("fundo_paused");
    TextureManager::Instance()->clearFromTextureMap("resume_button");
    
    SoundManager::Instance()->resumeMusic();
    std::cout<<"Exiting PauseState"<<std::endl;
    return true;
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
{
    if(!m_gameObjects.empty())
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            if(dynamic_cast<MenuButton*>(m_gameObjects[i]))
            {
                MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
                pButton->setCallback(callbacks[pButton->getCallbackID()]);
            }
        }
    }
}
