#pragma once

#include "Vector3.h"

class Camera {
    public:
        Camera();
        Camera(Vector3 eye, Vector3 viewDirection, Vector3 upDirection);

        Vector3 getEye();
        Vector3 getViewDirection();
        Vector3 getUpDirection();
        Vector3 getU();
        Vector3 getV();

    private:
        Vector3 eye;
        Vector3 viewDirection;
        Vector3 upDirection;
        Vector3 u;
        Vector3 v;

};