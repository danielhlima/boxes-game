//
//  PlayState.hpp
//  BoxesGame
//
//  Created by Daniel Lima on 15/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#pragma once

#include <iostream>
#include "PlayStateBase.hpp"
#include "Box.hpp"
#include <SDL2/SDL.h>
#include "InputHandler.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"
#include "NPCObject.hpp"
#include "SoundManager.hpp"
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include "GameOverSatate.hpp"
#include "PauseState.hpp"
#include "GameWinState.hpp"

int const ROWS = 14;
int const COLS = 50;
int const INITIAL_X_POSITION = 0;
int const INITIAL_Y_POSITION = 150;
int const INITIAL_COLUMN = 15;
int const MAX_FRAMES_ENABLED = 5;
int const LAST_LEVEL = 1;


class PlayState : public PlayStateBase
{
public:
    
    
    virtual ~PlayState(){}
    
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    
    bool isUpdating() { return updating; }
    virtual std::string getStateID() const { return s_playID; }
    void verifyNeighbours(int x, int y);
    void updateLevel();
    
    int getPoints() { return points; }
    void updatePoints (int value) { points += value; }
    
    static int b_x, b_y;
    static void boxChosen(int x, int y);
    Uint32 frameStart, frameTime;
    int factor=100, factorMultitple=100, velocity_matrix = 4000;
    
private:
    
    static const std::string s_playID;
    bool updating;
    GameObject* matrix[ROWS][COLS];
    std::vector<GameObject*> neighbours;
    int points;
    
    bool withinGrid(int colNum, int rowNum);
    void buildMatrix();
    std::vector<GameObject*> getNeighbours(int  row, int col);
    void updateMatrix();
    void reorganizeMatrix();
    void columnDown(int indexX, int indexY);
    void checkLimitMatrix();
    void moveMatrix();
    void checkVoidColumn();
    void createRandomColumn();
    void verifyLevel();
};
