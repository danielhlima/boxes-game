//
//  Game.cpp
//  BoxesGame
//
//  Created by Daniel Lima on 14/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#include "Game.hpp"
#include <iostream>
#include "InputHandler.hpp"
#include "TextureManager.hpp"
#include "MainMenuState.hpp"

using namespace std;

Game* Game::s_pInstance = NULL;

Game::Game():
m_pWindow(NULL),
m_pRenderer(NULL),
m_bRunning(false),
m_pGameStateMachine(NULL),
m_bChangingState(false)
{
    
}

Game::~Game()
{
    m_pRenderer = NULL;
    m_pWindow = NULL;
}

bool Game::init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        cout<<"SDL Initialization success"<<endl;
        
        m_pWindow = SDL_CreateWindow("The Boxes War", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, 0);
        
        if(m_pWindow != 0)
        {
            cout<<"Window creation success"<<endl;
            
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
            
            if(m_pRenderer != 0)
            {
                cout<<"Renderer creation success"<<endl;
                SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
            }
            else
            {
                cout<<"Renderer initializatio failure"<<endl;
                return false;
            }
        }
        else
        {
            cout<<"Window initialization failure"<<endl;
            return false;
        }
    }
    else
    {
        cout<<"SDL initialization failure"<<endl;
        return false;
    }
    
    //Everything initialized as expected
    
    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MainMenuState());
    
    m_bRunning = true;
    return true;
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);
    
    m_pGameStateMachine->render();
    
    SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
    m_pGameStateMachine->update();
}

void Game::handleEvents()
{
    InputHandler::Instance()->update();
}

void Game::clean()
{
    cout<<"Cleaning the game"<<endl;

    
    
    m_pGameStateMachine->clean();
    m_pGameStateMachine = NULL;
    delete m_pGameStateMachine;
    
    TextureManager::Instance()->clearTextureMap();
    
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

