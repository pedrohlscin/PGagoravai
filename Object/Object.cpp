#include "Object.h"


Object::Object(Geometry *geometry, Material *material) {
    this->material = material;
    this->geometry = geometry;
}

bool Object::intersect(const Ray &r, ObjectIntersectionInfo *info) {
    return this->geometry->intersect(r, info);
}
