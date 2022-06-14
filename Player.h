#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <math.h>

#define PI 3.141592
class Player : public Entity
{

private:
	static const float speed;
	sf::CircleShape* circle = nullptr;
	sf::RectangleShape* line = nullptr;
	sf::Vector2f PositionOfMouse;
	sf::Vector2f MyPosition;

public:

	Player()
	{

	}

	Player(int health, int power, sf::Vector2f basePosition)
	{
		circle = new sf::CircleShape();
		line = new sf::RectangleShape();

		setEntityStatus(health, power);
		setPosition(basePosition);
		circle = getCircle();
		line = getLine();
		
	}

	~Player()
	{
		
	}

	void control()
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
	}

	sf::Vector2f getPosition()
	{
		return circle->getPosition();
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
