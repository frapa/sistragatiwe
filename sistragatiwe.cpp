#include <iostream>
#include <SFML/Graphics.hpp>
#include "lib/include/world.hpp"
#include "lib/include/logic.hpp"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Sistragatiwe");
	window.setFramerateLimit(30);

    World world("resources/maps/test/test.xml");
    
    // not that eveything is initialized start the
    // game logic loop
    sf::Thread logic_thread(&logic, &world);
    logic_thread.launch();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			} else if (event.type == sf::Event::MouseButtonReleased) {
                sf::Vector2i pos = sf::Mouse::getPosition(window);

                sf::Vector2f v = window.mapPixelToCoords(pos);
                std::cout << v.x << " " << v.y << std::endl;
            }
		}

		window.clear(sf::Color(25, 130, 225));

        window.draw(world.map);

		window.display();
	}

    logic_thread.terminate();

	return 0;
}
