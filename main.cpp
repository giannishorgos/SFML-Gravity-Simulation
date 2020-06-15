/****************************************************************|
 * TITLE: Gravity Simulation with actual                         |
 * physics.                                                      |
 * DATE: 11/05/2020                                              |
 * AUTHOR: giannis horgos                                        |
 * DESCRIPTION: Every frame move the object                      |
 * according to the gravity acceleration and the intial force.   |
 * in that case the switch time & total time are unnecessary     |
 * but if I want to make it independet from fps I will use them. |
 ****************************************************************/

#include "player.h"
#include "gravity.h"
#include "Collision.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <time.h>
#include <sstream>

#define HEIGHT 600
#define WIDTH 1800

std::string floatToString(float d)
{
   std::stringstream ss;
   ss << d;
   return ss.str();
}

std::string intToString(int d)
{
   std::stringstream ss;
   ss << d;
   return ss.str();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Gravity Simulation");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    srand(time(NULL));

    int players_number = 150;

	Player **players = new Player*[players_number];
	Gravity *gravity = new Gravity(0.0f, 0.00f);
	Collision *collision = new Collision;

	for(int i = 0; i < players_number; i++)
        players[i] = new Player(rand() % (10 - 3 + 1) + 3 , (-1 * rand() % 3 + 1) * rand() % 7 + 1);



	float total_time = 0;
    bool grav = false;
	sf::Clock clock;
	sf::Text text;
	sf::Text coll;
	sf::Font font;

	font.loadFromFile("arial.ttf");
	//set font of the text
	text.setFont(font);
	coll.setFont(font);
	//set posistion
	text.setPosition(WIDTH - 150, 0);
	coll.setPosition(0, 0);
    // set the character size
    text.setCharacterSize(24); // in pixels, not points!
    coll.setCharacterSize(24);
    // set the color
    text.setFillColor(sf::Color::White);
    coll.setFillColor(sf::Color::White);

	float last_time = 0;
	//displays on screen the fps
	int fpscounter = 0;
	//display on screen the number of collisions
	std::string crushes;

    /////////////////////////////
    ////  G A M E  L O O P   ////
    /////////////////////////////
    while (window.isOpen())
    {
        fpscounter++;

        if(fpscounter > 60)
        {
            text.setFillColor(sf::Color::White);
            fpscounter -= 60;
        }
        total_time += clock.restart().asSeconds();

        std::string fps = floatToString(1.0 / (total_time - last_time)); //calculate the fps
        last_time = total_time;

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || grav)
		{
            grav = true;
            for(int i = 0; i < players_number; i++)
                players[i]->setIsStoped(false);

            collision->detectCollision(players, players_number, &grav, &total_time, window);
            crushes = intToString(collision->CollisionBetweenObjects(players, players_number));
            gravity->gravityForce(players, players_number, &total_time, &grav);

            for(int i = 0; i < players_number; i++)
                players[i]->movePlayer();
		}


        sf::Event event;
//        crushes = floatToString(total_time);
//        fps = floatToString(players[2]->getGravitySpeed());
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
            text.setString("fps: " + fps);
            coll.setString("Crushes: " + crushes);

        window.clear();

        window.draw(text);
        window.draw(coll);
        for(int i = 0; i < players_number; i++)
            players[i]->Draw(window);

        window.display();
    }
    for(int i = 0; i < players_number; i++)
        delete players[i];
    delete[] players;
    delete gravity;
    delete collision;
    return 0;
}
