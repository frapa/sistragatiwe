#include "../include/map.hpp"

void Map::addTerritory(std::string path, std::string _name) {
    // check wether name is unique, because it is used as id
    bool is_unique = true;
    for (lemon::SmartDigraph::NodeIt t(graph); t != lemon::INVALID; ++t) {
        if (name[t] == _name) {
            is_unique = false;
        }
    }

    if (is_unique) {
        Node t = graph.addNode();

        // set attributes of the node
        name[t] = _name;
        nodes[_name] = t;
        // other attributes
        territories[t] = new Territory(path); // territory which olds the geometry
        area[t] = territories[t]->getArea(); // are of the territory
    } else {
        std::cout << "Error while creating territory: name is not unique." << std::endl;
    }
}

void Map::addRoad(Node from, Node to, float _length) {
    Arc a = graph.addArc(from, to);
    length[a] = _length;
}

Node Map::getTerritoryByName(std::string _name) {
    for (lemon::SmartDigraph::NodeIt t(graph); t != lemon::INVALID; ++t) {
        if (name[t] == _name) {
            return t;
        }
    }

    return lemon::INVALID;

    /*if (nodes.find(_name) == nodes.end()) {
        return nodes[_name];
    } else {
        // if a territory with that name does not exists return invalid iterator
        return lemon::INVALID;
    }*/
}

Node Map::getTerritoryByNumber(unsigned number) {
    if (number >= 0 and number < nodes.size()) {
        // iterator to the beggining of map
        auto n = nodes.begin();
        // advance interator until position number
        std::advance(n, number);

        return n->second;
    } else {
        std::cout << "Error: node id is out of range" << std::endl;
    }
}

unsigned Map::getTerritoryCount() {
    return lemon::countNodes(graph);
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // draw each territory
    for (lemon::SmartDigraph::NodeIt t(graph); t != lemon::INVALID; ++t) {
        target.draw(*territories[t], states);
    }
}
