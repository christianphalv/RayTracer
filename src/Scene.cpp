#include "../include/Scene.h"

Scene::Scene(std::string inputFilename) {

    // Default settings
    float min = -INFINITY;
    float max = INFINITY;
    this->material = NULL;
    this->texture = NULL;

    // Default camera variables
    Vector3 eye = Vector3(0, 0, 0);
    Vector3 viewDir = Vector3(1, 0, 0);
    Vector3 upDir = Vector3(0, 1, 0);

    // Setup polygon objects
    std::vector<Vector3*> vertices;
    std::vector<Vector3*> vertexNormals;
    std::vector<Vector2*> vertexTextures;

    // Open stream to input file
    std::ifstream inputFile(inputFilename, std::ios::in | std::ios::binary);

    // Check if valid file
    if (!inputFile.is_open()) {
        std::cout << "Error: Invalid input file. \n";
        exit(0);
    }

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
            this->imageWidth = safeStreamInt(iss, 0, INFINITY);
            this->imageHeight = safeStreamInt(iss, 0, INFINITY);

        } else if (keyword.compare("bkgcolor") == 0) {
            this->bkgColor = safeStreamVector3(iss, 0, 1);

        } else if (keyword.compare("mtlcolor") == 0) {
            Vector3 mtlAlbedo = safeStreamVector3(iss, 0, 1);
            Vector3 mtlSpecular = safeStreamVector3(iss, 0, 1);
            Vector3 mtlK = safeStreamVector3(iss, 0, 1);
            float mtlN = safeStreamFloat(iss, 0, max);
            float mtlOpacity = safeStreamFloat(iss, 0, max);
            float mtlRefraction = safeStreamFloat(iss, 0, max);

            if (this->texture) {
                this->material = new TexturedMaterial(this->texture, mtlSpecular, mtlK, mtlN, mtlOpacity, mtlRefraction);
            } else {
                this->material = new Material(mtlAlbedo, mtlSpecular, mtlK, mtlN, mtlOpacity, mtlRefraction);
            }

        } else if (keyword.compare("texture") == 0) {
            std::string textureFilename;
            iss >> textureFilename;
            std::string path = "./";
            path.append(textureFilename);
            std::cout << path << "\n";
            this->texture = new Image(path);

            if (this->material) {
                this->material = new TexturedMaterial(this->texture, this->material->getSpecular(), this->material->getK(), this->material->getN(), 1, 1);
            }
            
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

        } else if (keyword.compare("vt") == 0) {
            Vector2 v = safeStreamVector2(iss, min, max);
            vertexTextures.push_back(new Vector2(v.getX(), v.getY()));

        } else if (keyword.compare("vn") == 0) {
            Vector3 n = safeStreamVector3(iss, min, max);
            vertexNormals.push_back(new Vector3(n.getX(), n.getY(), n.getZ()));

        } else if (keyword.compare("f") == 0) {

            // Retrieve the rest of the line
            std::string rem(iss.str().substr(iss.tellg()));

            // Initialize regex system
            std::smatch match;
            std::regex regTexAndNormals("([1-9]+)/([1-9]+)/([1-9]+) +([1-9]+)/([1-9]+)/([1-9]+) +([1-9]+)/([1-9]+)/([1-9]+)");
            std::regex regTex("([1-9]+)/([1-9]+) +([1-9]+)/([1-9]+) +([1-9]+)/([1-9]+)");
            std::regex regNormals("([1-9]+)//([1-9]+) +([1-9]+)//([1-9]+) +([1-9]+)//([1-9]+)");
            std::regex reg("([1-9]+) +([1-9]+) +([1-9]+)");
            
            if (std::regex_search(rem, match, regTexAndNormals)) {

                // Retrieve triangle vertex indices
                int iv0 = stoi(match[1].str());
                int iv1 = stoi(match[4].str());
                int iv2 = stoi(match[7].str());

                // Retrieve triangle texture indices
                int it0 = stoi(match[2].str());
                int it1 = stoi(match[5].str());
                int it2 = stoi(match[8].str());

                // Retrieve triangle normal indices
                int in0 = stoi(match[3].str());
                int in1 = stoi(match[6].str());
                int in2 = stoi(match[9].str());

                // Check if vertex indices are valid
                if (iv0 > vertices.size() || iv1 > vertices.size() || iv2 > vertices.size()) {
                    std::cout << "Error: Triangle vertex index out of range. \n";
                    exit(0);
                }
                
                // Check if texture indices are valid
                if (it0 > vertexTextures.size() || it1 > vertexTextures.size() || it2 > vertexTextures.size()) {
                    std::cout << "Error: Triangle normal index out of range. \n";
                    exit(0);
                }

                // Check if normal indices are valid
                if (in0 > vertexNormals.size() || in1 > vertexNormals.size() || in2 > vertexNormals.size()) {
                    std::cout << "Error: Triangle normal index out of range. \n";
                    exit(0);
                }

                // Retrieve triangle vertices
                Vector3 v0 = vertices[iv0 - 1]->copy();
                Vector3 v1 = vertices[iv1 - 1]->copy();
                Vector3 v2 = vertices[iv2 - 1]->copy();

                // Retrieve triangle textures
                Vector2 t0 = vertexTextures[it0 - 1]->copy();
                Vector2 t1 = vertexTextures[it1 - 1]->copy();
                Vector2 t2 = vertexTextures[it2 - 1]->copy();

                // Retrieve triangle normals
                Vector3 n0 = vertexNormals[in0 - 1]->copy();
                Vector3 n1 = vertexNormals[in1 - 1]->copy();
                Vector3 n2 = vertexNormals[in2 - 1]->copy();

                // Instantiate triangle and add to objects
                this->objects.push_back(new TexturedSmoothShadedTriangle(this->material, v0, v1, v2, t0, t1, t2, n0, n1, n2));
                
            } else if (std::regex_search(rem, match, regTex)) {

                // Retrieve triangle vertex indices
                int iv0 = stoi(match[1].str());
                int iv1 = stoi(match[3].str());
                int iv2 = stoi(match[5].str());

                // Retrieve triangle texture indices
                int it0 = stoi(match[2].str());
                int it1 = stoi(match[4].str());
                int it2 = stoi(match[6].str());

                // Check if vertex indices are valid
                if (iv0 > vertices.size() || iv1 > vertices.size() || iv2 > vertices.size()) {
                    std::cout << "Error: Triangle vertex index out of range. \n";
                    exit(0);
                }
                
                // Check if texture indices are valid
                if (it0 > vertexTextures.size() || it1 > vertexTextures.size() || it2 > vertexTextures.size()) {
                    std::cout << "Error: Triangle normal index out of range. \n";
                    exit(0);
                }

                // Retrieve triangle vertices
                Vector3 v0 = vertices[iv0 - 1]->copy();
                Vector3 v1 = vertices[iv1 - 1]->copy();
                Vector3 v2 = vertices[iv2 - 1]->copy();

                // Retrieve triangle textures
                Vector2 t0 = vertexTextures[it0 - 1]->copy();
                Vector2 t1 = vertexTextures[it1 - 1]->copy();
                Vector2 t2 = vertexTextures[it2 - 1]->copy();

                // Instantiate triangle and add to objects
                this->objects.push_back(new TexturedFlatShadedTriangle(this->material, v0, v1, v2, t0, t1, t2));

            } else if (std::regex_search(rem, match, regNormals)) {

                // Retrieve triangle vertex indices
                int iv0 = stoi(match[1].str());
                int iv1 = stoi(match[3].str());
                int iv2 = stoi(match[5].str());

                // Retrieve triangle normal indices
                int in0 = stoi(match[2].str());
                int in1 = stoi(match[4].str());
                int in2 = stoi(match[6].str());

                // Check if vertex indices are valid
                if (iv0 > vertices.size() || iv1 > vertices.size() || iv2 > vertices.size()) {
                    std::cout << "Error: Triangle vertex index out of range. \n";
                    exit(0);
                }

                
                // Check if normal indices are valid
                if (in0 > vertexNormals.size() || in1 > vertexNormals.size() || in2 > vertexNormals.size()) {
                    std::cout << "Error: Triangle normal index out of range. \n";
                    exit(0);
                }

                // Retrieve triangle vertices
                Vector3 v0 = vertices[iv0 - 1]->copy();
                Vector3 v1 = vertices[iv1 - 1]->copy();
                Vector3 v2 = vertices[iv2 - 1]->copy();

                // Retrieve triangle normals
                Vector3 n0 = vertexNormals[in0 - 1]->copy();
                Vector3 n1 = vertexNormals[in1 - 1]->copy();
                Vector3 n2 = vertexNormals[in2 - 1]->copy();

                // Instantiate triangle and add to objects
                this->objects.push_back(new SmoothShadedTriangle(this->material, v0, v1, v2, n0, n1, n2));

            } else if (std::regex_search(rem, match, reg)) {

                // Retrieve triangle vertex indices
                int iv0 = stoi(match[1].str());
                int iv1 = stoi(match[2].str());
                int iv2 = stoi(match[3].str());

                // Check if vertex indices are valid
                if (iv0 > vertices.size() || iv1 > vertices.size() || iv2 > vertices.size()) {
                    std::cout << "Error: Triangle vertex index out of range. \n";
                    exit(0);
                }

                // Retrieve triangle vertices
                Vector3 v0 = vertices[iv0 - 1]->copy();
                Vector3 v1 = vertices[iv1 - 1]->copy();
                Vector3 v2 = vertices[iv2 - 1]->copy();

                // Instantiate triangle and add to objects
                this->objects.push_back(new FlatShadedTriangle(this->material, v0, v1, v2));
            }


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
}

Vector3 Scene::traceRay(Ray ray) {
    int maxRecursion = 10;
    std::stack<int> materialStack;
    materialStack.push(1);
    Vector3 color = traceRayRecursive(ray, maxRecursion, 1);
    return color;
}

Vector3 Scene::traceRayRecursive(Ray ray, int maxRecursion, float etaI) {

    if (maxRecursion < 0) {
        return Vector3(0, 0, 0);
    }

    // Trace ray for object intersections
    float time;
    Object* object;
    if (this->castRay(ray, 0.001, INFINITY, time, object)) {

        // Calculate intersection point
        Vector3 point = ray.calculatePoint(time);

        // Calculate surface normal at intersection point
        Vector3 n = object->calculateNormal(point).normalized();

        // Calculate Frenzel reflectance
        Vector3 I = -ray.getDirection().normalized();
        float alpha = n * I;
        if (alpha < 0) {
            n = -n;
            alpha = n * I;
        }
        float etaT = object->getMaterial()->getRefraction();
        float F0 = pow((etaT - 1) / (etaT + 1), 2);
        float Fr = F0 + ((1 - F0) * pow(1 - alpha, 5));

        // Calculate illumination from object intersection point
        Vector3 illumination = this->shadeRay(ray, point, object);

        // Recursively calculate reflection
        Ray R = Ray(point, 2 * alpha * n - I);
        Vector3 reflection = Fr * this->traceRayRecursive(R, maxRecursion - 1, etaI);

        // Reset etaT to 1 if exiting material
        if (etaI == etaT) {
            etaT = 1;
        }

        // Recursively calculate refraction
        Vector3 refraction = Vector3(0, 0, 0);
        float discriminant = 1 - (pow(etaI / etaT, 2) * (1 - pow(alpha, 2)));
        if (discriminant >= 0) {
            Vector3 TDir = ((-n * sqrt(discriminant)) + ((etaI / etaT) * ((alpha * n) - I))).normalized();
            Ray T = Ray(point, TDir);
            refraction = (1 - Fr) * (1 - object->getMaterial()->getOpacity()) * this->traceRayRecursive(T, maxRecursion - 1, etaT);

        }

        // Set pixel to shaded intersection point
        Vector3 color = (illumination + reflection + refraction).clamped(0, 1);
        return color;

    } else {

        // Set pixel to background color if no intersecion
        return this->getBackgroundColor();
    }
}

bool Scene::castRay(Ray ray, float min, float max, float& time, Object*& object) {
    
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
    Vector3 illumination = mat->getK().getX() * object->albedo(point);

    // Loop through each light source
    for (int i = 0; i < this->lights.size(); i++) {

        Light* light = this->lights[i];

        // Calculate L
        Vector3 L = -this->lights[i]->sourceDirection(point).normalized();

        // Initialize shadow parameters
        Ray shadowRay = Ray(point, L);

        // Set maximum time
        float max;
        if (dynamic_cast<DirectionalLight*>(light)) {
            max = INFINITY;
        } else {
            max = (light->source - point).length();
        }

        // Calculate shadow flag
        float shadowFlag = this->shadowFlag(shadowRay, 0.001, max);
        
        // Calculate H
        Vector3 H = (L + -ray.getDirection()).normalized();
        //Vector3 H = (L + (point - this->cam->getEye()).normalized()).normalized();

        // Calculare diffuse component
        Vector3 diffuse = mat->getK().getY() * object->albedo(point) * MathUtils::clamp((N * L), 0, 1);

        // Calculate specular component
        Vector3 specular = mat->getK().getZ() * mat->getSpecular() * pow(MathUtils::clamp(N * H, 0, 1), mat->getN());

        // Add diffuse and specular components to illumination
        Vector3 ds = diffuse + specular;
        Vector3 hue = this->lights[i]->calculateHue(point);
        illumination = illumination + shadowFlag * Vector3(ds.getX() * hue.getX(), ds.getY() * hue.getY(), ds.getZ() * hue.getZ());
    }

    return illumination;
}

float Scene::shadowFlag(Ray ray, float min, float max) {

    // Initialize shadow flag
    float S = 1;

    // Loop through each object in the scene
    for (int i = 0; i < this->getObjects().size(); i++) {

        // Check ray-object intersection
        float t;
        if (this->getObjects()[i]->rayIntersect(ray, min, max, t)) {

            // Incorporate object's opacity to shadow flag
            S = S * (1 - this->getObjects()[i]->getMaterial()->getOpacity());
        }
    }

    return S;
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

Vector2 Scene::safeStreamVector2(std::istringstream& iss, float min, float max) {

    // Try to read floats from stream
    float x;
    float y;
    try {
        iss >> x;
        iss >> y;

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

    return Vector2(x, y);
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