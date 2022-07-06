// type definitions

#ifndef TYPES_H_
#define TYPES_H_

#include <vector>
#include "vector3.h"

struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

struct Ray {
    Vector3 pos;
    Vector3 dir;
};

struct Sphere {
    Vector3 position;
    float radius;
    Color mtlColor;
};

struct Scene {
    int imwidth;
    int imheight;

    Vector3 eye;
    Vector3 viewDir;
    Vector3 upDir;
    float vfov;

    Color bkgcolor;

    Sphere s;
};

struct ViewWindow {
    Vector3 ul, ur, ll, lr;
    float height, width;
    float deltaH, deltaV;
}

#endif // TYPES_H_