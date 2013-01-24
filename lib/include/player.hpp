#ifndef PLAYER
#define PLAYER

#include <vector>
#include <string>
#include <lemon/smart_graph.h>

typedef lemon::SmartDigraph::Node Node;
typedef lemon::SmartDigraph::Arc Arc;

class Player {
public:
    std::vector<Node> territories;

    int food;

    std::string name;

    Player(std::string _name):
        name(_name), food(0)
    {}

    void addTerritory(Node node);
};

#endif
