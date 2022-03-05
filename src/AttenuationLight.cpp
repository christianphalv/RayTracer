#include "../include/AttenuationLight.h"

AttenuationLight::AttenuationLight(Vector3 source, Vector3 hue, Vector3 cValues): Light(source, hue) {
    this->cValues = cValues;
}

Vector3 AttenuationLight::sourceDirection(Vector3 point) {
    return point - this->source;
}

Vector3 AttenuationLight::calculateHue(Vector3 point) {

    // Calculate distance from light to point
    float d = (this->source - point).length();

    // Calculate attenuation factor
    float att = 1 / (this->cValues.getX() + (this->cValues.getY() * d) + (this->cValues.getZ() * pow(d, 2)));

    // Return normalized hue if length greater than one
    if (this->hue.length() > 1) {

        // Scale hue by attenuation factor
        return this->hue.normalized() * att;
    }

    // Scale hue by attenuation factor
    return this->hue * att;
}