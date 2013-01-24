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

namespace svg {
    // Returns a point along a quadratic bezier curve.
    // p1, p2, p3 are the control points, while
    // l is a parameter which tells where the point is
    // along the curve (0 is one end, 1 the other)
    sf::Vector2f quadraticBezier(sf::Vector2f p1,
                                sf::Vector2f p2,
                                sf::Vector2f p3,
                                double l);

    // Returns a point alog a cubic bezier curve.
    // p1, p2, p3 and p4 are the control points, while
    // l is a parameter which tells where the point is
    // along the curve (0 is one end, 1 the other)
    sf::Vector2f cubicBezier(sf::Vector2f p1,
                           sf::Vector2f p2,
                           sf::Vector2f p3,
                           sf::Vector2f p4,
                           double l);

    class Path {
    private:
        std::vector<sf::Vector2f> points;
        
        // create a new segment
        void lineTo(float x, float y);
        // delete duplicate points
        void deleteDuplicates();

    public:
        Path() {}
        Path(std::string path) { createPath(path); }

        // parse path string
        void createPath(std::string path);
        // create geom from read path
        void createGeom(Geometry& geom);
    };
}

#endif
