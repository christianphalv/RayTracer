#include "../include/Light.h"

Light::Light(Vector3 source, Vector3 hue) {
    this->source = source;
    this->hue = hue;
}

Vector3 Light::calculateHue(Vector3 point) {

    // Return normalized hue if length greater than one
    if (this->hue.length() > 1) {
        return this->hue.normalized();
    }
    
    return this->hue;
}