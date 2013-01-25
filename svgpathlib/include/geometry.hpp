#ifndef GEOMETRY
#define GEOMETRY

#include <vector>
#include <array>
#include <algorithm>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "triangulate.hpp"

typedef std::array<sf::Vector2f, 3> Face;

class Geometry {
public:
    std::vector<sf::Vector2f> vertices;
    std::vector<Face> faces;

    Geometry() {}
    Geometry(int vertex_num):
        vertices(vertex_num)
    {}

    // add a vertex
    void addVertex(sf::Vector2f vertex);
    // add a face
    void addFace(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c);
    // clear content
    void clear();

    // geometries can be added up by summing the triangles and vertices
    Geometry operator+ (const Geometry& geom);
    Geometry& operator+= (const Geometry& geom);

    // check if the geometry contains a point
    bool contains(sf::Vector2f point);
    // returns the area of the geometry
    float getArea();
};

#endif
