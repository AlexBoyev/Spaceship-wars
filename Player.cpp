#include "Player.h"

// Constructor
Player::Player(int x, int y) : x(x), y(y), hitPoints(HIT_POINTS), ammo(AMMO), powerUps(0) {
    // Initialize bullets array
    for (int i = 0; i < MAX_BULLETS; ++i) {
        bullets[i] = { 0, 0, false };
    }
}

// Move function implementation
void Player::move(char direction, int gameWidth, int gameHeight) {
    int newX = getX();
    int newY = getY();
    switch (direction) {
    case 'A':
    case 'a':
        if (newX > 0) newX--; // Move left
        break;
    case 'D':
    case 'd':
        if (newX < gameWidth - 1) newX++; // Move right
        break;
    case 'W':
    case 'w':
        if (newY > 0) newY--; // Move up
        break;
    case 'S':
    case 's':
        if (newY < gameHeight - 1) newY++; // Move down
        break;
    default:
        // Invalid input, do nothing
        break;
    }
    setX(newX);
    setY(newY);
}

bool Player::shoot() {
    if (ammo > 0) {
        for (int i = 0; i < MAX_BULLETS; ++i) {
            if (!bullets[i].active) {
                bullets[i] = { x, y - 1, true };
                ammo--;
                return true;
            }
        }
    }
    return false;
}



void Player::updateBullets() {
    for (int i = 0; i < MAX_BULLETS; ++i) {
        if (bullets[i].active) {
            bullets[i].y--;
            if (bullets[i].y < 0) {
                bullets[i].active = false;
            }
        }
    }
}


// Get active bullets
Bullet* Player::getBullets() {
    return bullets;
}

// Getter methods
int Player::getX() {
    return x;
}

int Player::getY() {
    return y;
}

int Player::getHitPoints() {
    return hitPoints;
}

int Player::getAmmo() {
    return ammo;
}

int Player::getPowerUp() {
    return powerUps;
}

// Setter methods
void Player::setX(int newX) {
    x = newX;
}

void Player::setY(int newY) {
    y = newY;
}

void Player::setHitPoints(int newHitPoints) {
    hitPoints = newHitPoints;
}

void Player::setAmmo(int newAmmo) {
    ammo = newAmmo;
}

void Player::setPowerUps(int powerup) {
    powerUps = powerup;
}
