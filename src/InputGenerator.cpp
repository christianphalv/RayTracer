#include "../include/InputGenerator.h"

std::string generateRandomHelixInput() {

    // Initialize the input filename
    std::string filename = "generatedInput.txt";
    std::string path = "input/" + filename;

    // Open stream to output file
    std::ofstream outputFile(path, std::ios::out);

    // Write image information
    outputFile << "vfov 60" << "\n"
        //<< "imsize 7680 4320" << "\n" // Production (Takes a long time)
        //<< "imsize 1280 1024" << "\n" // Production (Takes a long time)
        << "imsize 500 500" << "\n" // Testing (Super quick)
        << "eye 0 0 0" << "\n"
        << "viewdir 0 0 1" << "\n"
        << "updir 0 1 0" << "\n"
        << "bkgcolor 0.1 0.1 0.1" << "\n";

    // Seed random number
    srand(static_cast<unsigned>(time(0)));

    // Generate each sphere
    for (int i = 0; i < 300; i++) {

        // Set a random color for the sphere
        float randMax = static_cast<float>(RAND_MAX);
        Vector3 color = Vector3(static_cast<float>(rand() / randMax), static_cast<float>(rand() / randMax), static_cast<float>(rand() / randMax));

        // Calculate Cartesian coordinates from polar coordinates
        float r = 4.0;
        float theta = degreesToRadians(20.0);
        float depth = 0.5;
        float iteration = static_cast<float>(i);
        float x = r * cos((theta * iteration) + iteration);
        float y = r * sin((theta * iteration) + iteration);
        float z = depth * iteration;

        // Initialize position from coordinates
        Vector3 position = Vector3(x, y, z);
        Vector3 position2 = Vector3(x, y, z + 1.5);

        // Output the sphere information
        outputFile << "mtlcolor " << color.getX() << " " << color.getY() << " " << color.getZ() << "\n"
            << "sphere " << position.getX() << " " << position.getY() << " " << position.getZ() << " 1" << "\n";
    }

    // Close output file
    outputFile.close();

    // Return file path
    return path;
}

std::string generateSelectColorsHelixInput() {

    // Initialize the input filename
    std::string filename = "generatedInput.txt";
    std::string path = "input/" + filename;

    // Open stream to output file
    std::ofstream outputFile(path, std::ios::out);

    // Write image information
    outputFile << "vfov 120" << "\n"
        //<< "imsize 7680 4320" << "\n" // Production (Takes a long time)
        //<< "imsize 1280 1024" << "\n" // Production (Takes a long time)
        << "imsize 500 500" << "\n" // Testing (Super quick)
        << "eye 0 0 0" << "\n"
        << "viewdir 0 0 1" << "\n"
        << "updir 0 1 0" << "\n"
        << "bkgcolor 0.1 0.1 0.1" << "\n";

    // Seed random number
    srand(static_cast<unsigned>(time(0)));

    // Define color set
    Vector3 colors[] = {hexToColor(0x444444), hexToColor(0x888888), hexToColor(0xCCCCCC), hexToColor(0xFFFFFF)};
    int colorsLenth = sizeof(colors) / sizeof(colors[0]);

    // Generate each sphere
    for (int i = 0; i < 300; i++) {

        // Set a random color for the sphere from the color set
        Vector3 color = colors[rand() % colorsLenth];

        // Calculate Cartesian coordinates from polar coordinates
        float r = 4.0;
        float theta = degreesToRadians(20.0);
        float depth = 0.5;
        float iteration = static_cast<float>(i);
        float x = r * cos((theta * iteration) + iteration);
        float y = r * sin((theta * iteration) + iteration);
        float z = depth * iteration;

        // Initialize position from coordinates
        Vector3 position = Vector3(x, y, z);
        Vector3 position2 = Vector3(x, y, z + 1.5);

        // Output the sphere information
        outputFile << "mtlcolor " << color.getX() << " " << color.getY() << " " << color.getZ() << "\n"
            << "sphere " << position.getX() << " " << position.getY() << " " << position.getZ() << " 1" << "\n";
    }

    // Close output file
    outputFile.close();

    // Return file path
    return path;
}