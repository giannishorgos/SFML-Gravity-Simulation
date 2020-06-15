#include "gravity.h"

Gravity::Gravity(float gravity_speed, float switch_time) : acceleration(9.8f)
{
    this->gravity_speed = gravity_speed;
	this->switch_time = switch_time;
	//acceleration = 9.8;
	collision = new Collision;
}

Gravity::~Gravity()
{
	std::cout << "the object is destroyed. . .\n";
}

void Gravity::gravityForce(Player** players, int players_number, float* total_time, bool* grav)
{

    if(*total_time >= switch_time)
    {
        for(int i = 0; i < players_number; i++)
        {

            if(players[i]->getGravitySpeed() == 0 && !players[i]->getIsStoped())
            {

                players[i]->setVerticalSpeed(-players[i]->getInitialSpeed()); //in the first frame the gravity speed is not applied to the ball
                players[i]->setGravitySpeed(players[i]->getGravitySpeed() + 0.16); // 0.16 * 60fps = 10 m/s more every second == 10 m/s*s
            }
            else if(!players[i]->getIsStoped() && !players[i]->getIsStoped())
            {
                players[i]->setVerticalSpeed(-(players[i]->getInitialSpeed() - players[i]->getGravitySpeed()));
                players[i]->setGravitySpeed(players[i]->getGravitySpeed() + 0.16); // 0.16 * 60fps = 10 m/s more every second == 10 m/s*s
            }
            //collision->detectCollision(players, players_number, grav, i);
        }
        *total_time -= switch_time;
	}

}

void Gravity::setSwitchTime(float switch_time)
{
    this->switch_time = switch_time;
}

