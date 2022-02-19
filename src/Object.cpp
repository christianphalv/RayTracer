#include "../include/Object.h"

Object::Object(Vector3 position, Material* material) {
    this->position = position;
    this->material = material;
}

Vector3 Object::getPosition() {
    return this->position;
}

Material* Object::getMaterial() {
    return this->material;
}

void Object::setPosition(Vector3 v) {
    this->position = v;
}