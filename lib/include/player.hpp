#ifndef PLAYER
#define PLAYER

#include <vector>
#include <string>
#include <lemon/smart_graph.h>
#include <SFML/Graphics.hpp>

typedef lemon::SmartDigraph::Node Node;
typedef lemon::SmartDigraph::Arc Arc;

class Player {
public:
    std::vector<Node> territories;

    int food;

    std::string name;
    sf::Color color;

    Player(std::string _name, sf::Color _color):
        name(_name), color(_color), food(0)
    {}

    void addTerritory(Node node);
};

#endif
