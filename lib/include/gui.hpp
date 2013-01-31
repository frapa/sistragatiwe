#ifndef GUI
#define GUI

#include <list>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <Poco/Path.h>
#include "message.hpp"
#include "widgets.hpp"

class Gui: public sf::Drawable {
private:
    std::list<Widget*> widgets;
    std::map<std::string, sf::Font> fonts;

public:
    Gui() {}

    void addWidget(Widget& widget);

    // font management
    void loadFont(std::string font_path);
    sf::Font& getFont(std::string font_name);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
