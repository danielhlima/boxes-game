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
#include <SDL2/SDL.h>

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
    
    if(!m_gameObjects.empty() && m_loadingComplete && !m_exiting && !isUpdating())
    {
        for(int i=0; i<m_gameObjects.size(); i++)
        {
            if(m_gameObjects[i] != NULL)
            {
                m_gameObjects[i]->update();
            }
        }
    }
    
    
    
    if(!isUpdating())
    {
        neighbours = getNeighbours(4, 3);
        
        if(neighbours.size() > 0)
        {
            SDL_Delay(1000);
            updateMatrix();
            SDL_Delay(1000);
        }
    }
    else
    {
        reorganizeMatrix();
        SDL_Delay(1000);
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

    buildMatrix();
    
    SoundManager::Instance()->stopTheMusic();
    SoundManager::Instance()->load("assets/sounds/Matt_s_Blues.ogg", "theme2", SOUND_MUSIC);
    SoundManager::Instance()->playMusic("theme2", -1);
    
    
    m_loadingComplete = true;
    updating = false;
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
    if((colNum < 0) || (rowNum <0) ) {
        return false;
    }
    
    if((colNum >= COLS) || (rowNum >= ROWS)) {
        return false;
    }
    
    return true;
}
void PlayState::buildMatrix()
{
    srand (time(NULL));
    
    for(int i=0; i<COLS; i++)
    {
        for(int j=0; j<ROWS; j++)
        {
            if((i == 1 && j == 4) ||
               (i == 2 && j == 4) ||
               (i == 3 && j == 4) ||
               (i == 4 && j == 4) ||
               (i == 3 && j == 3) ||
               (i == 3 && j == 5))
            {
                matrix[j][i] = new Box(new LoaderParams(INITIAL_X_POSITION+i*100, INITIAL_Y_POSITION+j*75, 100, 75, "caixa_sprite", 1, 0, 0, 0));
                dynamic_cast<Box*>(matrix[j][i])->m_xIndex = j;
                dynamic_cast<Box*>(matrix[j][i])->m_yIndex = i;
                
                m_gameObjects.push_back(matrix[j][i]);
            }
            else
            {
                matrix[j][i] = new Box(new LoaderParams(INITIAL_X_POSITION+i*100, INITIAL_Y_POSITION+j*75, 100, 75, "caixa_sprite", 1, rand() % 7, 0, 0));
                dynamic_cast<Box*>(matrix[j][i])->m_xIndex = j;
                dynamic_cast<Box*>(matrix[j][i])->m_yIndex = i;
                m_gameObjects.push_back(matrix[j][i]);
            }
        }
    }
}

std::vector<GameObject*> PlayState::getNeighbours(int  row, int col)
{
    for (int colNum = col-1; colNum <= (col+1); colNum+=1)
    {
        for (int rowNum = row-1;rowNum <= (row+1); rowNum +=1)
        {
            if(!((colNum == col) && (rowNum == row)))
            {
                if(withinGrid(colNum, rowNum))
                {
                    if((colNum == (col+1) && rowNum == row) ||
                       (colNum == col && rowNum == (row+1)) ||
                       (colNum == (col-1) && rowNum == row) ||
                       (colNum == col && rowNum == (row-1))){
                        if((matrix[rowNum][colNum])->getCurrentFrame() == (matrix[row][col])->getCurrentFrame())
                        {
                            
                            if(!(std::find(neighbours.begin(), neighbours.end(), (matrix[rowNum][colNum])) != neighbours.end()))
                                
                            {
                                neighbours.push_back((matrix[rowNum][colNum]));
                                getNeighbours(rowNum, colNum);
                            }
                            
                        }
                        
                    }
                    
                }
                
            }
            
        }
        
    }
    return PlayState::neighbours;
}

void PlayState::updateMatrix()
{
    for(int i=0; i<neighbours.size(); i++)
    {
        neighbours[i]->setCurrentFrame(7);
    }
    updating = true;
}

void PlayState::reorganizeMatrix()
{
    for(int i=0; i<neighbours.size(); i++)
    {
        Box* tempBox = dynamic_cast<Box*>(neighbours[i]);
        int tRow = tempBox->m_xIndex;
        int tCol = tempBox->m_yIndex;
        
        columnDown(tRow, tCol);
    }
    neighbours.clear();
}

void PlayState::columnDown(int indexX, int indexY)
{
    for(int i=indexX; i>=0; i--)
    {
        if(i == 0)
        {
            matrix[i][indexY]->setCurrentFrame(8);
        }
        else
        {
            (matrix[i][indexY])->setCurrentFrame((matrix[i-1][indexY])->getCurrentFrame());
            int iTemp = i;
            while((matrix[iTemp][indexY])->getCurrentFrame()==7)
            {
                iTemp--;
                if(iTemp >= 0)
                    (matrix[i][indexY])->setCurrentFrame((matrix[iTemp][indexY])->getCurrentFrame());
            }
        }
    }
}
