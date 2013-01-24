#ifndef TERRITORY
#define TERRITORY

#include <array>
#include <string>
#include <SFML/Graphics.hpp>
#include "svg.hpp"
#include "shape.hpp"

class Territory: public sf::Drawable {
private:
    SVGPath path;
    Shape shape;

    bool checkCollision(sf::Vector2f);

public:
    Territory(std::string _path):
        path(_path),
        shape(path.geom)
    {}

    float getArea() { return path.getArea(); }
    
    inline bool contains(float x, float y) { return checkCollision(sf::Vector2f(x, y)); }
    inline bool contains(sf::Vector2f pos) { return checkCollision(pos); }
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
