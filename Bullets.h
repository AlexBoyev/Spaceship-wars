// Bullets.h
#ifndef BULLETS_H
#define BULLETS_H

struct Bullet {
    int x;
    int y;
    bool active;

    Bullet() : x(0), y(0), active(false) {}
    Bullet(int x, int y, bool active) : x(x), y(y), active(active) {}
};

#endif
