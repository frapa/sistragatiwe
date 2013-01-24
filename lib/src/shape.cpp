#include "../include/shape.hpp"

void Shape::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (draw_fill) {
        target.draw(vertices, states);
    }

    if (draw_outline) {
        target.draw(outline, states);
    }
}
