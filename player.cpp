#include "player.h"

Player::Player(float initial_speed, float horizontal_speed)
{
    //set the ball at random posisiton at the beggining
	cir.setPosition(sf::Vector2f(rand() % (WIDTH - 10), rand() % (HEIGHT - 10 - HEIGHT / 2 - 10 + 1) + HEIGHT / 2 - 10) /*HEIGHT - DIAMETER)*/);
	this->initial_speed = initial_speed;
	this->horizontal_speed = horizontal_speed;
	//at start the ball doesent move
	is_stoped = true;
	vertical_speed = 0.0f;
	gravity_speed = 1.0f;
	mass = 1.0f;
	cir.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
}

Player::~Player()
{
	std::cout << "Player is destroyed . . . \n";
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(cir);
}

void Player::SetPosition(float x, float y)
{
    cir.setPosition(sf::Vector2f(x, y));
}

void Player::setIntialSpeed(float initial_speed) { this->initial_speed = initial_speed; }

void Player::setVerticalSpeed(float vertical_speed) { this-> vertical_speed = vertical_speed; }

void Player::setHorizontalSpeed(float horizontal_speed) { this->horizontal_speed = horizontal_speed; }

void Player::setGravitySpeed(float gravity_speed) { this->gravity_speed = gravity_speed; }

void Player::setIsStoped(bool action) { is_stoped = action; }

void Player::setMass(float mass) { this->mass = mass; }

float Player::getInitialSpeed() { return initial_speed; }

float Player::getHorizontalSpeed() { return horizontal_speed; }

float Player::getVerticalSpeed() { return vertical_speed; }

float Player::getGravitySpeed() { return gravity_speed; }

bool Player::getIsStoped() { return is_stoped; }

float Player::getMass() { return mass; }

void Player::movePlayer()
{
    //std::cout << vertical_speed << "\t" << (vertical_speed > 0.0f ? "DOWN" : "UP") << std::endl;
    cir.move(horizontal_speed, vertical_speed);
}

sf::Vector2<float> Player::getPosition()
{
    return cir.getPosition();
}





