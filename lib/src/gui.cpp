#include "../include/gui.hpp"

void Gui::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::View view = target.getView();

    sf::View new_view = target.getView();
    new_view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
    target.setView(new_view);
        
    for (Widget* widget: widgets) {
        target.draw(*widget, states);
    }

    target.setView(view);
}

void Gui::addWidget(Widget& widget) {
    widgets.push_back(widget.clone());
}

void Gui::loadFont(std::string font_path) {
    Poco::Path path(font_path);
    std::string name(path.getBaseName());

    fonts[name] = sf::Font();

    if (!fonts[name].loadFromFile(font_path)) {
        std::cout << "Problem while loading font" << std::endl;    
    }
}

sf::Font& Gui::getFont(std::string font_name) {
    return fonts[font_name];
}
