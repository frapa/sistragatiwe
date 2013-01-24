#include "../include/territory.hpp"

bool Territory::checkCollision(sf::Vector2f pos) {
    return path.geom.contains(pos);
}

void Territory::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
}
