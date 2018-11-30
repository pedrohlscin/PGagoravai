#ifndef PG_RAY_H
#define PG_RAY_H


#include "../Vector/Vec3.h"

class Ray {
private:
    Vec3 A;
    Vec3 B;

public:
    Ray() {}
    Ray(const Vec3& a, const Vec3& b) { A = a; B = b; }
    Vec3 origin() const       { return A; }
    Vec3 direction() const    { return B; }
    Vec3 positionAt(double t) const { return A + t*B;}

};

#endif //PG_RAY_H