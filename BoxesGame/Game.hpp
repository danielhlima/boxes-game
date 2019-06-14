//
//  Game.hpp
//  BoxesGame
//
//  Created by Daniel Lima on 14/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <vector>
#include "GameStateMachine.hpp"

class Game
{
public:
    
    static Game* Instance()
    {
        if(s_pInstance == NULL)
        {
            s_pInstance = new Game();
        }
        return s_pInstance;
    }
    
    bool init();
    
    //Loop
    void render();
    void update();
    void handleEvents();
    void clean();
    
    SDL_Renderer* getRenderer() const
    {
        return m_pRenderer;
    }
    
    SDL_Window* getWindow() const
    {
        return m_pWindow;
    }
    
    GameStateMachine* getStateMachine()
    {
        return m_pGameStateMachine;
    }
    
    bool running()
    {
        return m_bRunning;
    }
    
    void quit()
    {
        m_bRunning = false;
    }
    
    bool changingState()
    {
        return m_bChangingState;
    }
    
    void changingState(bool cs)
    {
        m_bChangingState = cs;
    }
    
    bool m_bRunning;
    
private:
    
    bool m_bChangingState;
    
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    
    GameStateMachine* m_pGameStateMachine;
    
    
    
    static Game* s_pInstance;
    
    Game();
    ~Game();
    
    Game(const Game&);
    Game& operator=(const Game&);
};

#endif /* Game_hpp */
