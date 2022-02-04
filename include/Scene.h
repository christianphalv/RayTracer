#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Camera.h"
#include "MathUtils.h"
#include "Object.h"
#include "Sphere.h"
#include "Vector3.h"

#define PI 3.14159265

class Scene {
    public:
        Scene(std::string inputFilename);

        Camera* getCamera();
        float getVerticalFov();
        float getHorizontalFov();
        int getImageWidth();
        int getImageHeight();
        Vector3 getBackgroundColor();
        std::vector<Object*> getObjects();

    private:
        Camera* cam;
        float vfov;
        float hfov;
        int imageWidth;
        int imageHeight;
        Vector3 bkgColor;
        Vector3 mtlColor;
        std::vector<Object*> objects;

        float safeStreamFloat(std::istringstream& iss, float min, float max);
        int safeStreamInt(std::istringstream& iss, int min, int max);
        Vector3 safeStreamVector3(std::istringstream& iss, float min, float max);


};