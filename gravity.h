#ifndef GRAVITY_H
#define GRAVITY_H

#include "player.h"
#include "Collision.h"

#include <iostream>
#include <SFML/Graphics.hpp>

#define HEIGHT 600
#define WIDTH 1800

class Player;
class Collision;

class Gravity
{
private:
	float gravity_speed;
	float switch_time;
	const float acceleration;
	Collision *collision;
public:
	Gravity(float gravity_speed, float switch_time);
	~Gravity();
	void gravityForce(Player** players, int players_number, float* total_time, bool* grav);
	void setSwitchTime(float switch_time);
};

#endif

