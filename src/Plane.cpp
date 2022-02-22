#include "../include/Plane.h"

Plane::Plane(Material* material, Vector3 v0, Vector3 v1, Vector3 v2): Object(material) {
    Vector3 e1 = v1 - v0;
    Vector3 e2 = v2 - v0;
    this->normal = cross(e1, e2);
    this->D = -(this->normal.getX() * v0.getX() + this->normal.getY() * v0.getY() + this->normal.getZ() * v0.getZ());
}

Plane::Plane(Material* material, Vector3 normal, Vector3 vertex): Object(material) {
    this->normal = normal;
    this->D = -(normal.getX() * vertex.getX() + normal.getY() * vertex.getY() + normal.getZ() * vertex.getZ());
}

bool Plane::rayIntersect(Ray r, float min, float max, float& time) {

    // Extract ray information
    Vector3 rd = r.getDirection();
    Vector3 ro = r.getOrigin();

    // Calculate denominator
    float denominator = this->normal.getX() * rd.getX() + this->normal.getY() * rd.getY() + this->normal.getZ() * rd.getZ();

    // Return false if ray is parallel to plane
    if (denominator == 0) {
        time = -1;
        return false;
    }

    // Calculate the intersection time
    float numerator = this->normal.getX() * ro.getX() + this->normal.getY() * ro.getY() + this->normal.getZ() * ro.getZ() + this->D;
    time = -numerator / denominator;

    // Check if time is within range
    if (time < min || time > max) {
        time = -1;
        return false;
    }

    return true;
}

Vector3 Plane::calculateNormal(Vector3 point) {
    return this->normal;
}

void Plane::info() {
    std::cout << "--- Plane ---\n"
        << "Equation: " << this->normal.getX() << "x + " << this->normal.getY() << "y + " << this->normal.getZ() << "z + " << this->D << " = 0\n";
}