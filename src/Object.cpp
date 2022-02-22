#include "../include/Object.h"

Object::Object(Material* material) {
    this->material = material;
}

Material* Object::getMaterial() {
    return this->material;
}
