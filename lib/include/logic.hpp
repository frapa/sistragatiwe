#ifndef LOGIC
#define LOGIC

#include <iostream>
#include <SFML/System.hpp>
#include "world.hpp"
#include "player.hpp"
#include <lemon/smart_graph.h>

typedef lemon::SmartDigraph::Node Node;
typedef lemon::SmartDigraph::Arc Arc;

void logic(World* w) {
    World& world = *w;
    
    while (true) {
        // update resources 
        for (Player& player: world.players) {
            for (Node t: player.territories) {
                player.food += world.map.area[t];
            }
        }
        
        sf::sleep(sf::seconds(1));
    }
} 

#endif
