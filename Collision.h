#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>
#include <math.h> // absolutni hodnota

extern int blockCount;

struct BlockPosition
{
	sf::Vector2f topLeft;
	sf::Vector2f topRight;
	sf::Vector2f bottomLeft;
	sf::Vector2f bottomRight;
	sf::Vector2f playerPosition;
	sf::Vector2f midPoint;

	float playerDistanceFromBlock;

	void findMidPoint() {
		midPoint.x = topLeft.x + 25.0f;
		midPoint.y = topLeft.y + 25.0f;
	}
};

class Collision
{
private:
	sf::Vector2f closestPoint;
	sf::Vector2f distanceBetweenPoint;
	sf::Vector2f playerPosition;
	std::vector<BlockPosition> blockPosition;
	std::vector<float> lineLength;
	BlockPosition nearestBlock;
	
	float min;
	float x;
	float y;
	float c;

	bool minWasSet = false;

public:

	Collision()
	{
		
	}

	~Collision()
	{

	}

	void setBlockPosition(std::vector<BlockPosition> vectorOfBlocksPosition)
	{
		blockPosition = vectorOfBlocksPosition;
		for (auto i = 0; i < blockCount; ++i) {
			blockPosition[i].findMidPoint();
			std::cout << "pozice x: " << blockPosition[i].topLeft.x << " pozice y: " << blockPosition[i].topLeft.y << std::endl;
		}
	}

	void setPlayerPosition(Player& player) { playerPosition = player.getPosition(); }

	double mag(sf::Vector2f v) const
	{
		return std::sqrt(v.x * v.x + v.y * v.y);
	}
	 
	sf::Vector2f norm(sf::Vector2f vec) const
	{
		float normer = 1.0f / mag({ vec.x, vec.y });
		return { vec.x * normer, vec.y * normer };
	}

	sf::Vector2f movePlayer()
	{
		return playerPosition;
	}



	void InCollision()
	{
		lineLength.clear();
		lineLength.shrink_to_fit();

		for (auto i = 0; i < blockCount; ++i)
		{

			x = abs(blockPosition[i].midPoint.x) - abs(playerPosition.x);
			y = abs(blockPosition[i].midPoint.y) - abs(playerPosition.y);
			c = x * x + y * y;
			lineLength.push_back(sqrt(c));


			if (minWasSet == false) {
				min = lineLength[0];
				minWasSet = true;
			}

			if (min > lineLength[i])
			{
				min = lineLength[i];
				nearestBlock = blockPosition[i];

			}

		}


		sf::Vector2f nearestPoint;
		nearestPoint.x = std::max(float(nearestBlock.topLeft.x), std::min(playerPosition.x, float(nearestBlock.bottomRight.x)));
		nearestPoint.y = std::max(float(nearestBlock.topLeft.y), std::min(playerPosition.y, float(nearestBlock.bottomRight.y)));

		sf::Vector2f rayNearestPoint;
		rayNearestPoint = nearestPoint - playerPosition;

		float overLap = 25 - mag(rayNearestPoint);

		

		if (std::isnan(overLap))
			overLap = 0;

		if (overLap >= 0)
		{
			//std::cout << "in collision   " << mag(rayNearestPoint) << std::endl;
			playerPosition = playerPosition - norm(rayNearestPoint) * overLap;
		}



	}

		
	
};