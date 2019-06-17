//
//  SettingsState.cpp
//  BoxesGame
//
//  Created by Daniel Lima on 17/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#include "SettingsState.hpp"

const std::string SettingsState::s_gamesettingsID = "SETTINGS";

void SettingsState::s_settingsToMainMenu()
{
    Game::Instance()->getStateMachine()->popState();
}

void SettingsState::update()
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

void SettingsState::render()
{
    if (m_loadingComplete && !m_gameObjects.empty())
    {
        for(int i=0; i<m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->draw();
        }
    }
}

bool SettingsState::onEnter()
{
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_settingsToMainMenu);
    
    if(!TextureManager::Instance()->load("assets/game/fundo_game.png", "fundo_settings", Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    if(!TextureManager::Instance()->load("assets/menu/main_menu.png", "main_menu_button", Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    GameObject* fundo = new NPCObject(new LoaderParams(0, 0, 1024, 768, "fundo_settings", 1, 0, 0, 0));
    GameObject* playButton = new MenuButton(new LoaderParams(17, 539, 200, 150, "main_menu_button", 1, 0, 1, 0));
    
    
    m_gameObjects.push_back(fundo);
    m_gameObjects.push_back(playButton);
    
    setCallbacks(m_callbacks);
    m_loadingComplete = true;
    return true;
}

bool SettingsState::onExit()
{
    m_exiting = true;
    
    if(m_loadingComplete && !m_gameObjects.empty())
    {
        m_gameObjects.back()->clean();
        m_gameObjects.pop_back();
    }
    
    m_gameObjects.clear();
    
    InputHandler::Instance()->reset();
    TextureManager::Instance()->clearFromTextureMap("fundo_settings");
    TextureManager::Instance()->clearFromTextureMap("main_menu_button");
    
    SoundManager::Instance()->resumeMusic();
    return true;
}

void SettingsState::setCallbacks(const std::vector<Callback>& callbacks)
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
