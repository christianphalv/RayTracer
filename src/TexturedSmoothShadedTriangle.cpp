#include "../include/TexturedSmoothShadedTriangle.h"

TexturedSmoothShadedTriangle::TexturedSmoothShadedTriangle(Material* material, Vector3 v0, Vector3 v1, Vector3 v2, Vector2 t0, Vector2 t1, Vector2 t2, Vector3 n0, Vector3 n1, Vector3 n2): Triangle(material, v0, v1, v2) {
    this->t0 = t0;
    this->t1 = t1;
    this->t2 = t2;
    this->n0 = n0.normalized();
    this->n1 = n1.normalized();
    this->n2 = n2.normalized();
}

Vector3 TexturedSmoothShadedTriangle::calculateNormal(Vector3 point) {

    // Initialize barycentric coordinates
    float alpha;
    float beta;
    float gamma;

    // Calculate barycentric coordinates
    barycentric(point, alpha, beta, gamma);
    
    return ((alpha * this->n0) + (beta * this->n1) + (gamma * this->n2)).normalized();
}

void TexturedSmoothShadedTriangle::info() {
    std::cout << "--- Textured Smooth Shaded Triangle ---\n"
        << "Vertices: \n";
    this->v0.info();
    this->v1.info();
    this->v2.info();
}

Vector3 TexturedSmoothShadedTriangle::albedo(Vector3 point) {

    // Initialize barycentric coordinates
    float alpha;
    float beta;
    float gamma;

    // Calculate barycentric coordinates
    barycentric(point, alpha, beta, gamma);

    // Calculate uv coordinates of the point
    float u = (alpha * this->t0.getX()) + (beta * this->t1.getX()) + (gamma * this->t2.getX());
    float v = (alpha * this->t0.getY()) + (beta * this->t1.getY()) + (gamma * this->t2.getY());
    Vector2 uv = Vector2(u, v);
    
    return this->material->getAlbedo(uv);
}