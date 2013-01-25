#include "../include/widget.hpp"

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text, states);
}
