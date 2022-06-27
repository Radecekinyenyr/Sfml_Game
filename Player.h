#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <math.h>
#include "gameTile.h"
#include "Shot.h"
#include "Collision.h"

#define PI 3.141592
class Player : public Entity
{

private:

	static const float speed;
	sf::CircleShape* circle = nullptr;
	Collision* collision;
	sf::RectangleShape* line = nullptr;
	sf::Vector2f PositionOfMouse;
	sf::Vector2f MyPosition;
	static const sf::Time delayRange;
	int lastOne = 0;
	std::vector<Shot*> shots;
	bool shotWasSet = false;
	bool shotMustBeDelete = true;

public:

	Player()
	{
		
	}

	Player(int health, int power, sf::Vector2f basePosition)
	{
		circle = new sf::CircleShape();
		line = new sf::RectangleShape();
		collision = new Collision();

		setEntityStatus(health, power);
		setPosition(basePosition);
		circle = getCircle();
		line = getLine();
		
	}

	~Player()
	{
		shots.clear();
		shots.shrink_to_fit();
		delete collision;
	}

	void control(sf::Time &delay, sf::Clock &clock, sf::RenderWindow& window)
	{
		

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			circle->move(-speed, 0);
			line->move(-speed, 0);

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			circle->move(speed, 0);
			line->move(speed, 0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			circle->move(0, -speed);
			line->move(0, -speed);

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			circle->move(0, speed);
			line->move(0, speed);
			
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{ 
			if (delay >= delayRange)
			{
				std::cout << "Bang!!!" << " pozice mysi: " << PositionOfMouse.x << " " << PositionOfMouse.y << " LastOne: " << lastOne << std::endl;
				shots.push_back(new Shot());
				shotWasSet = true;
				lastOne = shots.size();
				shots[lastOne - 1]->shoot(circle->getPosition(), PositionOfMouse);
				clock.restart();
			}

		}

		if (shotWasSet == true) {
			for (int i = 0; i < shots.size(); ++i)
			shots[i]->move();

	
		}
		

	}

	sf::Vector2f& getPosition()
	{
		MyPosition = circle->getPosition();
		return MyPosition;
	}

	
	void drawShot(sf::RenderWindow& window)
	{
		if (shotWasSet == true)
		{

			for (int i = 0; i < shots.size(); ++i)
				window.draw(shots[i]->getShotTexture());

			for (int i = 0; i < shots.size(); ++i) {
				collision->setObjectPosition(shots[i]->getShotPosition());
				collision->InCollision(2.0f, shotMustBeDelete);

				if (shotMustBeDelete == false)
				{
					delete shots[i];
					shots.erase(shots.begin() + i);
					shotMustBeDelete = true;
				}
			}
		}
	}

	void setTileMapForShots(TileMap& tileMap)
	{
		collision->setBlockPosition(tileMap.getBlockPosition());
	}

	void rotate(sf::RenderWindow & window)
	{
		MyPosition = circle->getPosition();
		PositionOfMouse.x = sf::Mouse::getPosition(window).x;
		PositionOfMouse.y = sf::Mouse::getPosition(window).y;

		MyPosition -= PositionOfMouse;
		float rotation = atan2(MyPosition.x, MyPosition.y) * 180 / PI;
		float rotation2 = atan2(MyPosition.y, MyPosition.x) * 180 / PI;

		circle->setRotation(rotation);
		line->setRotation(rotation2);

	}
};

const float  Player::speed = 0.07;
const sf::Time Player::delayRange = sf::milliseconds(100);
