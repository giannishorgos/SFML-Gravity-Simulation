#ifndef COLISION_H
#define COLISION_H

#include "player.h"

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

#define HEIGHT 600
#define WIDTH 1800
#define DIAMETER 20.0f

class Player;

class Collision
{
public:
    Collision();
    ~Collision();
    //detects collision with the walls and calulate the new speed
    void detectCollision(Player** players, int players_number, bool *grav, float *total_time, sf::RenderWindow& win);
    /*detect the collision between the balls and return the number of collisions
     *@return the number of collision */
    int CollisionBetweenObjects(Player** players, int players_number);
};

#endif // COLISION_H
