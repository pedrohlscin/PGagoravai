#include "../Camera/Ray.h"
#include "ObjectIntersection.h"

class Geometry{
public:
    virtual bool intersect(const Ray* r, ObjectIntersection* info=nullptr) const=0;
    virtual Vec3 getPoint() const=0;
};

class Sphere:public Geometry{
private:
    Vec3 center;
    double radius;
public:
    Sphere(Vec3 center, double radius);
    bool intersect(const Ray* r, ObjectIntersection* info=nullptr) const override;
    Vec3 getPoint() const override;
};