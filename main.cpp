#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Entity.h"
#include "Game.h"

int main()
{
    char map1[12][25] = {
        "########################",
        "#......................#",
        "#........###......##...#",
        "#..........#.......#...#",
        "#..........#...........#",
        "#.................##...#",
        "###...####........##...#",
        "#............#.........#",
        "#............#.........#",
        "#..#........###........#",
        "#..#.........#.........#",
        "########################"
    };

    

    Game game;
    game.map(map1);
    while (game.isRunning())
    {
        
        game.Event();
        game.render();
        game.update();
        
    }
    

   
    return 0;
}