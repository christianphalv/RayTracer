#include "../include/TexturedFlatShadedTriangle.h"

TexturedFlatShadedTriangle::TexturedFlatShadedTriangle(Material* material, Vector3 v0, Vector3 v1, Vector3 v2, Vector2 t0, Vector2 t1, Vector2 t2): Triangle(material, v0, v1, v2) {
    this->t0 = t0;
    this->t1 = t1;
    this->t2 = t2;
}

void TexturedFlatShadedTriangle::info() {
    std::cout << "--- Textured Flat Shaded Triangle ---\n"
        << "Vertices: \n";
    this->v0.info();
    this->v1.info();
    this->v2.info();
}

Vector3 TexturedFlatShadedTriangle::albedo(Vector3 point) {

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