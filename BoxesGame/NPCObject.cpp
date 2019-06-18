//
//  NPCObject.cpp
//  BoxesGame
//
//  Created by Daniel Lima on 15/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#include "NPCObject.hpp"


NPCObject::NPCObject(const LoaderParams* pParams):GameObject(pParams)
{
    m_position = Vector2D(pParams->getX(), pParams->getY());
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();
    m_numFrames = pParams->getNumFrames();
}

void NPCObject::draw()
{
    TextureManager::Instance()->draw(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(), m_width, m_height, Game::Instance()->getRenderer(), SDL_FLIP_NONE);
}

void NPCObject::update()
{
    
}

void NPCObject::clean()
{
    
}
