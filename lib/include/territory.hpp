#ifndef TERRITORY
#define TERRITORY

#include <array>
#include <string>
#include <SFML/Graphics.hpp>
#include "../../svgpathlib/include/svg.hpp"
#include "../../svgpathlib/include/shape.hpp"

class Territory: public sf::Drawable {
public:
    Geometry geom;
    Shape shape;

    Territory(std::string path)
    {
        // load path
        svg::Path p(path);
        // and create a geometry from it
        p.createGeom(geom);

        shape.createFromGeom(geom);
    }

    float getArea() { return geom.getArea(); }
    
    inline bool contains(float x, float y)
        { return geom.contains(sf::Vector2f(x, y)); }
    inline bool contains(sf::Vector2f pos)
        { return geom.contains(pos); }
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
