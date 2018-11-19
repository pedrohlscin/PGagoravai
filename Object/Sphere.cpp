#include "Object.h"


Sphere::Sphere(Vec3 center, double radius) {
    this->center = center;
    this->radius = radius;
}

Vec3 Sphere::getPoint() const {
    return center;
}

bool Sphere::intersect(const Ray &r, ObjectIntersectionInfo *info) const {
    Vec3 originToCenter = r.origin() - this->center;

    double a = originToCenter.dotProduct(r.direction(), r.direction());
    double b = 2.0 * (originToCenter.dotProduct(originToCenter, r.direction()));
    double c = originToCenter.dotProduct(originToCenter, originToCenter) - (this->radius * this->radius);

    secondDegreeEquation sde(a,b,c);
    double deltha = sde.getDeltha();

    if(deltha > 0){
        double firstRoot = sde.getRoots()[0];
        double secondRoot = sde.getRoots()[1];

        Vec3 pointOne = r.positionAt(firstRoot);
        Vec3 pointTwo = r.positionAt(secondRoot);

        Vec3 aux = r.origin() - pointOne;
        double distPointOneToRayOrigin = sqrt( originToCenter.dotProduct(aux, aux));
        aux = r.origin() - pointTwo;
        double distPointTwoToRayOrigin = sqrt(originToCenter.dotProduct(aux, aux));

        if(distPointOneToRayOrigin > distPointTwoToRayOrigin){
            info->t = secondRoot;
            info->pHit = r.positionAt(info->t);
            info->normal = (info->pHit - center) / radius;
            return true;

        }
        if(distPointTwoToRayOrigin > distPointOneToRayOrigin){
            info->t = firstRoot;
            info->pHit = r.positionAt(info->t);
            info->normal = (info->pHit - center) / radius;
            return true;
        }
    }
    return false;
}