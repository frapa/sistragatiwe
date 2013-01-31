#include "../include/widgets.hpp"

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text, states);
}

Widget* Label::clone() {
    return new Label(*this);
}

void Label::onMessage(ResMessage& message) {
    if (message.player.is_human) {
        setText(std::to_string(message.player.food));
    }
}

void MainPanel::draw(sf::RenderTarget& target, sf::RenderStates states)
    const
{
    target.draw(rectangle, states);
}

Widget* MainPanel::clone() {
    return new MainPanel(*this);
}

void MainPanel::onMessage(EventMessage& message) {
    if (message.event.type == sf::Event::Resized) {
        rectangle.setSize(
            sf::Vector2f(width, message.event.size.height));
        rectangle.setPosition(
            sf::Vector2f(message.event.size.width - width, 0));
    }
}
