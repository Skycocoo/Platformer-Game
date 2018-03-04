// Yuxi Luo (yl4217), February 26, 2018
// Homework 3, Space Invaders, CS3113 Game Programming

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <cstdlib>
#include <vector>

#include "Util/Util.h"
#include "setUp.h"

using namespace std;

enum GameMode {STATE_MAIN_MENU, STATE_GAME_LEVEL, STATE_GAME_OVER};
GameMode mode = STATE_MAIN_MENU;

float screenRatio = 0.0, screenHeight = 0.0, screenWidth = 0.0, splitScale = 0.0, edge = 1.0;

ShaderProgram textured;
ShaderProgram untextured;




void updateGame(const SDL_Event& event, GameState& game){
    switch (event.type){
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode){
                case SDL_SCANCODE_B:
                    if (mode == STATE_GAME_OVER) game.init();
                    mode = STATE_GAME_LEVEL;
                    break;
                case SDL_SCANCODE_SPACE:
                    if (mode == STATE_GAME_LEVEL) game.player.addBullet();
                    break;
                case SDL_SCANCODE_LEFT:
                    if (mode == STATE_GAME_LEVEL) game.player.control(-1);
                    break;
                case SDL_SCANCODE_RIGHT:
                    if (mode == STATE_GAME_LEVEL) game.player.control(1);
                    break;
            }
            break;
    }
}



int main(){
    // initial set up
    srand(time(NULL));
    SDL_Window* displayWindow = setUp("Homework 3 Space Invaders");

    GameState game;
    
    SDL_Event event;
    bool done = false;
    float lastFrameTicks = 0.0f;
    while (!done) {
        
        // keyboard event
        while (SDL_PollEvent(&event)) {
            checkKeyboard(event, done);
            updateGame(event, game);
        }
        
        // update parameters
        float ticks = (float)SDL_GetTicks()/1000.0f;
        float elapsed = ticks - lastFrameTicks;
        lastFrameTicks = ticks;
        
        game.update(elapsed);
        
        // display
        glClear(GL_COLOR_BUFFER_BIT);

        game.render();

        SDL_GL_SwapWindow(displayWindow);
    }

    SDL_Quit();

    return 0;
}
