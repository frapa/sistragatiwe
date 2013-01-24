#include "../include/load_file.hpp"

// Loads a map file. Map files are simply a list
// of space separated values which tells the name of
// the territories (name is the filename of the sprite
// without extension) and the position at which they
// should be placed.
void load_map(Poco::Path path, std::vector<Territory>& ters) {
	// open file for reading in text mode
    Poco::Path file_path(path, "map.txt");
	std::ifstream file(file_path.toString().c_str());

	// read version of the file, which is a number
    // placed at the beginning of the file
	int version;
	file >> version;

	// make sure version number is correct
	if (version == 1) {
		// variables used to store the data. 
		std::string name;
		float x, y;

		// loop through the file reading the content
		while (file >> name) {
            // read territory position
			file >> x >> y;

            // create and save a territory object
            ters.push_back(Territory(name, x, y));
		}
	}

    // create path pointing to the images' directory
    Poco::Path images_path(path, "images");

    // now load the images associated with the territories
    for (Territory& ter: ters) {
        // path corresponding to territory image file
        Poco::Path texture_path(images_path, ter.name + ".png");

        // load image into graphic memory
        ter.loadTexture(texture_path.absolute().toString());
    }
}

