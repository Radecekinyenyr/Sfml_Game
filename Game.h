#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>
#include "gameTile.h"
#include "Collision.h"
#include <vector>

class Game
{
private:
	sf::RenderWindow* window;
	sf::Event event;
	Player* player;
	Collision* collision;
	TileMap tileMap;
    int realBlockCount = 0;
	int countOfBlocksY = 0;
	int countOfBlocksX = 0;

public:
	
	Game()	
	{
		window = new sf::RenderWindow(sf::VideoMode(1200, 600), "TRIO");
		player = new Player(100, 50, {100,100});
		collision = new Collision();
		countOfBlocksX = 25;
		countOfBlocksY = 12;

	}
	~Game()
	{
		delete window;
		delete collision;
		delete player;
		
	}

	bool isRunning()
	{
		
		return window->isOpen();
	}
	
	void Event()
	{
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
	}

	void update()
	{
		player->control();
		player->rotate(*window);
		collision->setPlayerPosition(*player);
		collision->InCollision();
		player->setPosition(collision->movePlayer());
	}

	void render()
	{
		window->clear();
		player->draw(*window);
		window->draw(tileMap);
		window->display();
	}

	void map(char tilemap[12][25])
	{
		tileMap.load(sf::Vector2u(50,50), countOfBlocksX, countOfBlocksY, tilemap);
		collision->setBlockPosition(tileMap.getBlockPosition());
	}

	sf::Texture loadingFromFile(const std::string& file)
	{
		sf::Texture texture;
		if (!texture.loadFromFile(file))
			std::cout << "Chyba pri otvirani obrazku!!!" << std::endl;

		return texture;

	}

	const sf::RenderWindow& getWindow() const
	{
		return *window;
	}
};