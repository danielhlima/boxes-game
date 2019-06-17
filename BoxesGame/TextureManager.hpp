//
//  TextureManager.hpp
//  BoxesGame
//
//  Created by Daniel Lima on 14/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#pragma once

#include <iostream>
#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class TextureManager
{
public:
    
    static TextureManager* Instance()
    {
        if(s_pInstance == NULL)
        {
            s_pInstance = new TextureManager();
        }
        return s_pInstance;
    }
    
    bool load(std::string fileName, std::string identificator, SDL_Renderer* pRenderer);
    
    void clearTextureMap();
    void clearFromTextureMap(std::string identificator);
    
    TTF_Font* getTTF_Font() { return gFont; }
    bool m_bTtfEnabled;
    
    void draw(std::string identificator, int x, int y, int width, int height, SDL_Renderer* pRender, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawFrame(std::string identificator, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);
    
    std::map<std::string, SDL_Texture*> getTextureMap()
    {
        return m_textureMap;
    }
    
    int getTextWidth(){ return m_TextWidth; }
    int getTextHeight(){ return m_TextHeight; }
    void setTextWidth(int width) { m_TextWidth = width; }
    void setTextHeight(int height) { m_TextWidth = height; }
    
private:
    
    TextureManager() {}
    ~TextureManager() {}
    
    TextureManager(const TextureManager&);
    TextureManager& operator=(const TextureManager&);
    
    std::map<std::string, SDL_Texture*> m_textureMap;
    
    int m_TextWidth;
    int m_TextHeight;
    
    TTF_Font* gFont;
    
    static TextureManager* s_pInstance;
};
