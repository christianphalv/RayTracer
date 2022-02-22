#include "../include/Scene.h"

Scene::Scene(std::string inputFilename) {

    // Default settings
    float min = -10000;
    float max = 10000;
    this->material = new Material();

    // Default camera variables
    Vector3 eye = Vector3(0, 0, 0);
    Vector3 viewDir = Vector3(1, 0, 0);
    Vector3 upDir = Vector3(0, 1, 0);

    // Setup polygon objects
    std::vector<Vector3*> vertices;
    std::vector<Vector3*> indices;
    std::vector<Material*> triangleMats;

    // Open stream to input file
    std::ifstream inputFile(inputFilename, std::ios::in | std::ios::binary);

    // Read each line of the input file
    std::string line;
    while (std::getline(inputFile, line)) {

        // Stream each line deliminating by spaces
        std::istringstream iss(line);
        //iss.exceptions(std::ios::failbit); // GIVES NEW LINE ERROR

        // Stream keywork
        std::string keyword;
        iss >> keyword;

        // Stream rest of line based on keyword
        if (keyword.compare("eye") == 0) {
            eye = safeStreamVector3(iss, min, max);

        } else if (keyword.compare("viewdir") == 0) {
            viewDir = safeStreamVector3(iss, min, max);

        } else if (keyword.compare("updir") == 0) {
            upDir = safeStreamVector3(iss, min, max);

        } else if (keyword.compare("vfov") == 0) {
            this->vfov = MathUtils::degreesToRadians(safeStreamFloat(iss, 0, 180));

        } else if (keyword.compare("imsize") == 0) {
            this->imageWidth = safeStreamInt(iss, 0, max);
            this->imageHeight = safeStreamInt(iss, 0, max);

        } else if (keyword.compare("bkgcolor") == 0) {
            this->bkgColor = safeStreamVector3(iss, 0, 1);

        } else if (keyword.compare("mtlcolor") == 0) {
            Vector3 mtlAlbedo = safeStreamVector3(iss, 0, 1);
            Vector3 mtlSpecular = safeStreamVector3(iss, 0, 1);
            Vector3 mtlK = safeStreamVector3(iss, 0, 1);
            float mtlN = safeStreamFloat(iss, 0, max);
            this->material = new Material(mtlAlbedo, mtlSpecular, mtlK, mtlN);

        } else if (keyword.compare("sphere") == 0) {
            Vector3 position = safeStreamVector3(iss, min, max);
            float radius = safeStreamFloat(iss, min, max);
            this->objects.push_back(new Sphere(this->material, position, radius));

        } else if (keyword.compare("plane") == 0) {
            Vector3 normal = safeStreamVector3(iss, min, max);
            Vector3 vertex = safeStreamVector3(iss, min, max);
            this->objects.push_back(new Plane(this->material, normal, vertex));

        } else if (keyword.compare("v") == 0) {
            Vector3 v = safeStreamVector3(iss, min, max);
            vertices.push_back(new Vector3(v.getX(), v.getY(), v.getZ()));

        } else if (keyword.compare("f") == 0) {
            Vector3 f = safeStreamVector3(iss, min, max);
            indices.push_back(new Vector3(f.getX(), f.getY(), f.getZ()));
            triangleMats.push_back(this->material);

        } else if (keyword.compare("light") == 0) {
            Vector3 source = safeStreamVector3(iss, min, max);
            float w = safeStreamFloat(iss, 0.0, 1.0);
            Vector3 hue = safeStreamVector3(iss, 0.0, max);

            if (w == 0) {
                this->lights.push_back(new DirectionalLight(source, hue));
            } else if (w > 0 && w <= 1) {
                this->lights.push_back(new PointLight(source, hue));
            } else {
                std::cout << "Error: Invalid w value for light. Must be in range 0-1. \n";
                exit(0);
            }

        } else if (keyword.compare("attlight") == 0) {
            Vector3 source = safeStreamVector3(iss, min, max);
            float w = safeStreamFloat(iss, 0.0, 1.0);
            Vector3 hue = safeStreamVector3(iss, 0.0, max);
            Vector3 cValues = safeStreamVector3(iss, 0.0, max);
            this->lights.push_back(new AttenuationLight(source, hue, cValues));
        }
    }

    // Instantiate camera
    this->cam = new Camera(eye, viewDir, upDir);

    // Calculate horizontal fov from vertical fov and image dimensions
    this->hfov = 2.0 * atan((static_cast<float>(this->imageWidth) / static_cast<float>(this->imageHeight)) * tan(this->vfov / 2.0));

    // Instantiate triangles
    for (int i = 0; i < indices.size(); i++) {

        // Retrieve triangle indices
        int i0 = indices[i]->getX() - 1;
        int i1 = indices[i]->getY() - 1;
        int i2 = indices[i]->getZ() - 1;

        // Check if indices are valid
        if (i0 >= vertices.size() || i1 >= vertices.size() || i2 >= vertices.size()) {
            std::cout << "Error: Triangle index out of range. \n";
            exit(0);
        }

        // Retrieve triangle vertices
        Vector3 v0 = vertices[i0]->copy();
        Vector3 v1 = vertices[i1]->copy();
        Vector3 v2 = vertices[i2]->copy();

        // Retrieve triangle material
        Material* m = triangleMats[i];

        // Instantiate triangle and add to objects
        this->objects.push_back(new Triangle(m, v0, v1, v2));
    }
}

bool Scene::traceRay(Ray ray, float min, float max, float& time, Object*& object) {
    
    // Initialize nearest object storage
    time = max;
    object = NULL;

    // Loop through each object in the scene
    for (int i = 0; i < this->getObjects().size(); i++) {

        // Check ray-object intersection
        float t;
        if (this->getObjects()[i]->rayIntersect(ray, min, max, t)) {

            // Check if nearest object so far
            if (t < time) {

                // Update nearest object
                time = t;
                object = this->getObjects()[i];
            }
        }
    }

    // Return true and out point if object intersected
    if (object) {
        return true;
    }

    // Return false if no intersection
    time = -1;
    return false;
}

Vector3 Scene::shadeRay(Ray ray, Vector3 point, Object* object) {

    // Extract material
    Material* mat = object->getMaterial();

    // Calculate surface normal at intersection point
    Vector3 N = object->calculateNormal(point);

    // Initialize illumination to ambient
    Vector3 illumination = mat->getAmbient();

    // Loop through each light source
    for (int i = 0; i < this->lights.size(); i++) {

        Light* light = this->lights[i];

        // Calculate L
        Vector3 L = -this->lights[i]->sourceDirection(point).normalized();

        // Initialize shadow parameters
        Ray shadowRay = Ray(point, L);
        float shadowTime;
        Object* shadowObject;

        // Set maximum time
        float max;
        if (dynamic_cast<DirectionalLight*>(light)) {
            max = INFINITY;
        } else {
            max = (light->source - point).length();
        }

        // Check if the point is in a shadow
        if (!traceRay(shadowRay, 0.001, max, shadowTime, shadowObject)) {

            // Calculate H
            Vector3 H = (L + -ray.getDirection()).normalized();

            // Calculare diffuse component
            Vector3 diffuse = mat->getK().getY() * mat->getAlbedo() * MathUtils::clamp((N * L), 0, 1);

            // Calculate specular component
            Vector3 specular = mat->getK().getZ() * mat->getSpecular() * pow(MathUtils::clamp(N * H, 0, 1), mat->getN());

            // Add diffuse and specular components to illumination
            Vector3 ds = diffuse + specular;
            Vector3 hue = this->lights[i]->calculateHue(point);
            illumination = illumination + Vector3(ds.getX() * hue.getX(), ds.getY() * hue.getY(), ds.getZ() * hue.getZ());
        }
    }

    return illumination;
}

Camera* Scene::getCamera() {
    return this->cam;
}

float Scene::getVerticalFov() {
    return this->vfov;
}

float Scene::getHorizontalFov() {
    return this->hfov;
}

int Scene::getImageWidth() {
    return this->imageWidth;
}

int Scene::getImageHeight() {
    return this->imageHeight;
}

Vector3 Scene::getBackgroundColor() {
    return this->bkgColor;
}

std::vector<Object*> Scene::getObjects() {
    return this->objects;
}

std::vector<Light*> Scene::getLights() {
    return this->lights;
}

float Scene::safeStreamFloat(std::istringstream& iss, float min, float max) {

    // Try to read float from stream
    float value;
    try {
        iss >> value;
    } catch (...) {
        std::cout << "Error: Could not convert input string to float.\n";
        exit(0);
    }

    // Check if value is within valid range
    if (value < min || value > max) {
        std::cout << "Error: Float value " << value << " not within valid range " << min << "-" << max << ".\n";
        exit(0);
    }

    return value;
}

int Scene::safeStreamInt(std::istringstream& iss, int min, int max) {

    // Try to read float from stream
    int value;
    try {
        iss >> value;
    } catch (...) {
        std::cout << "Error: Could not convert input string to int.\n";
        exit(0);
    }

    // Check if value is within valid range
    if (value < min || value > max) {
        std::cout << "Error: Integer value " << value << " not within valid range " << min << "-" << max << ".\n";
        exit(0);
    }

    return value;
}

Vector3 Scene::safeStreamVector3(std::istringstream& iss, float min, float max) {

    // Try to read floats from stream
    float x;
    float y;
    float z;
    try {
        iss >> x;
        iss >> y;
        iss >> z;

    } catch (...) {
        std::cout << "Error: Could not convert input string to float.\n";
        exit(0);
    }

    // Check if x value is within valid range
    if (x < min || x > max) {
        std::cout << "Error: Vector3 float value " << x << " not within valid range " << min << "-" << max << ".\n";
        exit(0);
    }

    // Check if y value is within valid range
    if (y < min || y > max) {
        std::cout << "Error: Vector3 float value " << y << " not within valid range " << min << "-" << max << ".\n";
        exit(0);
    }

    // Check if z value is within valid range
    if (z < min || z > max) {
        std::cout << "Error: Vector3 float value " << z << " not within valid range " << min << "-" << max << ".\n";
        exit(0);
    }

    return Vector3(x, y, z);
}