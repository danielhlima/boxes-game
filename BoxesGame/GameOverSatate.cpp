//
//  GameOverSatate.cpp
//  BoxesGame
//
//  Created by Daniel Lima on 16/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#include "GameOverSatate.hpp"

const std::string GameOverState::s_gameoverID = "GAMEOVER";



void GameOverState::s_exitMenu()
{
    Game::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void GameOverState::update()
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

void GameOverState::render()
{
    if (m_loadingComplete && !m_gameObjects.empty())
    {
        for(int i=0; i<m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->draw();
        }
    }
}

bool GameOverState::onEnter()
{
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_exitMenu);
    
    if(!TextureManager::Instance()->load("assets/game/fundo_game_over.png", "fundo_game_over", Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    if(!TextureManager::Instance()->load("assets/menu/menu_quit.png", "quit_button", Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    GameObject* fundo = new NPCObject(new LoaderParams(0, 0, 1024, 768, "fundo_game_over", 1, 0, 0, 0));
    GameObject* quitButton = new MenuButton(new LoaderParams(806, 539, 200, 150, "quit_button", 1, 0, 1, 0));

    
    m_gameObjects.push_back(fundo);
    m_gameObjects.push_back(quitButton);
    
    setCallbacks(m_callbacks);
    
    m_loadingComplete = true;
    std::cout<<"Entering GameOverState"<<std::endl;
    return true;
}

bool GameOverState::onExit()
{
    m_exiting = true;
    
    if(m_loadingComplete && !m_gameObjects.empty())
    {
        m_gameObjects.back()->clean();
        m_gameObjects.pop_back();
    }
    
    m_gameObjects.clear();
    
    InputHandler::Instance()->reset();
    TextureManager::Instance()->clearFromTextureMap("fundo_game_over");
    TextureManager::Instance()->clearFromTextureMap("quit_button");
    
    std::cout<<"Exiting MenuState"<<std::endl;
    return true;
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
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
