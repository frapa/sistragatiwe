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
    Shape(Geometry& geom):
        vertices(sf::Triangles, geom.faces.size() * 3),
        outline(sf::LinesStrip, geom.vertices.size()),
        draw_fill(true), draw_outline(true),
        outline_thickness(1.f),
        outline_color(255, 255, 255, 255),
        fill_color(150, 150, 150, 255)
    {
        int i = 0;
        for (Face& face: geom.faces) {
            vertices[i].position = face[0];
            vertices[i].color = fill_color;
            vertices[i].texCoords = sf::Vector2f(vertices[i].position);

            vertices[i + 1].position = face[1];
            vertices[i + 1].color = fill_color;
            vertices[i + 1].texCoords = sf::Vector2f(vertices[i + 1].position);

            vertices[i + 2].position = face[2];
            vertices[i + 2].color = fill_color;
            vertices[i + 2].texCoords = sf::Vector2f(vertices[i + 2].position);

            i += 3;
        }

        int j = 0;
        for (sf::Vector2f& point: geom.vertices) {
            outline[j].position = point;
            outline[j].color = outline_color;

            ++j;
        }
    }

    void setFillColor(sf::Color& color);
    void setOutlineColor(sf::Color& color);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
