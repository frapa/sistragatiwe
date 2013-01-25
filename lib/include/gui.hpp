#ifndef GUI
#define GUI

#include <list>
#include <SFML/Graphics.hpp>
#include "widgets.hpp"

class Gui {
private:
    std::list<Widget*> widgets;

public:
    Gui() {}

    void addWidget(Widget& widget);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
