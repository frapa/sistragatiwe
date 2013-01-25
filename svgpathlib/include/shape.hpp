#ifndef SHAPE
#define SHAPE

#include <SFML/Graphics.hpp>
#include "../include/geometry.hpp"

class Shape: public sf::Drawable {
private:
    sf::VertexArray vertices;
    sf::VertexArray outline;

    bool draw_outline;
    float outline_thickness;
    sf::Color outline_color;

    bool draw_fill; // shall I fill the polygon?
    sf::Color fill_color;

public:
    Shape():
        draw_fill(true), draw_outline(true),
        outline_thickness(1.f),
        outline_color(255, 255, 255, 255),
        fill_color(150, 150, 150, 255)
    {
        vertices.setPrimitiveType(sf::Triangles);
        outline.setPrimitiveType(sf::LinesStrip);
    }

    Shape(Geometry& geom):
        vertices(sf::Triangles, geom.faces.size() * 3),
        outline(sf::LinesStrip, geom.vertices.size() + 1),
        draw_fill(true), draw_outline(true),
        outline_thickness(1.f),
        outline_color(255, 255, 255, 255),
        fill_color(150, 150, 150, 255)
    {
        createFromGeom(geom);
    }

    void createFromGeom(Geometry& geom);

    void setFillColor(sf::Color& color);
    void setOutlineColor(sf::Color& color);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
