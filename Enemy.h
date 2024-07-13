// Enemy.h
#ifndef ENEMY_H
#define ENEMY_H

#include "Bullets.h"

const int ENEMY_HIT_POINTS = 3;

class Enemy {
public:
    Enemy(int x, int y);
    void move(int gameWidth, int gameHeight);
    void shoot();
    void updateBullet(int gameHeight);
    bool shouldShoot();

    // Getter methods
    int getX();
    int getY();
    int getHitPoints();
    Bullet* getBullet();

    // Setter methods
    void setX(int newX);
    void setY(int newY);
    void setHitPoints(int newHitPoints);

private:
    int x;
    int y;
    int hitPoints;
    Bullet bullet; // Single bullet for each enemy
    int shootTimer;
};

#endif
