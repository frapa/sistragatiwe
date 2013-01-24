#include "../include/svg.hpp"

namespace svg {
    std::string valid_commands = "MmZzLlHhVvCcSs";
    int cubic_bezier_count = 10;
    int quadratic_bezier_count = 6;

    void Path::createPath(std::string path) {
        // vector of strings containing all the
        // commands to be executed and the data
        // to be used (coordinated of points)
        std::vector<char> commands;
        std::vector<std::string> data;

        // Parse the path string and get commands
        // and data. A path command is a string like
        // "M 100 100 L 200 200". Letters are commands
        // and numbers are data. We split the path string
        // into letters (commands) and data (the rest)
        // paying attention not to add useless letters
        // (such as commas which are sometimes used as
        // separator), since we want to use a stream to
        // separate data afterwards.
        std::string current = ""; // store current data
        for (char c: path) {
            // if the character is a letter it is a command 
            if (isalpha(c)) {
                // save the command
                commands.push_back(c);
                // save the data
                data.push_back(current);
                 
                // clear current data
                current = "";
            // if the character is a number, a whitespace character,
            // a dot or a minus sign add it to the data string
            } else if (isdigit(c) or isspace(c) or c == '.' or c == '-') {
                current += c;
            // in other cases (such as commas), add a space instead,
            // thus easying the use of a standard stream to separate
            // and convert data to floats.
            } else {
                current += " ";
            }
        }
        
        // array which will contain the data
        std::vector<std::vector<float>> float_data(commands.size());

        // convert data to float
        int i = 0;
        for (std::string& str: data) {
            std::stringstream stream(str);
            float value;
            
            // fix for the first value
            if (i == 0 and str == "") continue;

            while (stream >> value) {
                float_data[i].push_back(value);
            }
            
            ++i;
        }

        // set up the drawing environment
        float x = 0, y = 0; // where is the pen?
        
        // execute svg path commands creating a geom
        for (int i = 0; i != commands.size();  ++i) {
            // check if command if suported by this implementation,
            // if not, just do nothing
            if (valid_commands.find(commands[i]) != std::string::npos) {
                // find out which command has to be executed
                if (commands[i] == 'M') {
                    // move pen to coordinates
                    x = float_data[i][0];
                    y = float_data[i][1];

                    lineTo(x, y);

                    for (int j = 2; j != float_data[i].size(); j += 2) {
                        x = float_data[i][j];
                        y = float_data[i][j + 1];

                        lineTo(x, y);
                    }
                } else if (commands[i] == 'm') {
                    // move pen a bit, relative to the last position
                    x += float_data[i][0];
                    y += float_data[i][1];

                    lineTo(x, y);
                    
                    for (int j = 2; j != float_data[i].size(); j += 2) {
                        x += float_data[i][j];
                        y += float_data[i][j + 1];
                        
                        lineTo(x, y);
                    }
                } else if (commands[i] == 'Z' or commands[i] == 'z') {
                    ;
                } else if (commands[i] == 'L') {
                    for (int j = 0; j != float_data[i].size(); j += 2) {
                        x = float_data[i][j];
                        y = float_data[i][j + 1];

                        lineTo(x, y);
                    }
                } else if (commands[i] == 'l') {
                    for (int j = 0; j != float_data[i].size(); j += 2) {
                        x += float_data[i][j];
                        y += float_data[i][j + 1];

                        lineTo(x, y);
                    }
                } else if (commands[i] == 'H') {
                    for (int j = 0; j != float_data[i].size(); ++j) {
                        x = float_data[i][j];

                        lineTo(x, y);
                    }
                } else if (commands[i] == 'h') {
                    for (int j = 0; j != float_data[i].size(); ++j) {
                        x += float_data[i][j];

                        lineTo(x, y);
                    }
                } else if (commands[i] == 'V') {
                    for (int j = 0; j != float_data[i].size(); ++j) {
                        y = float_data[i][j];

                        lineTo(x, y);
                    }
                } else if (commands[i] == 'v') {
                    for (int j = 0; j != float_data[i].size(); ++j) {
                        y += float_data[i][j];

                        lineTo(x, y);
                    }
                // Cubic bezier curve, absolute coordinates
                } else if (commands[i] == 'C') {
                    for (int j = 0; j != float_data[i].size(); j += 6) {
                        // get coordinates of the control points
                        sf::Vector2f p1(x, y);
                        sf::Vector2f p2(float_data[i][j], float_data[i][j + 1]);
                        sf::Vector2f p3(float_data[i][j + 2], float_data[i][j + 3]);
                        sf::Vector2f p4(float_data[i][j + 4], float_data[i][j + 5]);
                        
                        for (int k = 1; k != cubic_bezier_count + 1; ++k) {
                            sf::Vector2f pos(cubicBezier(p1, p2, p3, p4,
                                1.f / cubic_bezier_count * k));
                            lineTo(pos.x, pos.y);
                        }

                        x = p4.x;
                        y = p4.y;
                    }
                // cubic bezier curve, relative coordinates
                } else if (commands[i] == 'c') {
                    for (int j = 0; j != float_data[i].size(); j += 6) {
                        // get absolute coordinates of control points
                        sf::Vector2f p1(x, y);
                        sf::Vector2f p2 = p1 +
                            sf::Vector2f(float_data[i][j], float_data[i][j + 1]);
                        sf::Vector2f p3 = p1 +
                            sf::Vector2f(float_data[i][j + 2], float_data[i][j + 3]);
                        sf::Vector2f p4 = p1 +
                            sf::Vector2f(float_data[i][j + 4], float_data[i][j + 5]);

                        for (int k = 1; k != cubic_bezier_count + 1; ++k) {
                            sf::Vector2f pos(cubicBezier(p1, p2, p3, p4,
                                1.f / cubic_bezier_count * k));
                            lineTo(pos.x, pos.y);
                        }

                        x = p4.x;
                        y = p4.y;
                    }
                /// DOES NOT WORK
                } else if (commands[i] == 'Q') {
                    for (int j = 0; j != float_data[i].size(); j += 4) { 
                        sf::Vector2f p1(x, y);
                        sf::Vector2f p2(float_data[i][j], float_data[i][j + 1]);
                        sf::Vector2f p3(float_data[i][j + 2], float_data[i][j + 3]);

                        for (int k = 1; k != quadratic_bezier_count + 1; ++k) {
                            sf::Vector2f pos(quadraticBezier(p1, p2, p3,
                                1.f / quadratic_bezier_count * k));
                            lineTo(pos.x, pos.y);
                        }

                        x = p3.x;
                        y = p3.y;
                    }
                } else if (commands[i] == 'q') {
                    for (int j = 0; j != float_data[i].size(); j += 4) { 
                        sf::Vector2f p1(x, y);
                        sf::Vector2f p2 = p1 +
                            sf::Vector2f(float_data[i][j], float_data[i][j + 1]);
                        sf::Vector2f p3 = p1 +
                            sf::Vector2f(float_data[i][j + 2], float_data[i][j + 3]);

                        for (int k = 1; k != quadratic_bezier_count + 1; ++k) {
                            sf::Vector2f pos(quadraticBezier(p1, p2, p3,
                                1.f / quadratic_bezier_count * k));
                            lineTo(pos.x, pos.y);
                        }

                        x = p3.x;
                        y = p3.y;
                    }
                }
                // GOES BACK WORKING
            }
        }

        // delete duplicate points
        deleteDuplicates();
    }

    void Path::lineTo(float x, float y) {
        points.push_back(sf::Vector2f(x, y));
    }

    void Path::deleteDuplicates() {
        // copy points to temporary vector
        std::vector<sf::Vector2f> copy(points);
        // clear points vector (stupid comment I know)
        points.clear();
        
        for (auto point = copy.begin(); point != copy.end(); ++point) {
            if (std::find(points.begin(), points.end(), *point) == points.end()) {
                points.push_back(*point);
            }
        }
    }

    void Path::createGeom(Geometry& geom) {
        // clear geom from previous data
        geom.clear();

        // add vertices to the geom
        for (sf::Vector2f& p: points) {
            geom.addVertex(p);
        }

        // triangulate polygon (only with no holes)
        std::vector<sf::Vector2f> triangles;

        Triangulate::Process(points, triangles);

        for (int i = 0; i != triangles.size(); i += 3) {
            geom.addFace(triangles[i], triangles[i + 1], triangles[i + 2]);
        }
    }

    sf::Vector2f quadraticBezier(sf::Vector2f p1,
                                sf::Vector2f p2,
                                sf::Vector2f p3,
                                double l)
    {
        double t = 1 - l;
        double tt = t * t;
        double ll = l * l;

        sf::Vector2f result;
        result.x = p1.x * tt + p2.x * 2 * t * l + p3.x * ll;
        result.y = p1.y * tt + p2.y * 2 * t * l + p3.y * ll;

        return result;
    }

    sf::Vector2f cubicBezier(sf::Vector2f p1,
                           sf::Vector2f p2,
                           sf::Vector2f p3,
                           sf::Vector2f p4,
                           double l)
    {
        double t = 1 - l;
        double tt = t * t;
        double ttt = tt * t;
        double ll = l * l;
        double lll = ll * l;

        sf::Vector2f result;
        result.x = p1.x * ttt + p2.x * 3 * tt * l + p3.x * 3 * t * ll + p4.x * lll;
        result.y = p1.y * ttt + p2.y * 3 * tt * l + p3.y * 3 * t * ll + p4.y * lll;

        return result;
    }
}
