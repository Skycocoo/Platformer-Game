// Yuxi Luo (yl4217), February 26, 2018
// CS3113 Game Programming

#include "GameState.h"
#include "../setUp.h"

extern ShaderProgram untextured;
extern ShaderProgram textured;

enum GameMode {STATE_MAIN_MENU, STATE_GAME_LEVEL, STATE_GAME_OVER};
extern GameMode mode;


GameState::GameState(){
    xml = XMLLoad("Asset/sheet.xml");
    untextured = setUntextured();
    
    GLuint text;
    textured = setTextured("Asset/font1.png", text);
    disp = Text(&textured, text);
    
    init();
}

void GameState::init(){
    GLuint texture;
    textured = setTextured("Asset/sheet.png", texture);
    
    std::vector<XMLData> playerlife;
    playerlife.push_back(xml.getData("playerShip1_blue.png"));
    playerlife.push_back(xml.getData("playerShip1_damage1.png"));
    playerlife.push_back(xml.getData("playerShip1_damage2.png"));
    playerlife.push_back(xml.getData("playerShip1_damage3.png"));
    playerlife.push_back(xml.getData("playerLife1_blue.png"));
    
    enemygroup = EnemyGroup(texture, xml.getData("enemyBlack1.png"), glm::vec3(0, 2, 0));
    player = Player(texture, playerlife, glm::vec3(0, -4, 0));
}


// bullets: disappear when collide
void GameState::checkCollision(){
    
    // players' bullet: collide with enemy / with board
    for (size_t i = 0; i < player.bul.size(); i++){
        for (size_t j = 0; j < enemygroup.ene.size(); j++){
            if (player.bul[i].collide(enemygroup.ene[j])){
                player.delBullet(i);
                player.incScore(10);
                enemygroup.delEne(j);
            }
        }
    }
    
    // enemy's bullet: collide with player / with board
    for (size_t i = 0; i < enemygroup.ene.size(); i++){
        for (size_t j = 0; j < enemygroup.ene[i].bul.size(); j++){
            if (enemygroup.ene[i].bul[j].collide(player)){
                player.decLives();
                enemygroup.ene[i].delBullet(j);
            }
        }
    }
}

void GameState::update(float elapsed){
    switch (mode){
        case STATE_MAIN_MENU:
            break;
        case STATE_GAME_LEVEL:
            checkCollision();
            player.update(elapsed);
            enemygroup.update(elapsed);
            if (player.getLives() == 0 || enemygroup.getEne() == 0) mode = STATE_GAME_OVER;
            break;
        case STATE_GAME_OVER:
            break;
    }
}


void GameState::render(){
    switch (mode){
        case STATE_MAIN_MENU:
            displayMainMenu();
            break;
        case STATE_GAME_LEVEL:
            displayLevel();
            break;
        case STATE_GAME_OVER:
            displayOver();
            break;
    }
    
}


void GameState::displayMainMenu(){
    disp.render("Space Invaders", 1, 2, 0, 3.5);
    disp.render("<=   =>   to move", 0.5, 1, 0, 1);
    disp.render("[     ]  to fight", 0.5, 1, 0, 0);
    
    disp.render("B: begin   Q: quit", 0.5, 1, 0, -1.5);
}

void GameState::displayLevel(){
    player.render();
    enemygroup.render();
    
    disp.render("Score: " + std::to_string(player.getScore()), 0.4, 1, -4, 3.5);
    disp.render("Lives: ", 0.4, 1, 3.5, 3.5);
    player.renderLives();
}

void GameState::displayOver(){
    disp.render("Game Over", 1, 2, 0, 1.5);
    
    std::string winner = (player.getLives() == 0) ? "Enemy" : "Player";
    disp.render(winner + " wins", 1, 2, 0, 0);
    
    disp.render("B: begin   Q: quit", 0.5, 1, 0, -1.5);
}

