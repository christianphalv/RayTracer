#include "../include/Sphere.h"

Sphere::Sphere(Material* material, Vector3 position, float radius): Object(material) {
    this->radius = radius;
    this->position = position;
}

bool Sphere::rayIntersect(Ray r, float min, float max, float& time) {

    // Extract sphere center
    float c_x = this->position.getX();
    float c_y = this->position.getY();
    float c_z = this->position.getZ();

    // Extract sphere radius
    float radius = this->radius;

    // Extract ray origin
    float o_x = r.getOrigin().getX();
    float o_y = r.getOrigin().getY();
    float o_z = r.getOrigin().getZ();

    // Extract ray direction
    float d_x = r.getDirection().getX();
    float d_y = r.getDirection().getY();
    float d_z = r.getDirection().getZ();

    // Calculate quadratic equation coefficients
    float B = 2 * (d_x * (o_x - c_x) + d_y * (o_y - c_y) + d_z * (o_z - c_z));
    float C = pow(o_x - c_x, 2) + pow(o_y - c_y, 2) + pow(o_z - c_z, 2) - pow(radius, 2);

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

        // Check if first intersection point is behind min point or beyond max point
        if (t_1 < min || t_1 > max) {

            // Check if second intersection point is behind min point or beyond max point
            if (t_2 < min || t_2 > max) {

                // Return false if intersection is behind min point or beyond max point
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

        // Calculate single intersection point
        time = -B / 2;

        // Check if point is behind min or beyond max
        if (time < min || time > max) {
            time = -1;
            return false;
        }

        // Return single intersection point
        return true;
    }

    // Return false if no intersection
    time = -1;
    return false;
}

Vector3 Sphere::calculateNormal(Vector3 point) {
    return (point - this->position).normalized();
}

void Sphere::info() {
    std::cout << "--- Sphere ---\n"
        << "Position: " << this->position.getX() << ", " << this->position.getY() << ", " << this->position.getZ() << "\n"
        << "Radius: " << this->radius << "\n";
}

Vector3 Sphere::albedo(Vector3 point) {

    // Calculate the surface normal at the point
    Vector3 N = calculateNormal(point);

    // Calculate theta and phi
    float theta = atan2(N.getY(), N.getX());
    float phi = acos(N.getZ());

    // Normalize theta to [0, 2 * PI]
    if (theta < 0) {
        theta += 2 * MathUtils::PI;
    }

    // Calculate the uv coordinates
    float u = theta / (2 * MathUtils::PI);
    float v = phi / MathUtils::PI;
    Vector2 uv = Vector2(u, v);

    return this->material->getAlbedo(uv);
}

float Sphere::getRadius() {
    return this->radius;
}

void Sphere::setRadius(float r) {
    this->radius = r;
}