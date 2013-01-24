#include "../include/territory.hpp"

void Territory::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(shape, states);
}
