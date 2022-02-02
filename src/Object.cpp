#include "../include/Object.h"

// Getters
Vector3 Object::getPosition() {
    return this->position;
}

Vector3 Object::getColor() {
    return this->color;
}

// Setters
void Object::setPosition(Vector3 v) {
    this->position = v;
}

void Object::setColor(Vector3 v) {
    this->color = v;
}