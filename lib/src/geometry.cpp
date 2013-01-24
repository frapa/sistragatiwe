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
