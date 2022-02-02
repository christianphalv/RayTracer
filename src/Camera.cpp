#include "../include/Camera.h"

Camera::Camera() {
    this->eye = Vector3(0, 0, 0);
    this->viewDirection = Vector3(1, 0, 0);
    this->upDirection = Vector3(0, 1, 0);
    this->u = cross(this->viewDirection, this->upDirection).normalized();
    this->v = cross(this->u, this->viewDirection);
}

Camera::Camera(Vector3 eye, Vector3 viewDirection, Vector3 upDirection) {
    this->eye = eye;
    this->viewDirection = viewDirection.normalized();
    this->upDirection = upDirection.normalized();
    this->u = cross(this->viewDirection, this->upDirection).normalized();
    if (u.length() == 0) {
        printf("Error: View direction is parallel with up direction");
        exit(0);
    }
    this->v = cross(this->u, this->viewDirection);
}

Vector3 Camera::getEye() {
    return this->eye;
}

Vector3 Camera::getViewDirection() {
    return this->viewDirection;
}

Vector3 Camera::getUpDirection() {
    return this->upDirection;
}

Vector3 Camera::getU() {
    return this->u;
}

Vector3 Camera::getV() {
    return this->v;
}