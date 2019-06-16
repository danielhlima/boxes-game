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

int const ROWS = 7;
int const COLS = 15;
int const INITIAL_X_POSITION = 0;
int const INITIAL_Y_POSITION = 150;
int const INITIAL_COLUMN = 6;
int const VELOCITY_MATRIX = 4000;
int const MAX_FRAMES_ENABLED = 6;

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
    
    static int b_x, b_y;
    static void boxChosen(int x, int y);
    Uint32 frameStart, frameTime;
    
private:
    
    static const std::string s_playID;
    bool updating;
    GameObject* matrix[ROWS][COLS];
    std::vector<GameObject*> neighbours;
    
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
};
