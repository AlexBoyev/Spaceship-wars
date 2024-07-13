// Enemy.cpp
#include "Enemy.h"
#include <cstdlib>

// Constructor
Enemy::Enemy(int x, int y)
    : x(x), y(y), hitPoints(ENEMY_HIT_POINTS), shootTimer(rand() % 30 + 30) {
    bullet = Bullet();
}

// Move function implementation
void Enemy::move(int gameWidth, int gameHeight) {
    int direction = rand() % 2 ? 1 : -1;
    int newX = getX() + direction;
    if (newX >= 0 && newX < gameWidth) {
        setX(newX);
    }
}

void Enemy::shoot() {
    if (!bullet.active) {
        bullet = Bullet(x, y + 1, true); // Use the constructor with all parameters
    }
}

void Enemy::updateBullet(int gameHeight) {
    if (bullet.active) {
        bullet.y++;
        if (bullet.y >= gameHeight) {
            bullet.active = false; // Deactivate bullet when it goes off-screen
        }
    }
}

bool Enemy::shouldShoot() {
    if (--shootTimer <= 0) {
        shootTimer = rand() % 30 + 30; // Reset timer
        return true;
    }
    return false;
}

// Getter methods
int Enemy::getX() { return x; }
int Enemy::getY() { return y; }
int Enemy::getHitPoints() { return hitPoints; }
Bullet* Enemy::getBullet() { return &bullet; }

// Setter methods
void Enemy::setX(int newX) { x = newX; }
void Enemy::setY(int newY) { y = newY; }
void Enemy::setHitPoints(int newHitPoints) { hitPoints = newHitPoints; }
