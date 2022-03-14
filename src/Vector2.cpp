#include "../include/Vector2.h"

// Constructors
Vector2::Vector2() {
    this->x = 1;
    this->y = 0;
}

Vector2::Vector2(float x, float y) {
    this->x = x;
    this->y = y;
}

void Vector2::info() {
    std::cout << "(" << this->x << ", " << this->y << ")\n";
}

Vector2 Vector2::copy() {
    return Vector2(this->x, this->y);
}

float Vector2::length() {
    return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

Vector2 Vector2::normalized() {
    return this->copy() / this->length();
}

// Getters
float Vector2::getX() {
    return this->x;
}

float Vector2::getY() {
    return this->y;
}

// Setters
void Vector2::setX(float x) {
    this->x = x;
}

void Vector2::setY(float y) {
    this->y = y;
}

Vector2 operator+(Vector2 u, Vector2 v) {
    return Vector2(u.getX() + v.getX(), u.getY() + v.getY());
}

Vector2 operator-(Vector2 u, Vector2 v) {
    return Vector2(u.getX() - v.getX(), u.getY() - v.getY());
}

Vector2 operator-(Vector2 v) {
    return Vector2(- v.getX(), - v.getY());
}

Vector2 operator*(Vector2 v, float c) {
    return Vector2(v.getX() * c, v.getY() * c);
}

Vector2 operator*(float c, Vector2 v) {
    return Vector2(v.getX() * c, v.getY() * c);
}

float operator*(Vector2 u, Vector2 v) {
    return (u.getX() * v.getX()) + (u.getY() * v.getY());
}

float cross(Vector2 u, Vector2 v) {
    return (u.getX() * v.getY()) - (u.getY() * v.getX());
}

Vector2 operator/(Vector2 v, float c) {
    return Vector2(v.getX() / c, v.getY() / c);
}

bool operator==(Vector2 u, Vector2 v) {
    return (u.getX() == v.getX()) && (u.getY() == v.getY());
}