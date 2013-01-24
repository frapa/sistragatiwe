#ifndef LOAD_FILE
#define LOAD_FILE

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <Poco/Path.h>
#include <SFML/Graphics.hpp>
#include "territory.hpp"

// Loads a map file. Map files are simply a list
// of space separated values which tells the name of
// the territories (name is the filename of the sprite
// without extension) and the position at which they
// should be placed.
void load_map(Poco::Path path, std::vector<Territory>& ters);

#endif
