#ifndef MAP
#define MAP

#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <SFML/Graphics.hpp>
#include "territory.hpp"
#include "pugixml.hpp"
#include <lemon/smart_graph.h>
#include <lemon/maps.h>

typedef lemon::SmartDigraph::Node Node;
typedef lemon::SmartDigraph::Arc Arc;

class Map: public sf::Drawable {
private:
    // graph which stores all data about the map and links between territories
    lemon::SmartDigraph graph;
    // add an attribute name to every node in the graph
    lemon::SmartDigraph::NodeMap<std::string> name;
    lemon::SmartDigraph::NodeMap<float> area;
    // each node has a pointer to its territory
    lemon::SmartDigraph::NodeMap<Territory*> territories;
    // add a length for each arc
    lemon::SmartDigraph::ArcMap<float> length;

    // used to find a node from the name
    std::map<std::string, Node> nodes;

public:
    Map():
        // node maps
        name(graph), area(graph),
        territories(graph),
        // arc maps
        length(graph)
    {}
    
    void addTerritory(std::string path, std::string _name);
    void addRoad(Node from, Node to, float _length);

    Node getTerritoryByName(std::string _name);
    Node getTerritoryByNumber(unsigned number);
    unsigned getTerritoryCount();
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
