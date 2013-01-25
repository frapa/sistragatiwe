#include "../include/gui.hpp"

void Gui::draw(sf::RenderTarget& target, sf::RenderStates states) {
    for (Widget* widget: widgets) {
        target.draw(*widget, states);
    }
}

void Gui::addWidget(Widget& widget) {
    widgets.push_back(&widget);
}
