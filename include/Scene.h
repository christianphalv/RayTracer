#pragma once

#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include "AttenuationLight.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "FlatShadedTriangle.h"
#include "Image.h"
#include "Light.h"
#include "Material.h"
#include "MathUtils.h"
#include "Object.h"
#include "Plane.h"
#include "PointLight.h"
#include "Ray.h"
#include "SmoothShadedTriangle.h"
#include "Sphere.h"
#include "TexturedFlatShadedTriangle.h"
#include "TexturedSmoothShadedTriangle.h"
#include "TexturedMaterial.h"
#include "Vector2.h"
#include "Vector3.h"

#define PI 3.14159265

class Scene {
    public:
        /**
         * Constructor for a scene.
         * 
         * The scene constructor will read the input file and
         * initialize a scene based on the specified parameters.
         *
         * @param inputFilename The name of the input file defining a scene.
         */
        Scene(std::string inputFilename);

        /**
         * Find the first ray-object intersection.
         *
         * @param ray The ray for ray-object intersection.
         * @param min The minimum time for intersection.
         * @param max The maximum time for intersection.
         * @param time OUT The nearest intersection point time.
         * @param object OUT The nearest intesected object.
         * @return true if intersection, otherwise false.
         */
        bool castRay(Ray ray, float min, float max, float& time, Object*& object);

        Vector3 traceRay(Ray ray);

        Vector3 traceRayRecursive(Ray ray, int maxRecursion, float etaI);
        //Vector3 traceRayRecursive(Ray ray, int maxRecursion, std::stack<int>& materialStack);

        /**
         * Shade the pixel based on the Phong-Blinn illumination model.
         *
         * @param point The point of the object to be shaded.
         * @param object The object to be shaded.
         * @return color of the shaded pixel.
         */
        Vector3 shadeRay(Ray ray, Vector3 point, Object* object);

        float shadowFlag(Ray ray, float min, float max);

        Camera* getCamera();
        float getVerticalFov();
        float getHorizontalFov();
        int getImageWidth();
        int getImageHeight();
        Vector3 getBackgroundColor();
        std::vector<Object*> getObjects();
        std::vector<Light*> getLights();

    private:
        Camera* cam;
        float vfov;
        float hfov;
        int imageWidth;
        int imageHeight;
        Vector3 bkgColor;
        Material* material;
        Image* texture;
        std::vector<Object*> objects;
        std::vector<Light*> lights;

        float safeStreamFloat(std::istringstream& iss, float min, float max);
        int safeStreamInt(std::istringstream& iss, int min, int max);
        Vector2 safeStreamVector2(std::istringstream& iss, float min, float max);
        Vector3 safeStreamVector3(std::istringstream& iss, float min, float max);


};

struct Index {
    Vector3 vertices;
    Vector3 normals;
};