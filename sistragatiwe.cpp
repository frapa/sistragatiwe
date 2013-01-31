#include <iostream>
#include <SFML/Graphics.hpp>
#include "lib/include/world.hpp"
#include "lib/include/message.hpp"
#include "lib/include/message_spec.hpp"

sf::Mutex mutex;

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Sistragatiwe");
	window.setFramerateLimit(30);

    World world(window, "resources/maps/test/test.xml");
    
    // not that eveything is initialized start the
    // game logic loop
    sf::Thread logic_thread(&World::gameLogic, &world);
    logic_thread.launch();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			} else if (event.type == sf::Event::Resized) {
                sf::View view(window.getView());
                view.setSize(event.size.width, event.size.height);

                window.setView(view);
            } else if (event.type == sf::Event::MouseButtonReleased) {
                sf::Vector2i pos = sf::Mouse::getPosition(window);

                sf::Vector2f v = window.mapPixelToCoords(pos);
            }
            
            mutex.lock();
            world.events.push(event);
            mutex.unlock();
		}

        mutex.lock();

		window.clear(sf::Color(25, 130, 225));

        window.draw(world.map);
        window.draw(world.gui);

		window.display();

        mutex.unlock();
	}

    logic_thread.terminate();

	return 0;
}
