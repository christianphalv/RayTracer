#include "../include/Object.h"

Object::Object(Material* material) {
    this->material = material;
}

Vector3 Object::albedo(Vector3 point) {
    return this->material->getAlbedo(Vector2(0, 0));
}

Material* Object::getMaterial() {
    return this->material;
}
