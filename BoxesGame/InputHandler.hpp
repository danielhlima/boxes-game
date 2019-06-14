//
//  InputHandler.hpp
//  BoxesGame
//
//  Created by Daniel Lima on 14/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include "Vector2D.hpp"

enum mouse_button
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler
{
public:
    
    static InputHandler* Instance()
    {
        if(s_pInstance == NULL)
        {
            s_pInstance = new InputHandler();
        }
        
        return s_pInstance;
    }
    
    void reset();
    
    void update();
    
    bool isKeyDown(SDL_Scancode key) const;
    
    // mouse events
    bool getMouseButtonState(int buttonNumber) const;
    Vector2D* getMousePosition() const;
    
private:
    
    InputHandler();
    ~InputHandler();
    
    InputHandler(const InputHandler&);
    InputHandler& operator=(const InputHandler&);
    
    //keyboard specific
    const Uint8* m_keystates;
    void onKeyDown();
    void onKeyUp();
    
    //Mouse specific
    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);
    
    std::vector<bool> m_mouseButtonStates;
    Vector2D* m_mousePosition;
    

    static InputHandler* s_pInstance;
};

















