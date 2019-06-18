//
//  GameWinState.cpp
//  BoxesGame
//
//  Created by Daniel Lima on 17/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#include "GameWinState.hpp"

const std::string GameWinState::s_gamewinID = "GAMEWIN";

void GameWinState::s_exitMenu()
{
    Game::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void GameWinState::s_menuToPlay()
{
    Game::Instance()->getStateMachine()->changeState(new PlayState());
}

void GameWinState::update()
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

void GameWinState::render()
{
    if (m_loadingComplete && !m_gameObjects.empty())
    {
        for(int i=0; i<m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->draw();
        }
    }
}

bool GameWinState::onEnter()
{
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_exitMenu);
    m_callbacks.push_back(s_menuToPlay);
    
    if(!TextureManager::Instance()->load("assets/game/fundo_game_win.png", "fundo_game_win", Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    if(!TextureManager::Instance()->load("assets/menu/menu_quit.png", "quit_button", Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    if(!TextureManager::Instance()->load("assets/menu/menu_play.png", "play_button", Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    GameObject* fundo = new NPCObject(new LoaderParams(0, 0, 1024, 768, "fundo_game_win", 1, 0, 0, 0));
    GameObject* quitButton = new MenuButton(new LoaderParams(806, 539, 200, 150, "quit_button", 1, 0, 1, 0));
    GameObject* playButton = new MenuButton(new LoaderParams(17, 539, 200, 150, "play_button", 1, 0, 2, 0));
    
    
    m_gameObjects.push_back(fundo);
    m_gameObjects.push_back(quitButton);
    m_gameObjects.push_back(playButton);
    
    setCallbacks(m_callbacks);
    
    SoundManager::Instance()->stopTheMusic();
    SoundManager::Instance()->load("assets/sounds/victory_theme.ogg", "victory_theme", SOUND_MUSIC);
    SoundManager::Instance()->playMusic("victory_theme", 0);
    
    m_loadingComplete = true;
    return true;
}

bool GameWinState::onExit()
{
    m_exiting = true;
    
    if(m_loadingComplete && !m_gameObjects.empty())
    {
        m_gameObjects.back()->clean();
        m_gameObjects.pop_back();
    }
    
    m_gameObjects.clear();
    
    InputHandler::Instance()->reset();
    TextureManager::Instance()->clearFromTextureMap("fundo_game_win");
    TextureManager::Instance()->clearFromTextureMap("quit_button");
    TextureManager::Instance()->clearFromTextureMap("play_button");
    
    return true;
}

void GameWinState::setCallbacks(const std::vector<Callback>& callbacks)
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
