//
//  main.cpp
//  BoxesGame
//
//  Created by Daniel Lima on 14/06/19.
//  Copyright © 2019 Daniel Lima. All rights reserved.
//

#include <iostream>
#include "Game.hpp"

using namespace std;

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, const char * argv[]) {
    
    Uint32 frameStart, frameTime;
    
    cout<<"Game initialization attempt..."<<endl;
    if(Game::Instance()->init())
    {
        cout<<"Game initialization success!"<<endl;
        while (Game::Instance()->running())
        {
            frameStart = SDL_GetTicks();
            
            Game::Instance()->handleEvents();
            Game::Instance()->update();
            Game::Instance()->render();
            
            frameTime = SDL_GetTicks() - frameStart;
            
            if(frameTime < DELAY_TIME)
            {
                SDL_Delay((int)(DELAY_TIME - frameTime));
            }
            
            
//            SDL_Delay(10000);
//            Game::Instance()->m_bRunning = false;
        }
    }
    else
    {
        cout<<"Game initialization failure..."<<SDL_GetError()<<endl;
        return -1;
    }
    
    cout<<"Game closing..."<<endl;
    Game::Instance()->clean();
    
    return 0;
}
