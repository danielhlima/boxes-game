//
//  MenuButton.cpp
//  BoxesGame
//
//  Created by Daniel Lima on 14/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#include "MenuButton.hpp"


MenuButton::MenuButton(const LoaderParams* pParams):GameObject(pParams)
{
    m_position = Vector2D(pParams->getX(), pParams->getY());
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();
    m_numFrames = pParams->getNumFrames();
    m_callbackID = pParams->getCallbackID();
    m_currentFrame = pParams->getCurrentFrame();
}

void MenuButton::draw()
{
//    TextureManager::Instance()->draw(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(), m_width, m_height, Game::Instance()->getRenderer(), SDL_FLIP_NONE);
    
    TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(), m_width, m_height, 0, m_currentFrame, Game::Instance()->getRenderer(), 0, 255);
}

void MenuButton::update()
{
    Vector2D* pMousePos = InputHandler::Instance()->getMousePosition();
    
    if(pMousePos->getX() < (m_position.getX() + m_width) && pMousePos->getX() > m_position.getX()
       && pMousePos->getY() < (m_position.getY() + m_height) && pMousePos->getY() > m_position.getY())
    {
        if(InputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
        {
            if(m_callback != 0)
            {
                SoundManager::Instance()->playSound("menu_button", 0);
                m_callback();
            }
            
            m_bReleased = false;
        }
        else if(!InputHandler::Instance()->getMouseButtonState(LEFT))
        {
            m_bReleased = true;
        }
    }
}

void MenuButton::clean()
{
    
}
