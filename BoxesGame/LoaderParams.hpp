//
//  LoaderParams.hpp
//  BoxesGame
//
//  Created by Daniel Lima on 14/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#pragma once

#include <string>

class LoaderParams
{
public:
    
    LoaderParams(int x, int y, int width, int height, std::string textureID, int numFrames, int callbackID = 0, int animSpeed = 0) :
    m_x(x),
    m_y(y),
    m_width(width),
    m_height(height),
    m_textureID(textureID),
    m_numFrames(numFrames),
    m_callbackID(callbackID),
    m_animSpeed(animSpeed)
    {
        
    }
    
private:
    
    int m_x;
    int m_y;
    
    int m_width;
    int m_height;
    
    int m_callbackID;
    int m_animSpeed;
    
    std::string m_textureID;
    
    int m_numFrames;
};
