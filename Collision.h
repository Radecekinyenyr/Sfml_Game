#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

extern int blockCount;

struct BlockPosition
{
	sf::Vector2f topLeft;
	sf::Vector2f topRight;
	sf::Vector2f bottomLeft;
	sf::Vector2f bottomRight;
	sf::Vector2f midPoint;

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
	sf::Vector2f objectPosition;
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

	void setObjectPosition(sf::Vector2f& objectPos) { objectPosition = objectPos; }

	double mag(sf::Vector2f v) const
	{
		return std::sqrt(v.x * v.x + v.y * v.y);
	}
	 
	sf::Vector2f norm(sf::Vector2f vec) const
	{
		float normer = 1.0f / mag({ vec.x, vec.y });
		return { vec.x * normer, vec.y * normer };
	}

	sf::Vector2f moveObject()
	{
		return objectPosition;
	}



	void InCollision(float objectSize, bool& deleteIt)
	{
		lineLength.clear();
		lineLength.shrink_to_fit();

		for (auto i = 0; i < blockCount; ++i)
		{

			x = abs(blockPosition[i].midPoint.x) - abs(objectPosition.x);
			y = abs(blockPosition[i].midPoint.y) - abs(objectPosition.y);
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
		nearestPoint.x = std::max(float(nearestBlock.topLeft.x), std::min(objectPosition.x, float(nearestBlock.bottomRight.x)));
		nearestPoint.y = std::max(float(nearestBlock.topLeft.y), std::min(objectPosition.y, float(nearestBlock.bottomRight.y)));

		sf::Vector2f rayNearestPoint;
		rayNearestPoint = nearestPoint - objectPosition;
		
		float overLap = objectSize - mag(rayNearestPoint);

		

		if (std::isnan(overLap))
			overLap = 0;

		if (overLap >= 0) { 
			if (deleteIt == false)
			objectPosition = objectPosition - norm(rayNearestPoint) * overLap; 
			else deleteIt = false;
		}

	}
	
};
