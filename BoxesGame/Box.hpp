//
//  Box.hpp
//  BoxesGame
//
//  Created by Daniel Lima on 15/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#pragma once

#include "GameObject.hpp"

class Box : public GameObject
{
public:

    Box(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();

    void setCallback(void(*callback)()) { m_callback = callback;}
    int getCallbackID() { return m_callbackID; }
    
    int m_xIndex;
    int m_yIndex;

private:

    
    bool m_bReleased;
    int m_callbackID;
    void (*m_callback)();
};
