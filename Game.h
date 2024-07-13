#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Enemy.h"


class Game {
public:
    Game(int width, int height, int numEnemies);
    ~Game();
    void startGame();
    void moveEnemies();
    void update();
    void render();
    void handleInput();
    bool isGameOver();
    void checkCollisions();
    void handleShooting();
    void handleSpecialAttack();
    void spawnPowerUp();

    // Getter methods
    int getWidth();
    int getHeight();
    Player& getPlayer();
    Enemy** getEnemies();
    int getNumEnemies();
    char** getGameBoard();
    int getPowerUpX();
    int getPowerUpY();

    // Setter methods
    void setWidth(int newWidth);
    void setHeight(int newHeight);
    void setPlayer(const Player& newPlayer);
    void setEnemies(Enemy** newEnemies);
    void setNumEnemies(int newNumEnemies);
    void setGameBoard(char** newGameBoard);
    void setPowerUpX(int newPowerUpX);
    void setPowerUpY(int newPowerUpY);
    bool isEnemyAt(int x, int y);
    bool isPowerUpAt(int x, int y);

private:
    int width;
    int height;
    Player player;
    Enemy** enemies;
    int numEnemies;
    char** gameBoard;
    bool gameOver;
    int hits;
    int misses;
    // Special attack attributes ( Bonus )
    int powerUpX;
    int powerUpY;
    bool isSpecialShooting;
    Bullet specialBullets[3 * MAX_BULLETS];
};

#endif
