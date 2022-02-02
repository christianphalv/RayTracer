#include "../include/Ray.h"

// Constructors
Ray::Ray(Vector3 origin, Vector3 direction) {
    this->origin = origin;
    this->direction = direction.normalized();
}

Vector3 Ray::calculatePoint(float t) {
    return this->origin + (this->direction * t);
}

// Getters
Vector3 Ray::getOrigin() {
    return this->origin;
}

Vector3 Ray::getDirection() {
    return this->direction;
}

// Setters
void Ray::setOrigin(Vector3 v) {
    this->origin = v;
}

void Ray::setDirection(Vector3 v) {
    this->direction = v;
}