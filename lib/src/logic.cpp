#include "../include/world.hpp"

/*
 * This file contains the main part of the game: the game logic.
 * I put it in a separate file, for avoiding to much of confusion,
 * and huge files.
 */

void World::gameLogic() {
    sf::Clock clock;
    sf::Time interval;

    while (true) {
        while (!events.empty()) {
            EventMessage message(events.front());
            message.send();

            events.pop();
        }

        // update resources 
        for (Player& player: players) {
            for (Node t: player.territories) {
                player.food += (map.area[t] / 50) * interval.asSeconds();
            }

            // send a message telling that resources have been updated
            ResMessage message(player);
            mutex.lock();
            message.send();
            mutex.unlock();
        }
        
        sf::sleep(sf::seconds(1));
        interval = clock.getElapsedTime();
        clock.restart();
    }
}
