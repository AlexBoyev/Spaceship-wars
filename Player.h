#ifndef PLAYER_H
#define PLAYER_H

const int AMMO = 15;
const int HIT_POINTS = 5;
const int MAX_BULLETS = 10; // Maximum number of bullets allowed
#include "Bullets.h"

class Player {
public:
    Player(int x, int y);
    void move(char direction, int gameWidth, int gameHeight);
    bool shoot(); // Returns true if the player can shoot, false otherwise

    void updateBullets(); // Update bullet positions
    Bullet* getBullets(); // Get active bullets

    // Getter methods
    int getX();
    int getY();
    int getHitPoints();
    int getAmmo();
    int getPowerUp();

    // Setter methods
    void setX(int newX);
    void setY(int newY);
    void setHitPoints(int newHitPoints);
    void setAmmo(int newAmmo);
    void setPowerUps(int powerup);

private:
    int x;
    int y;
    int hitPoints;
    int ammo;
    int powerUps;
    Bullet bullets[MAX_BULLETS]; // Store active bullets
};

#endif
