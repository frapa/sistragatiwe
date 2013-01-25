#ifndef WIDGETS
#define WIDGETS

#include <string>
#include <SFML/Graphics.hpp>

class Widget: public sf::Drawable {

};

class Label: public Widget {
private:
    sf::Text text;

public:
    Label(sf::Font& _font, std::string _text, sf::Vector2f pos):
        text(_text, _font)
    {
        text.setPosition(pos);
    }

    void setText(std::string _text)
        { text = _text; }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void clone();
}

#endif
