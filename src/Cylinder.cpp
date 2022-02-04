#include "../include/Cylinder.h"

Cylinder::Cylinder(Vector3 position, Vector3 direction, float radius, float length, Vector3 color) {
    this->position = position;
    this->direction = direction;
    this->radius = radius;
    this->length = length;
    this->color = color;
}

bool Cylinder::rayIntersect(Ray r, float& time) {

    // Extract cylinder center
    float c_x = this->position.getX();
    float c_y = this->position.getY();
    float c_z = this->position.getZ();

    // Extract cylinder radius
    float radius = this->radius;

    // Extract ray origin
    float o_x = r.getOrigin().getX();
    float o_y = r.getOrigin().getY();
    float o_z = r.getOrigin().getZ();

    // Extract ray direction
    float d_x = r.getDirection().getX();
    float d_y = r.getDirection().getY();
    float d_z = r.getDirection().getZ();

    //

    // Calculate quadratic equation coefficients
    float B = 2 * (d_y * (o_y - c_y) + d_z * (o_z - c_z));
    float C = pow(o_y - c_y, 2) + pow(o_z - c_z, 2) - pow(radius, 2);

    // Calculate discriminant
    float discriminant = pow(B, 2) - (4 * C);

    // Calculate nearest intersection time
    if (discriminant > 0) {

        // Calculate intersection times
        float t_1 = (-B + sqrt(discriminant)) / 2;
        float t_2 = (-B - sqrt(discriminant)) / 2;

        // Organize times into ascending order
        if (t_1 > t_2) {
            std::swap(t_1, t_2);
        }

        // Check if first intersection point is behind ray
        if (t_1 < 0) {

            // Check if second intersection point is behind ray
            if (t_2 < 0) {

                // Return false if intersection is behind ray origin
                time = -1;
                return false;
            }

            // Return second intersection point
            time = t_2;
            return true;

        }

        // Return first intersection point
        time = t_1;
        return true;

    } else if (discriminant == 0) {

        // Return single intersection point
        time = -B / 2;
        return true;
    }

    // Return false if no intersection
    time = -1;
    return false;
}

void Cylinder::info() {
    std::cout << "--- Cylinder ---\n"
        << "Position: (" << this->position.getX() << ", " << this->position.getY() << ", " << this->position.getZ() << ")\n"
        << "Direction: (" << this->direction.getX() << ", " << this->direction.getY() << ", " << this->direction.getZ() << ")\n"
        << "Radius: " << this->radius << "\n"
        << "Length: " << this->length << "\n"
        << "Color: (" << this->color.getX() << ", " << this->color.getY() << ", " << this->color.getZ() << ")\n";
}

Vector3 Cylinder::getDirection() {
    return this->direction;
}

float Cylinder::getRadius() {
    return this->radius;
}

float Cylinder::getLength() {
    return this->length;
}

void Cylinder::setDirection(Vector3 d) {
    this->direction = d;
}

void Cylinder::setRadius(float r) {
    this->radius = r;
}

void Cylinder::setLength(float l) {
    this->length = l;
}