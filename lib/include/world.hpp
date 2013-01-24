#ifndef WORLD
#define WORLD

#include <iostream>
#include <algorithm>
#include <random>
#include "pugixml.hpp"
#include "territory.hpp"
#include "map.hpp"
#include "player.hpp"
#include <lemon/smart_graph.h>

typedef lemon::SmartDigraph::Node Node;
typedef lemon::SmartDigraph::Arc Arc;

class World {
public:
    // map stores informations about the world
    Map map;
    
    std::vector<Player> players;

    // initialize game
    World(std::string map_file)
    {
        // create a new xml document
        pugi::xml_document world;
        // construct it from a file
        world.load_file(map_file.c_str());
        
        // load all territories from the file
        for (pugi::xml_node territory: world.child("map").children("territory")) {
            // add territory to map, using document data
            map.addTerritory(territory.attribute("path").value(),
                territory.attribute("name").value());
        }
        
        // create roads between territories
        for (pugi::xml_node territory: world.child("map").children("territory")) {
            for (pugi::xml_node link: territory.children("link")) {
                Node from = map.getTerritoryByName(territory.attribute("name").value());
                Node to = map.getTerritoryByName(link.attribute("to").value());

                map.addRoad(from, to, link.attribute("length").as_float());
            }
        }
        
        // create players
        players.emplace(players.end(), "Human");

        // create a random number generator
        std::mt19937 gen;
        std::uniform_int_distribution<int> dist(0, map.getTerritoryCount() - 1);

        // randomly assign a territory to start with to each player
        std::vector<int> numbers;
        for (Player& player: players) {
            int number;

            // get a number (and check the corresponding territory has not already
            // been assigned to another player)
            do {
                number = dist(gen);
            } while (std::find(numbers.begin(), numbers.end(), number) != numbers.end());

            // assign territory to player
            player.addTerritory(map.getTerritoryByNumber(number));

            numbers.push_back(number);
        }
    }
};

#endif
