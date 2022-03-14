#include "../include/SmoothShadedTriangle.h"

SmoothShadedTriangle::SmoothShadedTriangle(Material* material, Vector3 v0, Vector3 v1, Vector3 v2, Vector3 n0, Vector3 n1, Vector3 n2): Triangle(material, v0, v1, v2) {
    this->n0 = n0.normalized();
    this->n1 = n1.normalized();
    this->n2 = n2.normalized();
}

Vector3 SmoothShadedTriangle::calculateNormal(Vector3 point) {

    // Initialize barycentric coordinates
    float alpha;
    float beta;
    float gamma;

    // Calculate barycentric coordinates
    barycentric(point, alpha, beta, gamma);
    
    return ((alpha * this->n0) + (beta * this->n1) + (gamma * this->n2)).normalized();
}

void SmoothShadedTriangle::info() {
    std::cout << "--- Smooth Shaded Triangle ---\n"
        << "Vertices: \n";
    this->v0.info();
    this->v1.info();
    this->v2.info();
}