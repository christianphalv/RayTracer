#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Object.h"
#include "Sphere.h"
#include "Vector3.h"

class Scene {
    public:
        Scene(std::string inputFilename);

        Vector3 getEye();
        Vector3 getViewDirection();
        Vector3 getUpDirection();
        float getVerticalFov();
        int getImageWidth();
        int getImageHeight();
        Vector3 getBackgroundColor();
        std::vector<Object*> getObjects();

    private:
        Vector3 eye;
        Vector3 viewDir;
        Vector3 upDir;
        float vfov;
        int imageWidth;
        int imageHeight;
        Vector3 bkgColor;
        Vector3 mtlColor;
        std::vector<Object*> objects;

        float safeStreamFloat(std::istringstream& iss, float min, float max);
        int safeStreamInt(std::istringstream& iss, int min, int max);
        Vector3 safeStreamVector3(std::istringstream& iss, float min, float max);

};