#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Entity
{
private:
	
	static int EntityCounts;

	int Health = 0;
	int Power = 0;
	float Speed = 0;
	

	sf::CircleShape* circle;
	sf::RectangleShape* line;



public:



	Entity()
	{

		circle = new sf::CircleShape();
		circle->setRadius(22);
		circle->setFillColor(sf::Color::Black);
		circle->setOutlineThickness(3);
		circle->setOutlineColor(sf::Color::White);
		circle->setOrigin(22,22);

		line = new sf::RectangleShape(sf::Vector2f(22, 2));
		line->setFillColor(sf::Color::Red);
		line->setOrigin(22, 1);

		++EntityCounts; std::cout << "konstruktor!!: " << EntityCounts << std::endl;
	}
	
	~Entity()
	{
		delete circle;
		delete line;
		std::cout << "destructor!!" << std::endl;
		--EntityCounts;
	}

	

	void draw(sf::RenderWindow & window)
	{
		window.draw(*circle);
		window.draw(*line);
	}

	void setPosition(sf::Vector2f newPos)
	{
		circle->setPosition(newPos);
		line->setPosition(newPos);
	}

	void setEntityStatus(int health, int power, float speed = 0.1F)
	{
		Health = health;
		Power = power;
		Speed = speed;
	}

	sf::CircleShape* getCircle() const
	{
		return circle;
	}

	sf::RectangleShape* getLine() const
	{
		return line;
	}
	
};


int Entity::EntityCounts = 0;
