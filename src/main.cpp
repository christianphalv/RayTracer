#include "../include/header.h"


int main(int argc, char *argv[]) {

    // Declare input file name
    std::string inputFileName;

    // Parse arguments
    if (argc == 1) {
        inputFileName = generateSelectColorsHelixInput();
    } else if (argc == 2) {
        inputFileName = argv[1];
    } else {
        printf("ERROR: Invalid arguments.\n");
        return 0;
    }

    // Initialize new scene from input file
    Scene* scene = new Scene(inputFileName);

    // for (int i = 0; i < scene->getObjects().size(); i++) {
    //     scene->getObjects()[i]->info();
    // }

    // Instantiate image
    Image image = Image(scene->getImageWidth(), scene->getImageHeight());

    // Extract camera from scene
    Camera* cam = scene->getCamera();

    // Calculate h and w
    float d = 1.0;
    float h = 2.0 * d * tan(scene->getVerticalFov() / 2.0);
    float w = 2.0 * d * tan(scene->getHorizontalFov() / 2.0);

    // Calculate the four corners of the viewing window
    Vector3 ul = cam->getEye() + (d * cam->getViewDirection()) - (w / 2.0) * cam->getU() + (h / 2.0) * cam->getV();
    Vector3 ur = cam->getEye() + (d * cam->getViewDirection()) + (w / 2.0) * cam->getU() + (h / 2.0) * cam->getV();
    Vector3 ll = cam->getEye() + (d * cam->getViewDirection()) - (w / 2.0) * cam->getU() - (h / 2.0) * cam->getV();
    Vector3 lr = cam->getEye() + (d * cam->getViewDirection()) + (w / 2.0) * cam->getU() - (h / 2.0) * cam->getV();

    // Calculate pixel-ray offsets
    Vector3 dh = (ur - ul) / (image.getWidth() - 1);
    Vector3 dv = (ll - ul) / (image.getHeight() - 1);

    // Time raytracer
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < image.getWidth(); i++) {
        for (int j = 0; j < image.getHeight(); j++) {

            // Calculate pixel-ray
            Vector3 pixelPoint = ul + (dh * static_cast<float>(i)) + (dv * static_cast<float>(j));
            Vector3 rayDirection = pixelPoint - cam->getEye();
            Ray ray = Ray(cam->getEye(), rayDirection);

            // 
            //std::cout << i << " " << j << "\n";
            //std::cout << "BEFORE\n";
            image.setPixel(i, j, scene->traceRay(ray));
            //std::cout << "After\n";

            // // Trace ray for object intersections
            // float time;
            // Object* object;
            // if (scene->traceRay(ray, 0, INFINITY, time, object)) {

            //     // Set pixel to shaded intersection point
            //     Vector3 color = scene->shadeRay(ray, ray.calculatePoint(time), object);
            //     image.setPixel(i, j, color);

            // } else {

            //     // Set pixel to background color if no intersecion
            //     image.setPixel(i, j, scene->getBackgroundColor());
            // }

        }

        // Display progress
        //std::cout << "\r" << static_cast<int>(static_cast<float>(i) / static_cast<float>(image.getWidth()) * 100) << "%";
    }

    // Display 100%
    std::cout << "\r" << "100%" << "\n";

    // Print raytracer time
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << duration.count() << " milleseconds" << "\n";

    // Remove extension from input file
    std::string outputFileName;
    size_t extensionPoint = inputFileName.find_last_of(".");
    if (extensionPoint == std::string::npos) {
        outputFileName = inputFileName;
    } else {
        outputFileName = inputFileName.substr(0, extensionPoint);
    }

    // Remove path from input file
    extensionPoint = outputFileName.find_last_of("/");
    if (extensionPoint != std::string::npos) {
        outputFileName = outputFileName.substr(extensionPoint + 1);
    }

    // Add output folder to output path
    outputFileName = "output/" + outputFileName;

    // Generate PPM file
    image.generatePPM(outputFileName);

    return 0;
}