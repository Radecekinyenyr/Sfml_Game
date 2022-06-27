#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#define PI 3.14159265359


class Shot
{
private:
	sf::CircleShape* shotTexture;
	static const float speed;
	sf::Vector2f plPos;
	sf::Vector2f direction;
	sf::Vector2f shotPosition;
	bool wasSet = false;

	float vectorAngle(sf::Vector2f currentPos, sf::Vector2f target)
	{
		target -= currentPos;
		return atan2(target.y, target.x);

	}

public:
	Shot()
	{
		shotTexture = new sf::CircleShape(4);
		shotTexture->setFillColor(sf::Color::Blue);

	}

	~Shot()
	{
		delete shotTexture;
		std::cout << "shot destroyed!!" << std::endl;
	}

	void shoot(sf::Vector2f playerPos, sf::Vector2f mousePosition)
	{
		if (wasSet == false)
		{
			shotTexture->setPosition(playerPos);
			
			float angleToMouse = vectorAngle(playerPos, mousePosition);
			direction.x = cos(angleToMouse) * speed;
			direction.y = sin(angleToMouse) * speed;
			std::cout << "x: " << mousePosition.x << " y: " << mousePosition.y << std::endl;
			wasSet = true;
		}

	}

	void move()
	{
		if (wasSet == true) { shotTexture->move(direction); }
	}

	sf::CircleShape getShotTexture()
	{
		return *shotTexture;
	}

	sf::Vector2f& getShotPosition()
	{
		shotPosition = shotTexture->getPosition();
		return shotPosition;
	}

	void setPosition(sf::Vector2f shotPos)
	{
		shotTexture->setPosition(shotPos);
	}
};

const float Shot::speed = 0.2;