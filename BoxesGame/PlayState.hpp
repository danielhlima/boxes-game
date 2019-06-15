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
    
//    bool withinGrid(int colNum, int rowNum);
//    void buildMatrix();
//    
//    std::vector<GameObject*> neighbours(int  row, int col);
//    void updateMatrix();
    
    
};
