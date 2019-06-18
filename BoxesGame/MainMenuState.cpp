//
//  MainMenuState.cpp
//  BoxesGame
//
//  Created by Daniel Lima on 14/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#include "MainMenuState.hpp"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::s_menuToPlay()
{
    Game::Instance()->getStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_menuToSettings()
{
    Game::Instance()->getStateMachine()->pushState(new SettingsState());
}

void MainMenuState::s_menuToCredits()
{
    Game::Instance()->getStateMachine()->pushState(new CreditState());
}

void MainMenuState::s_exitFromMenu()
{
    Game::Instance()->quit();
}

void MainMenuState::update()
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

    GameObject* fundo = new NPCObject(new LoaderParams(0, 0, 1024, 768, "fundo", 1, 0, 0, 0));

    GameObject* playButton = new MenuButton(new LoaderParams(17, 539, 200, 150, "play_button", 1, 0, 1, 0));

    GameObject* settingsButton = new MenuButton(new LoaderParams(280, 539, 200, 150, "settings_button", 1, 0, 2, 0));

    GameObject* creditsButton = new MenuButton(new LoaderParams(546, 539, 200, 150, "credits_button", 1, 0, 3, 0));

    GameObject* quitButton = new MenuButton(new LoaderParams(806, 539, 200, 150, "quit_button", 1, 0, 4, 0));

    m_gameObjects.push_back(fundo);
    m_gameObjects.push_back(playButton);
    m_gameObjects.push_back(settingsButton);
    m_gameObjects.push_back(creditsButton);
    m_gameObjects.push_back(quitButton);

    setCallbacks(m_callbacks);

    SoundManager::Instance()->load("assets/sounds/menu_button_sound.ogg", "menu_button", SOUND_SFX);
    SoundManager::Instance()->load("assets/sounds/Da_Jazz_Blues.ogg", "theme1", SOUND_MUSIC);
    SoundManager::Instance()->playMusic("theme1", -1);

    m_loadingComplete = true;
    
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
    TextureManager::Instance()->clearFromTextureMap("fundo");
    TextureManager::Instance()->clearFromTextureMap("play_button");
    TextureManager::Instance()->clearFromTextureMap("settings_button");
    TextureManager::Instance()->clearFromTextureMap("credits_button");
    TextureManager::Instance()->clearFromTextureMap("quit_button");

    SoundManager::Instance()->stopTheMusic();
    
    return true;
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
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
