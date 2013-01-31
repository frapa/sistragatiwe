#ifndef WIDGETS
#define WIDGETS

#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "message.hpp"
#include "message_spec.hpp"

class Widget: public sf::Drawable {
public:
    Widget() {}

    // This enables the copy of a vector of pointers
    // to subclasses of Widget. It keeps the polymorfism. 
    virtual Widget* clone() {}
};

class Label: public Widget, public Receiver<ResMessage> {
private:
    sf::Text text;

public:
    Label(sf::Font& font, std::string _text, sf::Vector2f pos, int size):
        text(_text, font, size)
    {
        text.setPosition(pos);
    }

    Label(Label& label):
        text(label.text.getString(), *label.text.getFont(),
            label.text.getCharacterSize())
    {
        text.setPosition(label.text.getPosition());
    }

    void setText(std::string _text)
        { text.setString(_text); }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual Widget* clone();
    virtual void onMessage(ResMessage& message);
};

// specific to sistragatiwe
class MainPanel: public Widget, public Receiver<EventMessage> {
private:
    sf::RectangleShape rectangle;
    int width;

public:
    MainPanel(sf::RenderWindow& window):
        width(200)
    {
        rectangle.setSize(sf::Vector2f(width, window.getSize().y));
        rectangle.setPosition(sf::Vector2f(window.getSize().x - width, 0));
    }

    MainPanel(MainPanel& panel) {
        rectangle.setSize(panel.rectangle.getSize());
        rectangle.setPosition(panel.rectangle.getPosition());
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual Widget* clone();
    virtual void onMessage(EventMessage& message);
};

#endif
