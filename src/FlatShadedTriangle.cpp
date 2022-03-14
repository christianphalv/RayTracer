#include "../include/FlatShadedTriangle.h"

FlatShadedTriangle::FlatShadedTriangle(Material* material, Vector3 v0, Vector3 v1, Vector3 v2): Triangle(material, v0, v1, v2) {

}

void FlatShadedTriangle::info() {
    std::cout << "--- Flat Shaded Triangle ---\n"
        << "Vertices: \n";
    this->v0.info();
    this->v1.info();
    this->v2.info();
}