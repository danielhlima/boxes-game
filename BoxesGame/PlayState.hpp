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

int const ROWS = 6;
int const COLS = 10;
int const INITIAL_X_POSITION = 0;
int const INITIAL_Y_POSITION = 100;

class PlayState : public PlayStateBase
{
public:
    
    virtual ~PlayState(){}
    
    virtual void update();
    virtual void render();
    
    virtual bool onEnter();
    virtual bool onExit();
    
    virtual std::string getStateID() const { return s_playID; }
    
private:
    
    static const std::string s_playID;
    
    Box* matrix[ROWS][COLS] = {};
    
    std::vector<Box*> neighbours;
    
    bool withinGrid(int colNum, int rowNum);
    void buildMatrix();
    
    std::vector<Box*> getNeighbours(int  row, int col);
    void updateMatrix();
    
    
};
