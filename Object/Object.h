#ifndef PG_HITABLE_H
#define PG_HITABLE_H

#include "../Camera/Ray.h"

class material;

struct hitInfo {
    float THit;
    vec3 HitVector;
    vec3 normal;
    material *surfaceMaterial;
};

class object  {
private:
    material *sphereMaterial;

public:
    virtual bool hit(const ray& r, float t_min, float t_max, hitInfo& rec) const = 0;

};


#endif //PG_HITABLE_H