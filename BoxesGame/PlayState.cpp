//
//  PlayState.cpp
//  BoxesGame
//
//  Created by Daniel Lima on 15/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#include "PlayState.hpp"
#include "InputHandler.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"
#include "NPCObject.hpp"
#include "SoundManager.hpp"
#include <stdlib.h>
#include <time.h>
#include <algorithm>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
    if(m_loadingComplete && !m_exiting)
    {
        if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
        {
            std::cout<<"PlayGame calling PauseState"<<std::endl;
//            TheGame::Instance()->getStateMachine()->pushState(new PauseState());
        }
    }
    
    if(!m_gameObjects.empty() && m_loadingComplete && !m_exiting)
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

void PlayState::render()
{
    if (m_loadingComplete && !m_gameObjects.empty() && !m_exiting)
    {
        for(int i=0; i<m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->draw();
        }
    }
}

bool PlayState::onEnter()
{
    
    if(!TextureManager::Instance()->load("assets/game/fundo_game.png", "background_game", Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    if(!TextureManager::Instance()->load("assets/game/caixa_sprite.png", "caixa_sprite", Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    srand(time(0));
    
    GameObject* backgroundImage = new NPCObject(new LoaderParams(0, 0, 1024, 768, "background_game", 1, 0, 0, 0));
    
    
    m_gameObjects.push_back(backgroundImage);
    
    srand (time(NULL));
    
    for(int i=0; i<COLS; i++)
    {
        for(int j=0; j<ROWS; j++)
        {
            GameObject* box = NULL;
            box = new Box(new LoaderParams(INITIAL_X_POSITION+i*100, INITIAL_Y_POSITION+j*75, 100, 75, "caixa_sprite", 1, rand() % 7, 0, 0));
            m_gameObjects.push_back(box);
        }
    }
    
    
    
    
    SoundManager::Instance()->stopTheMusic();
    SoundManager::Instance()->load("assets/sounds/Matt_s_Blues.ogg", "theme2", SOUND_MUSIC);
    SoundManager::Instance()->playMusic("theme2", -1);
    
    
    m_loadingComplete = true;
    std::cout<<"Entering PlayState"<<std::endl;
    
    return true;
}

bool PlayState::onExit()
{
    m_exiting = true;
    
    if(m_loadingComplete && !m_gameObjects.empty())
    {
        m_gameObjects.back()->clean();
        m_gameObjects.pop_back();
    }
    
    m_gameObjects.clear();
    
    InputHandler::Instance()->reset();
    
    std::cout<<"Exiting PlayState"<<std::endl;
    return true;
}

bool PlayState::withinGrid(int colNum, int rowNum)
{
    return true;
}
void PlayState::buildMatrix()
{
    
}

std::vector<GameObject*> PlayState::getNeighbours(int  row, int col)
{
    return PlayState::neighbours;
}

void PlayState::updateMatrix()
{
    
}


