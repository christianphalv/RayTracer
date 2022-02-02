#include "../include/header.h"


int main(int argc, char *argv[]) {

    // Declare input file name
    std::string inputFileName;

    // Parse arguments
    if (argc == 2) {
        inputFileName = argv[1];
    } else {
        printf("ERROR: Invalid arguments.\n");
        return 0;
    }

    // Initialize new scene from input file
    Scene* scene = new Scene(inputFileName);

    // Print info of each object in scene (FOR DEBUGGING)
    for (int i = 0; i < scene->getObjects().size(); i++) {
        scene->getObjects()[i]->info();
    }

    // Instantiate image
    Image image = Image(scene->getImageWidth(), scene->getImageHeight());


    for (int i = 0; i < image.getWidth(); i++) {
        for (int j = 0; j < image.getHeight(); j++) {

            Vector3 color = Vector3((static_cast<float>(i)) / (static_cast<float>(image.getWidth())), (static_cast<float>(j)) / (static_cast<float>(image.getHeight())), 0);
            image.setPixel(i, j, color);
        }
    }

    // Generate PPM file
    image.generatePPM("test");

    return 0;
}

Vector3 traceRay(Ray ray, Scene scene) {

}