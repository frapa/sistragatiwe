#ifndef SVG
#define SVG

#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <SFML/Graphics.hpp>
#include "triangulate.hpp"
#include "geometry.hpp"

sf::Vector2f quadraticBezier(sf::Vector2f p1,
                            sf::Vector2f p2,
                            sf::Vector2f p3,
                            double l);

sf::Vector2f cubicBezier(sf::Vector2f p1,
                       sf::Vector2f p2,
                       sf::Vector2f p3,
                       sf::Vector2f p4,
                       double l);

class SVGPath {
private:
    std::vector<sf::Vector2f> points;
    
    // create a new segment
    void lineTo(float x, float y);
    // create geom from read path
    void createGeom();
    // delete duplicate points
    void deleteDuplicates();

public:
    Geometry geom;

    SVGPath() {}
    SVGPath(std::string path) { createPath(path); }

    // parse path string
    void createPath(std::string path);
    // get number of vertices
    int pointCount() { return points.size(); }
    // get surface area
    float getArea() { return Triangulate::Area(points); }
};

#endif
