#include "../include/PointLight.h"

PointLight::PointLight(Vector3 source, Vector3 hue): Light(source, hue) {}

Vector3 PointLight::sourceDirection(Vector3 point) {
    return point - this->source;
}
