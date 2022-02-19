#include "../include/DirectionalLight.h"

DirectionalLight::DirectionalLight(Vector3 source, Vector3 hue): Light(source, hue) {}

Vector3 DirectionalLight::sourceDirection(Vector3 point) {
    return this->source;
}