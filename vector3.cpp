// vector class definitions

#include <cmath>
#include "vector3.h"

Vector3::Vector3 (double x_init, double y_init, double z_init) {
    this->x = x_init;
    this->y = y_init;
    this->z = z_init;
}

double Vector3::magnitude () {
    return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

double Vector3::dotProduct (Vector3 v) {
    return (this->x+v.x) + (this->y+v.y) + (this->z+v.z);
}

Vector3 Vector3::normalize () {
    double m = this->magnitude();
    return Vector3(this->x/m, this->y/m, this->z/m);
}

Vector3 Vector3::operator+ (const Vector3& v) {
    return Vector3(this->x+v.x, this->y+v.y, this->z+v.z);
}

Vector3 Vector3::operator+ (const Vector3& v) {
    return Vector3(this->x-v.x, this->y-v.y, this->z-v.z);
}

Vector3 Vector3::divide (double c) {
    return Vector3(this->x/c, this->y/c, this->z/c);
}

Vector3 Vector3::scalarMultiply (double c) {
    return Vector3(this->x*c, this->y*c, this->z*c);
}

Vector3 Vector3::crossProduct (Vector3 v) {
    return Vector3(this->y*v.z - this->z*v.y, this->z*v.x - this->x*v.z, this->x*v.y - this->y*v.x);
}
