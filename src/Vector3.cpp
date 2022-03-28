#include "../include/Vector3.h"

// Constructors
Vector3::Vector3() {
    this->x = 1;
    this->y = 0;
    this->z = 0;
}

Vector3::Vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3::info() {
    std::cout << "(" << this->x << ", " << this->y << ", " << this->z << ")\n";
}

Vector3 Vector3::copy() {
    return Vector3(this->x, this->y, this->z);
}

float Vector3::length() {
    return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

Vector3 Vector3::normalized() {
    return this->copy() / this->length();
}

Vector3 Vector3::clamped(float min, float max) {
    return Vector3(MathUtils::clamp(this->x, min, max), MathUtils::clamp(this->y, min, max), MathUtils::clamp(this->z, min, max));
}

// Getters
float Vector3::getX() {
    return this->x;
}

float Vector3::getY() {
    return this->y;
}

float Vector3::getZ() {
    return this->z;
}

// Setters
void Vector3::setX(float x) {
    this->x = x;
}

void Vector3::setY(float y) {
    this->y = y;
}

void Vector3::setZ(float z) {
    this->z = z;
}

Vector3 operator+(Vector3 u, Vector3 v) {
    return Vector3(u.getX() + v.getX(), u.getY() + v.getY(), u.getZ() + v.getZ());
}

Vector3 operator-(Vector3 u, Vector3 v) {
    return Vector3(u.getX() - v.getX(), u.getY() - v.getY(), u.getZ() - v.getZ());
}

Vector3 operator-(Vector3 v) {
    return Vector3(- v.getX(), - v.getY(), - v.getZ());
}

Vector3 operator*(Vector3 v, float c) {
    return Vector3(v.getX() * c, v.getY() * c, v.getZ() * c);
}

Vector3 operator*(float c, Vector3 v) {
    return Vector3(v.getX() * c, v.getY() * c, v.getZ() * c);
}

float operator*(Vector3 u, Vector3 v) {
    return (u.getX() * v.getX()) + (u.getY() * v.getY()) + (u.getZ() * v.getZ());
}

Vector3 cross(Vector3 u, Vector3 v) {
    float w_x = (u.getY() * v.getZ()) - (u.getZ() * v.getY());
    float w_y = (u.getZ() * v.getX()) - (u.getX() * v.getZ());
    float w_z = (u.getX() * v.getY()) - (u.getY() * v.getX());
    return Vector3(w_x, w_y, w_z);
}

Vector3 operator/(Vector3 v, float c) {
    return Vector3(v.getX() / c, v.getY() / c, v.getZ() / c);
}

bool operator==(Vector3 u, Vector3 v) {
    return (u.getX() == v.getX()) && (u.getY() == v.getY()) && (u.getZ() == v.getZ());
}