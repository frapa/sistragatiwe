#include "../include/shape.hpp"

void Shape::createFromGeom(Geometry& geom) {
    if (vertices.getVertexCount() != geom.faces.size() * 3) {
        vertices.resize(geom.faces.size() * 3);
    }

    if (outline.getVertexCount() != geom.vertices.size()) {
        outline.resize(geom.vertices.size() + 1);
    }

    int i = 0;
        for (Face& face: geom.faces) {
            vertices[i].position = face[0];
            vertices[i].color = fill_color;

            vertices[i + 1].position = face[1];
            vertices[i + 1].color = fill_color;

            vertices[i + 2].position = face[2];
            vertices[i + 2].color = fill_color;

            i += 3;
        }

        int j = 0;
        for (sf::Vector2f& point: geom.vertices) {
            outline[j].position = point;
            outline[j].color = outline_color;

            ++j;
        }

        outline[j].position = geom.vertices[0];
        outline[j].color = outline_color;
}

void Shape::setFillColor(sf::Color& color) {
    fill_color = color;
    
    for (int i = 0; i != vertices.getVertexCount() + 1; ++i) {
        vertices[i].color = fill_color;
    }
}

void Shape::setOutlineColor(sf::Color& color) {
    outline_color = color;

    for (int i = 0; i != outline.getVertexCount() + 1; ++i) {
        outline[i].color = outline_color;
    }
}

void Shape::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (draw_fill) {
        target.draw(vertices, states);
    }

    if (draw_outline) {
        target.draw(outline, states);
    }
}
