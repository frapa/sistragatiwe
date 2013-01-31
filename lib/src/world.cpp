#include "../include/world.hpp"

void World::loadMap(std::string filename) {
    // create a new xml document
    pugi::xml_document world;
    // construct it from a file
    world.load_file(filename.c_str());
    
    // load all territories from the file
    for (pugi::xml_node territory: world.child("map").children("territory"))
    {
        // add territory to map, using document data
        map.addTerritory(territory.attribute("path").value(),
            territory.attribute("name").value());
    }
    
    // create roads between territories
    for (pugi::xml_node territory: world.child("map").children("territory"))
    {
        for (pugi::xml_node link: territory.children("link")) {
            Node from = map.getTerritoryByName(
                territory.attribute("name").value());
            Node to = map.getTerritoryByName(
                link.attribute("to").value());

            map.addRoad(from, to, link.attribute("length").as_float());
        }
    }
}

void World::createPlayers(int humans, int bots) {
    // create players
    players.emplace(players.end(), true, "Human", sf::Color::Red);

    // create a random number generator
    std::mt19937 gen(time(NULL));
    std::uniform_int_distribution<int> dist(0, map.getTerritoryCount() - 1);

    // randomly assign a territory to start with to each player
    std::vector<int> nums;
    for (Player& player: players) {
        int number;

        // get a number (and check if the corresponding territory
        // has already been assigned to another player)
        do {
            number = dist(gen);
        } while (std::find(nums.begin(), nums.end(), number) != nums.end());

        Node terr = map.getTerritoryByNumber(number);

        // assign territory to player
        player.addTerritory(terr);
        // set the color of the territory
        map.territories[terr]->shape.setFillColor(player.color);

        nums.push_back(number);
    }
}

void World::loadFonts() {
    gui.loadFont("resources/fonts/Kavoon.ttf");
}

void World::createGui() {
    loadFonts();

    Label label(gui.getFont("Kavoon"), "0123456789",
        sf::Vector2f(10, 10), 16);

    MainPanel panel(window);

    gui.addWidget(label);
    gui.addWidget(panel);
}
