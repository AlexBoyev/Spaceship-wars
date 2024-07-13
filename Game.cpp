// Game.cpp
#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
Game::Game(int width, int height, int numEnemies)
    : width(width), height(height), player(width / 2, height - 1), numEnemies(numEnemies), gameBoard(nullptr), powerUpX(-1), powerUpY(-1), gameOver(false), hits(0), misses(0), isSpecialShooting(false) {
    srand(time(0));
    gameBoard = new char* [height];
    for (int i = 0; i < height; ++i) {
        gameBoard[i] = new char[width];
        for (int j = 0; j < width; ++j) {
            gameBoard[i][j] = ' ';
        }
    }
    enemies = new Enemy * [numEnemies];
    for (int i = 0; i < numEnemies; ++i) {
        int x = rand() % width;
        int y = i % (height / 2);
        enemies[i] = new Enemy(x, y);
    }
    player.setAmmo(numEnemies * 5); // Set ammo based on the number of enemies

    // Initialize special bullets array
    for (int i = 0; i < 3 * MAX_BULLETS; ++i) {
        specialBullets[i] = Bullet(); // Correct way to initialize Bullet objects
    }
}

// Destructor
Game::~Game() {
    if (enemies) {
        for (int i = 0; i < numEnemies; ++i) {
            delete enemies[i];
        }
        delete[] enemies;
    }
    if (gameBoard) {
        for (int i = 0; i < height; ++i) {
            delete[] gameBoard[i];
        }
        delete[] gameBoard;
    }
}

// Start game
void Game::startGame() {
    int moveCounter = 0;
    while (!isGameOver()) {
        handleInput();
        if (moveCounter % 15 == 0) {
            moveEnemies();
        }
        if (moveCounter % 100 == 0) {
            spawnPowerUp();
        }
        update();
        render();
        moveCounter++;
    }
    if (getNumEnemies() == 0) {
        std::cout << "You won!" << std::endl;
    }
    else {
        std::cout << "Game Over!" << std::endl;
    }
}

// Handle input
void Game::handleInput() {
    if (_kbhit()) {
        char input = _getch();
        if (input == ' ') {
            handleShooting();
        }
        else if (input == 'G' || input == 'g') {
            handleSpecialAttack();
        }
        else {
            player.move(input, width, height);
        }
    }
}

void Game::update() {
    player.updateBullets();

    Bullet* playerBullets = player.getBullets();
    for (int i = 0; i < MAX_BULLETS; ++i) {
        if (playerBullets[i].active) {
            bool hit = false;
            for (int j = 0; j < numEnemies; ++j) {
                if (playerBullets[i].x == enemies[j]->getX() && playerBullets[i].y == enemies[j]->getY()) {
                    int newHitPoints = enemies[j]->getHitPoints() - 1;
                    enemies[j]->setHitPoints(newHitPoints);
                    if (newHitPoints <= 0) {
                        delete enemies[j];
                        enemies[j] = enemies[--numEnemies];
                    }
                    playerBullets[i].active = false;
                    hits++;
                    hit = true;
                    break;
                }
            }
            if (!hit && playerBullets[i].y == 0) {
                playerBullets[i].active = false;
                misses++;
            }
        }
    }

    // Update special bullets
    if (isSpecialShooting) {
        for (int i = 0; i < 3 * MAX_BULLETS; ++i) {
            if (specialBullets[i].active) {
                specialBullets[i].y--;
                if (specialBullets[i].y < 0) {
                    specialBullets[i].active = false;
                }
                else {
                    for (int j = 0; j < numEnemies; ++j) {
                        if (specialBullets[i].x == enemies[j]->getX() && specialBullets[i].y == enemies[j]->getY()) {
                            int newHitPoints = enemies[j]->getHitPoints() - 1;
                            enemies[j]->setHitPoints(newHitPoints);
                            if (newHitPoints <= 0) {
                                delete enemies[j];
                                enemies[j] = enemies[--numEnemies];
                            }
                            specialBullets[i].active = false;
                            hits++;
                            break;
                        }
                    }
                }
            }
        }
    }

    // Check for player collisions with enemies or enemy bullets
    checkCollisions();

    for (int i = 0; i < numEnemies; ++i) {
        enemies[i]->updateBullet(height);
        Bullet* enemyBullet = enemies[i]->getBullet();
        if (enemyBullet->active) {
            if (enemyBullet->x == player.getX() && enemyBullet->y == player.getY()) {
                player.setHitPoints(player.getHitPoints() - 1);
                enemyBullet->active = false;
                if (player.getHitPoints() <= 0) {
                    gameOver = true;
                }
            }
        }
        if (enemies[i]->shouldShoot()) {
            enemies[i]->shoot();
        }
    }

    if (player.getAmmo() == 0 && numEnemies > 0) {
        gameOver = true;
    }

    if (numEnemies == 0) {
        gameOver = true;
    }

    // Check for power-up collection
    if (player.getX() == powerUpX && player.getY() == powerUpY) {
        player.setPowerUps(player.getPowerUp() + 1);
        powerUpX = -1;
        powerUpY = -1;
    }
}


void Game::handleShooting() {
    if (player.shoot()) {
        // Player successfully shoots
    }
    else {
        // Player failed to shoot (out of ammo)
    }
}


void Game::handleSpecialAttack() {
    if (player.getPowerUp() >= 3) {
        player.setPowerUps(0);
        isSpecialShooting = true;
        int startX = player.getX();
        for (int i = 0; i < 3 * MAX_BULLETS; i += 3) {
            if (!specialBullets[i].active && !specialBullets[i + 1].active && !specialBullets[i + 2].active) {
                specialBullets[i] = { startX - 1, player.getY() - 1, true };
                specialBullets[i + 1] = { startX, player.getY() - 1, true };
                specialBullets[i + 2] = { startX + 1, player.getY() - 1, true };
                break;
            }
        }
    }
}



void Game::render() {
    system("cls");
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (player.getX() == x && player.getY() == y) {
                std::cout << 'A';
            }
            else {
                bool drawn = false;
                Bullet* bullets = player.getBullets();
                for (int i = 0; i < MAX_BULLETS; ++i) {
                    if (bullets[i].active && bullets[i].x == x && bullets[i].y == y) {
                        std::cout << '^';
                        drawn = true;
                        break;
                    }
                }
                if (!drawn) {
                    for (int i = 0; i < 3 * MAX_BULLETS; ++i) {
                        if (specialBullets[i].active && specialBullets[i].x == x && specialBullets[i].y == y) {
                            std::cout << '^';
                            drawn = true;
                            break;
                        }
                    }
                }
                if (!drawn) {
                    bool enemyHere = false;
                    for (int i = 0; i < numEnemies; ++i) {
                        if (enemies[i]->getX() == x && enemies[i]->getY() == y) {
                            std::cout << 'M';
                            enemyHere = true;
                            break;
                        }
                        Bullet* enemyBullet = enemies[i]->getBullet();
                        if (enemyBullet->active && enemyBullet->x == x && enemyBullet->y == y) {
                            std::cout << 'v';
                            enemyHere = true;
                            break;
                        }
                    }
                    if (!enemyHere) {
                        if (powerUpX == x && powerUpY == y) {
                            std::cout << '+';
                        }
                        else {
                            std::cout << ' ';
                        }
                    }
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Hits: " << hits << "  Misses: " << misses << "  Player HP: " << player.getHitPoints() << "  Power-ups: " << player.getPowerUp() << "  Ammo: " << player.getAmmo() << std::endl;
}

// Move enemies
void Game::moveEnemies() {
    for (int i = 0; i < numEnemies; ++i) {
        enemies[i]->move(width, height);
    }
}

// Check if game is over
bool Game::isGameOver() {
    return gameOver;
}

// Check for collisions
void Game::checkCollisions() {
    for (int i = 0; i < numEnemies; ++i) {
        if (player.getX() == enemies[i]->getX() && player.getY() == enemies[i]->getY()) {
            // Handle collision between player and enemy
            player.setHitPoints(0); // Or any other logic you want to apply
            gameOver = true;
        }
    }
    if (player.getX() == powerUpX && player.getY() == powerUpY) {
        player.setPowerUps(player.getPowerUp() + 1);
        powerUpX = -1;
        powerUpY = -1;
    }
}


// Spawn a power-up
void Game::spawnPowerUp() {
    do {
        powerUpX = rand() % width;
        powerUpY = rand() % height;
    } while ((powerUpX == player.getX() && powerUpY == player.getY()) || isEnemyAt(powerUpX, powerUpY));
}

// Check if there is an enemy at a specific position
bool Game::isEnemyAt(int x, int y) {
    for (int i = 0; i < getNumEnemies(); ++i) {
        if (enemies[i]->getX() == x && enemies[i]->getY() == y) {
            return true;
        }
    }
    return false;
}

// Getter methods
int Game::getWidth() { return width; }
int Game::getHeight() { return height; }
Player& Game::getPlayer() { return player; }
Enemy** Game::getEnemies() { return enemies; }
int Game::getNumEnemies() { return numEnemies; }
char** Game::getGameBoard() { return gameBoard; }
int Game::getPowerUpX() { return powerUpX; }
int Game::getPowerUpY() { return powerUpY; }

// Setter methods
void Game::setWidth(int newWidth) { width = newWidth; }
void Game::setHeight(int newHeight) { height = newHeight; }
void Game::setPlayer(const Player& newPlayer) { player = newPlayer; }
void Game::setEnemies(Enemy** newEnemies) {
    if (enemies) {
        for (int i = 0; i < getNumEnemies(); ++i) {
            delete enemies[i];
        }
        delete[] enemies;
    }
    enemies = newEnemies;
}
void Game::setNumEnemies(int newNumEnemies) { numEnemies = newNumEnemies; }
void Game::setGameBoard(char** newGameBoard) {
    if (gameBoard) {
        for (int i = 0; i < height; ++i) {
            delete[] gameBoard[i];
        }
        delete[] gameBoard;
    }
    gameBoard = newGameBoard;
}
void Game::setPowerUpX(int newPowerUpX) { powerUpX = newPowerUpX; }
void Game::setPowerUpY(int newPowerUpY) { powerUpY = newPowerUpY; }
