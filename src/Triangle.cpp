#include "../include/Triangle.h"

Triangle::Triangle(Material* material, Vector3 v0, Vector3 v1, Vector3 v2): Object(material) {
    this->v0 = v0;
    this->v1 = v1;
    this->v2 = v2;
    this->plane = new Plane(material, v0, v1, v2);

    Vector3 e1 = this->v1 - this->v0;
    Vector3 e2 = this->v2 - this->v0;
    this->normal = cross(e1, e2).normalized();
}

bool Triangle::rayIntersect(Ray r, float min, float max, float& time) {

    // Check if ray intersects triangle plane
    if (!this->plane->rayIntersect(r, min, max, time)) {
        time = -1;
        return false;
    }

    // Calculate the intersection point
    Vector3 p = r.calculatePoint(time);

    // Check if triangle is facing camera
    // if (r.getDirection().normalized() * this->normal < 0) {
    //     time = -1;
    //     return false;
    // }

    // Initialize barycentric coordinates
    float alpha;
    float beta;
    float gamma;

    // Check if point is in triangle
    if (!barycentric(p, alpha, beta, gamma)) {
        time = -1;
        return false;
    }

    // Point is in triangle
    return true;
}

Vector3 Triangle::calculateNormal(Vector3 point) {
    Vector3 e1 = this->v1 - this->v0;
    Vector3 e2 = this->v2 - this->v0;
    return cross(e1, e2);
}

bool Triangle::barycentric(Vector3 p, float& alpha, float& beta, float& gamma) {

    // Calculate the difference vectors
    Vector3 e1 = this->v1 - this->v0;
    Vector3 e2 = this->v2 - this->v0;
    Vector3 ep = p - this->v0;

    // Calculate the dot products
    float d_11 = e1 * e1;
    float d_12 = e1 * e2;
    float d_22 = e2 * e2;
    float d_p1 = ep * e1;
    float d_p2 = ep * e2;

    // Calculate D values
    float D = d_11 * d_22 - d_12 * d_12;
    float D_beta = d_22 * d_p1 - d_12 * d_p2;
    float D_gamma = d_11 * d_p2 - d_12 * d_p1;

    // Calculate barycentric coordinates
    beta = D_beta / D;
    gamma = D_gamma / D;
    alpha = 1 - (beta + gamma);

    // Check if any coordinate is less than zero
    if (alpha < 0 || beta < 0 || gamma < 0) {
        return false;
    }

    // Check if sum of coordinates is greater than one
    if (alpha + beta + gamma > 1) {
        return false;
    }

    return true;
}