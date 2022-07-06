// vector class

#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <cmath>

class Vector3 {
    public:
        double x, y, z;

        Vector3 (double x_init, double y_init, double z_init);
       
        double magnitude ();
        double dotProduct (Vector3 v);

        Vector3 normalize ();
        Vector3 operator+ (const Vector3& v);
        Vector3 operator- (const Vector3& v);
        Vector3 divide (double c);
        Vector3 scalarMultiply (double c);
        Vector3 crossProduct (Vector3 v);
}; 

#endif // VECTOR3_H_
