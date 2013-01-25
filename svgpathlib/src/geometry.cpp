#include "../include/geometry.hpp"

// add vertex checking if it is already in the geometry
void Geometry::addVertex(sf::Vector2f vertex) {
    if (std::find(vertices.begin(), vertices.end(), vertex) == vertices.end()) {
        vertices.push_back(vertex);
    }
}

void Geometry::addFace(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c) {
    Face face = {a, b, c};

    faces.push_back(face);
}

void Geometry::clear() {
    vertices.clear();
    faces.clear();
}

Geometry Geometry::operator+ (const Geometry& geom) {
    // create a copy of itself
    Geometry new_geom(*this);

    new_geom += geom;

    return new_geom;
}

Geometry& Geometry::operator+= (const Geometry& geom) {
    for (const sf::Vector2f& vertex: geom.vertices) {
        addVertex(vertex);
    }

    for (const Face& face: geom.faces) {
        addFace(face[0], face[1], face[2]);
    }

    return *this;
}

bool Geometry::contains(sf::Vector2f point) {
    for (Face& face: faces) {
        if (Triangulate::InsideTriangle(
                face[0].x, face[0].y,
                face[1].x, face[1].y,
                face[2].x, face[2].y,
                point.x, point.y
            ))
        {
            return true;
        }
    }

    return false;
}

float Geometry::getArea() {
    return abs(Triangulate::Area(vertices));
}
