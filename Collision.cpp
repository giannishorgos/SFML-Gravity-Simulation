#include "Collision.h"

Collision::Collision()
{
    //ctor
}

Collision::~Collision()
{
    //dtor
}

void Collision::detectCollision(Player** players, int players_number, bool *grav, float *total_time, sf::RenderWindow& win)
{
    for(int i = 0; i < players_number; i++)
    {
        //collision with left side bounds
        if(players[i]->getPosition().x <= 0.0f)
        {
            players[i]->SetPosition(0.0f, players[i]->getPosition().y);
            players[i]->setHorizontalSpeed(-players[i]->getHorizontalSpeed());
        }
        //collision with right side bounds
        else if(players[i]->getPosition().x >= WIDTH - DIAMETER)
        {
            players[i]->SetPosition(WIDTH - DIAMETER, players[i]->getPosition().y);
            players[i]->setHorizontalSpeed(-players[i]->getHorizontalSpeed());
        }
        //collision with the ground
        if(players[i]->getPosition().y + DIAMETER >= HEIGHT)
        {
            players[i]->SetPosition(players[i]->getPosition().x, HEIGHT - DIAMETER);
            //apply tribh
            if(fabs(players[i]->getHorizontalSpeed()) >= 0.5)
            {
                players[i]->setHorizontalSpeed(players[i]->getHorizontalSpeed() - (players[i]->getHorizontalSpeed() / 10)); //tribh from the ground. more trinh == smaller paranomasth
            }
            //stop the movement if the horizontal speed is very small
            else
                players[i]->setHorizontalSpeed(0.0f);
            //if the vertical speed is very small stop the movement of the object
            if(fabs(players[i]->getVerticalSpeed()) <= 0.5f)
            {
                players[i]->setIsStoped(true);
                players[i]->setVerticalSpeed(0.0f);
            }
            else
            {
                players[i]->setIntialSpeed(players[i]->getVerticalSpeed() - (players[i]->getVerticalSpeed() / 5)); //air force. greater force == smaller paranomasth
                //*total_time = 0;
                players[i]->setGravitySpeed(0.0f);
                players[i]->setVerticalSpeed(0.0f);
            }
        }
        if(abs(players[i]->getPosition().x - sf::Mouse::getPosition(win).x) <= DIAMETER)
            players[i]->setHorizontalSpeed(10 * -players[i]->getHorizontalSpeed());
    }
}

int Collision::CollisionBetweenObjects(Player** players, int players_number)
{
    int counter = -1000000;
    static int crushes = 0;
    float sum_of_masses;
    float sub_m1;
    float sub_m2;

	for(int i = 0; i < players_number; i++)
		for(int j = 0; j < players_number; j++)
		{
			if(i == j || counter > 0) continue;
			else if(players[i]->getPosition().x - players[j]->getPosition().x > -DIAMETER
                    && players[i]->getPosition().x - players[j]->getPosition().x < 0.0f
                    && fabs(players[i]->getPosition().y - players[j]->getPosition().y) <= DIAMETER / 2)
            {
                    sum_of_masses = players[i]->getMass() + players[j]->getMass();
                    sub_m1 = players[i]->getMass() - players[j]->getMass();
                    sub_m2 = players[j]->getMass() - players[i]->getMass();
                    float temp = players[i]->getHorizontalSpeed();

                    players[i]->setHorizontalSpeed(players[i]->getHorizontalSpeed() * sub_m1 / sum_of_masses +
                                                   2 * players[j]->getMass() * players[j]->getHorizontalSpeed() / sum_of_masses);

                    players[j]->setHorizontalSpeed(players[j]->getHorizontalSpeed() * sub_m2 / sum_of_masses +
                                                   2 * players[i]->getMass() * temp / sum_of_masses);

                    players[i]->SetPosition(players[j]->getPosition().x - DIAMETER < 0 ? players[i]->getPosition().x : players[j]->getPosition().x - DIAMETER, players[i]->getPosition().y);
                    counter++;
                    crushes++;
            }
            else if(players[i]->getPosition().x - players[j]->getPosition().x < DIAMETER
                    && players[i]->getPosition().x - players[j]->getPosition().x > 0.0f
                    && fabs(players[i]->getPosition().y - players[j]->getPosition().y) <= DIAMETER / 2)
            {
                    sum_of_masses = players[i]->getMass() + players[j]->getMass();
                    sub_m1 = players[i]->getMass() - players[j]->getMass();
                    sub_m2 = players[j]->getMass() - players[i]->getMass();
                    float temp = players[i]->getHorizontalSpeed();

                    players[i]->setHorizontalSpeed(players[i]->getHorizontalSpeed() * sub_m1 / sum_of_masses +
                                                   2 * players[j]->getMass() * players[j]->getHorizontalSpeed() / sum_of_masses);

                    players[j]->setHorizontalSpeed(players[j]->getHorizontalSpeed() * sub_m2 / sum_of_masses +
                                                   2 * players[i]->getMass() * temp / sum_of_masses);

                    players[j]->SetPosition(players[i]->getPosition().x - DIAMETER < 0 ? players[j]->getPosition().x : players[i]->getPosition().x - DIAMETER, players[j]->getPosition().y);
                    counter++;
                    crushes++;
            }
            if(players[i]->getPosition().y - players[j]->getPosition().y > -DIAMETER
               && players[i]->getPosition().y - players[j]->getPosition().y < 0.0f
               && fabs(players[i]->getPosition().x - players[j]->getPosition().x) <= DIAMETER / 2)
            {
                    sum_of_masses = players[i]->getMass() + players[j]->getMass();
                    sub_m1 = players[i]->getMass() - players[j]->getMass();
                    sub_m2 = players[j]->getMass() - players[i]->getMass();
                    float temp = players[i]->getVerticalSpeed();

                    players[i]->setHorizontalSpeed(players[i]->getVerticalSpeed() * sub_m1 / sum_of_masses +
                                                   2 * players[j]->getMass() * players[j]->getVerticalSpeed() / sum_of_masses);

                    players[j]->setHorizontalSpeed(players[j]->getVerticalSpeed() * sub_m2 / sum_of_masses +
                                                   2 * players[i]->getMass() * temp / sum_of_masses);

                    //players[j]->SetPosition(players[j]->getPosition().x, players[j]->getPosition().y - DIAMETER < 0 ? players[j]->getPosition().y : players[i]->getPosition().y - DIAMETER);
                    counter++;
                    crushes++;
            }
            else if(players[i]->getPosition().x - players[j]->getPosition().x < DIAMETER
                    && players[i]->getPosition().x - players[j]->getPosition().x > 0.0f
                    && fabs(players[i]->getPosition().y - players[j]->getPosition().y) <= DIAMETER / 2)
            {
                    sum_of_masses = players[i]->getMass() + players[j]->getMass();
                    sub_m1 = players[i]->getMass() - players[j]->getMass();
                    sub_m2 = players[j]->getMass() - players[i]->getMass();
                    float temp = players[i]->getHorizontalSpeed();

                    players[i]->setHorizontalSpeed(players[i]->getHorizontalSpeed() * sub_m1 / sum_of_masses +
                                                   2 * players[j]->getMass() * players[j]->getHorizontalSpeed() / sum_of_masses);

                    players[j]->setHorizontalSpeed(players[j]->getHorizontalSpeed() * sub_m2 / sum_of_masses +
                                                   2 * players[i]->getMass() * temp / sum_of_masses);

                    //players[j]->SetPosition(players[i]->getPosition().x - DIAMETER < 0 ? players[j]->getPosition().x : players[i]->getPosition().x - DIAMETER, players[j]->getPosition().y);
                    counter++;
                    crushes++;
            }


		}
		return crushes;
}














