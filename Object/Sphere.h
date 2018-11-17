#ifndef PG_SPHERE_H
#define PG_SPHERE_H

#include "object.h"
#include "../Math/secondDegreeEquation.h"

class sphere: public object  {
private:
    vec3 center;
    float radius;

public:
    sphere() {}
    sphere(vec3 cen, float r, material *m) : center(cen), radius(r), sphereMaterial(m)  {};
    virtual bool hit(const ray& r, float tmin, float tmax, hitInfo& record) const;

};
//Função que recebe um raio e calcula se ocorreu uma intersecção com a esfera
bool sphere::hit(const ray& r, float t_min, float t_max, hitInfo& record) const {
    vec3 oc = r.origin() - center;

    float a = dotProduct(r.direction(), r.direction());
    float b = 2.0*dotProduct(oc, r.direction());
    float c = dotProduct(oc, oc) - radius*radius;
    secondDegreeEquation dqe(a, b, c);
    float deltha = dqe.getDeltha();

    if (deltha > 0) {
        float firstRoot = dqe.getRoots()[0];
        float secondRoot = dqe.getRoots()[1];

        if (firstRoot < t_max && firstRoot > t_min) {
            record.THit = firstRoot;
            record.vectorGeneratedByHit = r.positionAt(record.THit);
            record.normal = (record.vectorGeneratedByHit - center) / radius;
            record.surfaceMaterial = sphereMaterial;
            return true;
        }

        if (secondRoot < t_max && secondRoot > t_min) {
            record.THit = secondRoot;
            record.vectorGeneratedByHit = r.positionAt(record.THit);
            record.normal = (record.vectorGeneratedByHit - center) / radius;
            record.surfaceMaterial = sphereMaterial;
            return true;
        }
    }

    return false;
}


#endif //PG_SPHERE_H