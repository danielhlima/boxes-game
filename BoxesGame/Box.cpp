//
//  Box.cpp
//  BoxesGame
//
//  Created by Daniel Lima on 15/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#include "Box.hpp"

Box::Box(const LoaderParams* pParams):GameObject(pParams)
{
    m_position = Vector2D(pParams->getX(), pParams->getY());
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();
    m_numFrames = pParams->getNumFrames();
    m_currentFrame = pParams->getCurrentFrame();
}

void Box::draw()
{
    TextureManager::Instance()->drawFrame(m_textureID, m_position.getX(), m_position.getY(), m_width, m_height, 0, m_currentFrame, Game::Instance()->getRenderer(), 0, 255);
}

void Box::update()
{
    Vector2D* pMousePos = InputHandler::Instance()->getMousePosition();
    
    if(pMousePos->getX() < (m_position.getX() + m_width) && pMousePos->getX() > m_position.getX()
       && pMousePos->getY() < (m_position.getY() + m_height) && pMousePos->getY() > m_position.getY())
    {
        if(InputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
        {
            if(this->getCurrentFrame() < 8)
                PlayState::boxChosen(this->m_xIndex, this->m_yIndex);
            m_bReleased = false;
        }
        else if(!InputHandler::Instance()->getMouseButtonState(LEFT))
        {
            m_bReleased = true;
        }
    }
}

void Box::clean()
{
    
}
