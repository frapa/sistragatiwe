#ifndef WORLD
#define WORLD

#include <iostream>
#include <algorithm>
#include <random>
#include <queue>
#include <list>
#include <ctime>
#include <lemon/smart_graph.h>
#include <SFML/Graphics.hpp>
#include "pugixml.hpp"
#include "territory.hpp"
#include "map.hpp"
#include "player.hpp"
#include "message.hpp"
#include "message_spec.hpp"
#include "gui.hpp"

typedef lemon::SmartDigraph::Node Node;
typedef lemon::SmartDigraph::Arc Arc;

extern sf::Mutex mutex;

class World {
private:
    void loadFonts();

    void loadMap(std::string filename);
    void createPlayers(int humans, int bots);
    void createGui();

public:
    sf::RenderWindow& window;
    // manages gui objects and drawing
    Gui gui;
    // map stores informations about the world
    Map map;
    // list with all players
    std::vector<Player> players;
    // events from the user
    std::queue<sf::Event, std::list<sf::Event>> events;

    // initialize game
    World(sf::RenderWindow& _window, std::string map_file):
        window(_window)
    {
        loadMap(map_file);
        
        createPlayers(1, 0);

        createGui();
    }

    // starts the game logic
    void gameLogic();
};

#endif
