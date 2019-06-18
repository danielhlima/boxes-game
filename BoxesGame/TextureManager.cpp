//
//  TextureManager.cpp
//  BoxesGame
//
//  Created by Daniel Lima on 14/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#include "TextureManager.hpp"

TextureManager* TextureManager::s_pInstance = NULL;

bool TextureManager::load(std::string fileName, std::string identificator, SDL_Renderer *pRenderer)
{
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
    
    if(pTempSurface == NULL)
    {
        std::cout<<"Loading image problems: "<<IMG_GetError()<<std::endl;
        return false;
    }
    
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
    
    SDL_FreeSurface(pTempSurface);
    
    if(pTexture != NULL)
    {
        m_textureMap[identificator] = pTexture;
        return true;
    }
    
    return false;
}

void TextureManager::draw(std::string identificator, int x, int y, int width, int height, SDL_Renderer *pRender, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    
    SDL_RenderCopyEx(pRender, m_textureMap[identificator], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string identificator, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer, double angle, int alpha, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = width * currentFrame;
    srcRect.y = height * currentRow;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    
    SDL_SetTextureAlphaMod(m_textureMap[identificator], alpha);
    SDL_RenderCopyEx(pRenderer, m_textureMap[identificator], &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::clearTextureMap()
{
    m_textureMap.clear();
}

void TextureManager::clearFromTextureMap(std::string id)
{
    m_textureMap.erase(id);
}
