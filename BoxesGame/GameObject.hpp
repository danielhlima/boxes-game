//
//  GameObject.hpp
//  BoxesGame
//
//  Created by Daniel Lima on 14/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#pragma once

#include "LoaderParams.hpp"
#include "Vector2D.hpp"
#include <string>
#include <memory>

class GameObject
{
public:
    
    virtual void draw() =0;
    virtual void update() =0;
    virtual void clean() = 0;
    virtual std::string type() =0;
    
    Vector2D& getPosition()
    {
        return m_position;
    }
    
    int getWidth()
    {
        return m_width;
    }
    
    int getHeight()
    {
        return m_height;
    }
    
protected:
    
    GameObject(const LoaderParams* pParams){}
    virtual ~GameObject(){}
    
    Vector2D m_position;
    
    int m_width;
    int m_height;
    
    int m_currentRow;
    int m_currentFrame;
    int m_numFrames;
    std::string m_textureID;
    
    int m_alpha;
};
