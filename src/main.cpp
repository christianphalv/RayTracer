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

    // Extract camera from scene
    Camera cam = scene->getCamera();

    // Calculate h and w
    float d = 1;
    float h = 2 * d * tan(scene->getVerticalFov() / 2.0);
    float w = 2 * d * tan(scene->getHorizontalFov() / 2.0);

    // Calculate the four corners of the viewing window
    Vector3 ul = cam.getEye() + (d * cam.getViewDirection()) - (w / 2.0) * cam.getU() + (h / 2.0) * cam.getV();
    Vector3 ur = cam.getEye() + (d * cam.getViewDirection()) + (w / 2.0) * cam.getU() + (h / 2.0) * cam.getV();
    Vector3 ll = cam.getEye() + (d * cam.getViewDirection()) - (w / 2.0) * cam.getU() - (h / 2.0) * cam.getV();
    Vector3 lr = cam.getEye() + (d * cam.getViewDirection()) + (w / 2.0) * cam.getU() - (h / 2.0) * cam.getV();

    // Calculate pixel-ray offsets
    Vector3 dh = (ur - ul) / (image.getWidth() - 1);
    Vector3 dv = (ll - ul) / (image.getHeight() - 1);


    for (int i = 0; i < image.getWidth(); i++) {
        for (int j = 0; j < image.getHeight(); j++) {

            // Calculate pixel-ray
            Vector3 pixelPoint = ul + (dh * static_cast<float>(i)) + (dv * static_cast<float>(j));
            Vector3 rayDirection = pixelPoint - cam.getEye();
            Ray ray = Ray(cam.getEye(), rayDirection);

            traceRay(ray, scene);

            Vector3 color = traceRay(ray, scene);
            image.setPixel(i, j, color);
        }
    }

    // Generate PPM file
    image.generatePPM("test");

    return 0;
}

Vector3 traceRay(Ray ray, Scene* scene) {

    // Initialize nearest object storage
    float nearestTime = 100000;
    Object* nearestObject = NULL;

    // Loop through each object in the scene
    for (int i = 0; i < scene->getObjects().size(); i++) {

        // Check ray-object intersection
        float time;
        if (scene->getObjects()[i]->rayIntersect(ray, time)) {

            // Check if nearest object so far
            if (time < nearestTime) {

                // Update nearest object
                nearestTime = time;
                nearestObject = scene->getObjects()[i];
            }
        }
    }

    // Return nearest object color
    if (nearestObject) {
        return nearestObject->getColor();
    }

    // Return background color if no objects intersected
    return scene->getBackgroundColor();
}