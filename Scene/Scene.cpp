//
// Created by guila on 17/11/18.
//

#include "Scene.h"


Scene::Scene() = default;


void Scene::add(Object* object){
    this->objects.push_back(object);
}


Vec3 Scene::phong(Object* objLight, ObjectIntersectionInfo objInfo, Ray incidenceRay, Ray objectIntersectedToObjLight)const {

    Object* objectIntersected = objInfo.o;
    Vec3 cL = objLight->getMaterial()->ke * objLight->getMaterial()->getNormalizedColor();
    Vec3 dC = objectIntersected->getMaterial()->kd * objectIntersected->getMaterial()->getNormalizedColor();
    Vec3 v;
    float nl = std::max(0.0f, v.dotProduct(  objInfo.normal.getUnitVector(), objectIntersectedToObjLight.direction().getUnitVector()     ));
    float nv = std::max(0.0f, v.dotProduct(-incidenceRay.direction().getUnitVector(), 2*nl*objInfo.normal.getUnitVector() - objectIntersectedToObjLight.direction().getUnitVector()  ));
    Vec3 diff = cL * dC * nl;
    Vec3 spec = cL * pow(nv, objectIntersected->getMaterial()->alpha) * objectIntersected->getMaterial()->ks;

    return diff + spec;
}

Vec3 Scene::trace(const Ray &r, int recursionLevel) const {

    ObjectIntersectionInfo objectIntersectedInformation;
    Vec3 objectColor{0,0,0};

    if (this->intersect(r, &objectIntersectedInformation)) {
        Object *objectIntersected = objectIntersectedInformation.o;
        Vec3 colorSum{0,0,0};
        for (auto obj: this->objects){
            if(obj != objectIntersected && obj->isLight()) {
                Vec3 vDir = (obj->getPoint() - objectIntersectedInformation.pHit).getUnitVector();
                Ray objetToLight = {objectIntersectedInformation.pHit, vDir};
                ObjectIntersectionInfo oii2;
                if(!this->intersect(objetToLight, &oii2) || oii2.o == obj) {
                    colorSum += phong(obj, objectIntersectedInformation, r, objetToLight);
                }
            }
        }
        objectColor = objectIntersected->getMaterial()->getNormalizedColor() * objectIntersected->getMaterial()->ke + colorSum;
        objectColor.e[0] = std::min(objectColor.getColorR(), 1.0f);
        objectColor.e[1] = std::min(objectColor.getColorG(), 1.0f);
        objectColor.e[2] = std::min(objectColor.getColorB(), 1.0f);
        objectColor = objectColor*255;
        return objectColor;
    }
    return {0,0,0};
}

bool Scene::intersect(const Ray &r, ObjectIntersectionInfo *info) const {
    for(auto obj : this->objects){
        if(obj->intersect(r, info)){
            return true;
        }
    }
    return false;
}


