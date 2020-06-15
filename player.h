#ifndef PLAYER_H
#define PLAYER_H

#include "gravity.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

#define HEIGHT 600
#define WIDTH 1800
#define DIAMETER 20.0f

class Player
{
private:
    float initial_speed;
    float vertical_speed;
    float horizontal_speed;
    float gravity_speed;
    float mass;
    bool is_stoped;
	sf::CircleShape cir{DIAMETER / 2};

public:
	Player(float initial_speed, float horizontal_speed = 0.0f);
	Player() {}
	~Player();
	//Draw the object in the window
	void Draw(sf::RenderWindow& window);
	//set the absolute positionserss
	void SetPosition(float x, float y);
    //change the intial speed
	void setIntialSpeed(float initial_speed);
	//change the vertical speed
	void setVerticalSpeed(float vertical_speed);
	//change the horizotal speed
	void setHorizontalSpeed(float horizontal_speed);
	//change the gravity speed
	void setGravitySpeed(float gravity_speed);
	//change the katastash of the player
	void setIsStoped(bool action);
	//set the mass
	void setMass(float mass);
	//getters
	float getInitialSpeed();
	float getHorizontalSpeed();
	float getVerticalSpeed();
	float getGravitySpeed();
	bool getIsStoped();
	float getMass();
	//calculate the speed of the object and moves the object according to these new speeds
	void movePlayer();
	//get the position of the sprite
	sf::Vector2<float> getPosition();


};

#endif
