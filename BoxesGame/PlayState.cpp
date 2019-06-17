//
//  PlayState.cpp
//  BoxesGame
//
//  Created by Daniel Lima on 15/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#include "PlayState.hpp"



const std::string PlayState::s_playID = "PLAY";
int PlayState::b_x;
int PlayState::b_y;

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
    
    if(PlayState::b_x != -1 && PlayState::b_y != -1)
    {
        verifyNeighbours(PlayState::b_x, PlayState::b_y);
    }
    
    if(!isUpdating())
    {
        moveMatrix();
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
    
    if(!TextureManager::Instance()->load("assets/game/caixa_sprite_half.png", "caixa_sprite_half", Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    if(!TextureManager::Instance()->load("assets/game/trophy.png", "trophy", Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    srand(time(0));
    
    GameObject* backgroundImage = new NPCObject(new LoaderParams(0, 0, 1024, 768, "background_game", 1, 0, 0, 0));
    
    
    m_gameObjects.push_back(backgroundImage);

    buildMatrix();
    
    SoundManager::Instance()->stopTheMusic();
    SoundManager::Instance()->load("assets/sounds/Matt_s_Blues.ogg", "theme2", SOUND_MUSIC);
    SoundManager::Instance()->load("assets/sounds/applause.ogg", "applause", SOUND_SFX);
    SoundManager::Instance()->load("assets/sounds/crash_box.ogg", "crash", SOUND_SFX);
    SoundManager::Instance()->load("assets/sounds/little_crash.ogg", "little_crash", SOUND_SFX);
    SoundManager::Instance()->playMusic("theme2", -1);
    SoundManager::Instance()->playSound("applause", 0);
    
    PlayState::b_x = -1;
    PlayState::b_y = -1;
    
    level = 0;
    m_loadingComplete = true;
    updating = false;
    frameStart = SDL_GetTicks();
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
            int frame = 8;
            if(i>=INITIAL_COLUMN)
            {
                frame = rand() % MAX_FRAMES_ENABLED;
            }
                matrix[j][i] = new Box(new LoaderParams(INITIAL_X_POSITION+i*50, INITIAL_Y_POSITION+j*38, 50, 38, "caixa_sprite_half", 1, frame, 0, 0));
                dynamic_cast<Box*>(matrix[j][i])->m_xIndex = j;
                dynamic_cast<Box*>(matrix[j][i])->m_yIndex = i;
                m_gameObjects.push_back(matrix[j][i]);
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
    
    reorganizeMatrix();
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
    if(neighbours.size() > 4)
        SoundManager::Instance()->playSound("crash", 0);
    else
        SoundManager::Instance()->playSound("little_crash", 0);
    neighbours.clear();
    updating = false;
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

            while(iTemp >= 0 && (matrix[iTemp][indexY])->getCurrentFrame()==7)
            {
                iTemp--;
                if(iTemp >= 0)
                    (matrix[i][indexY])->setCurrentFrame((matrix[iTemp][indexY])->getCurrentFrame());
            }
        }
    }
}

void PlayState::verifyNeighbours(int x, int y)
{
    if(!isUpdating())
    {
        updating = true;
        neighbours = getNeighbours(x, y);
        
        if(neighbours.size() > 0)
        {
            points+=neighbours.size();
            updateMatrix();
            checkVoidColumn();
            verifyLevel();
        }
        PlayState::b_y = -1;
        PlayState::b_x = -1;
        updating = false;
    }
}

void PlayState::boxChosen(int x, int y)
{
    b_x = x;
    b_y = y;
}

void PlayState::checkVoidColumn()
{
    for(int i=COLS-1; i>=0; i--)
    {
        bool columnVoid = true;
        for(int j=ROWS-1; j>=0; j--)
        {
            if(matrix[j][i]->getCurrentFrame()!=8 &&
               matrix[j][i]->getCurrentFrame()!=7)
            {
                columnVoid = false;
                continue;
            }
        }
        if(columnVoid)
        {
            for(int k=i; k>0; k--)
            {
                for(int m=ROWS-1; m>=0; m--)
                {
                    matrix[m][k]->setCurrentFrame(matrix[m][k-1]->getCurrentFrame());
                    matrix[m][k-1]->setCurrentFrame(8);
                }
            }
        }
    }
}

void PlayState::checkLimitMatrix()
{
    if(matrix[ROWS-1][0]->getCurrentFrame()!=8 &&
       matrix[ROWS-1][0]->getCurrentFrame()!=7)
    {
        Game::Instance()->getStateMachine()->changeState(new GameOverState());
    }
    else
    {
        createRandomColumn();
    }
}

void PlayState::moveMatrix()
{
    frameTime = SDL_GetTicks() - frameStart;
    if(frameTime > velocity_matrix)
    {
        frameStart = SDL_GetTicks();
        for(int i=0; i<COLS; i++)
        {
            for(int j=0; j<ROWS; j++)
            {
                if((i+1)<COLS)
                    matrix[j][i]->setCurrentFrame(matrix[j][i+1]->getCurrentFrame());
            }
        }
        checkLimitMatrix();
    }
}

void PlayState::createRandomColumn()
{
    for(int i=0; i<ROWS; i++)
    {
        matrix[i][COLS-1]->setCurrentFrame(rand() % MAX_FRAMES_ENABLED);
    }
}

void PlayState::verifyLevel()
{
    if(points!=0 &&
       points >= factorMultitple)
    {
        level++;
        
        if(level >= 32)
        {
            //Game win
        }
        
        factorMultitple+=factor;
        if(velocity_matrix > 550)
            velocity_matrix-=(factor+factor);
        updateLevel();
    }
}

void PlayState::updateLevel()
{
    updating = true;
    SoundManager::Instance()->playSound("applause", 0);
    for(int i=0; i<COLS; i++)
    {
        for(int j=0; j<ROWS; j++)
        {
            int frame = 8;
            if(i>=INITIAL_COLUMN)
            {
                frame = rand() % MAX_FRAMES_ENABLED;
            }
            matrix[j][i]->setCurrentFrame(frame);
        }
    }
    
    int y = (level <= 16)?10:70;
    int x = (level <= 16)?level:level-16;
        
    
    GameObject* trophy = new NPCObject(new LoaderParams(x*60, y, 60, 63, "trophy", 1, 0, 0, 0));
    m_gameObjects.push_back(trophy);
    updating = false;
}

