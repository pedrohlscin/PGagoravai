//
// Created by guila on 17/11/18.
//

#include "Scene.h"


Scene::Scene() = default;


void Scene::add(Object* object){
    this->objects.push_back(object);
}

Vec3 Scene::trace(const Ray &r, int recursionLevel) const {

    ObjectIntersectionInfo oii;
    Vec3 objectColor{0,0,0};

    if (this->intersect(r, &oii)) {
        Object *objectIntersected = oii.o;
        Vec3 colorSum{0,0,0};
        for (auto obj: this->objects){

            Vec3 vDir = (obj->getPoint() - oii.pHit).getUnitVector();
            Ray objetToLight = {oii.pHit + 0.0001f*oii.normal,  vDir};
            ObjectIntersectionInfo oii2;
            if(obj != objectIntersected && obj->isLight() && (!this->intersect(objetToLight, &oii2) || oii2.o == obj) ){
                //Calculando cores em base em componentes
                Vec3 cL = obj->getMaterial()->ke * obj->getMaterial()->getNormalizedColor();
                Vec3 dC = objectIntersected->getMaterial()->kd * objectIntersected->getMaterial()->getNormalizedColor();
                Vec3 v;
                float nl = std::max(0.0f, v.dotProduct(  oii.normal.getUnitVector(), objetToLight.direction().getUnitVector()     ));
                float nv = std::max(0.0f, v.dotProduct(-r.direction().getUnitVector(), 2*nl*oii.normal.getUnitVector() - objetToLight.direction().getUnitVector()  ));
                Vec3 diff = cL * dC * nl;
                Vec3 spec = cL * pow(nv, objectIntersected->getMaterial()->alpha) * objectIntersected->getMaterial()->ks;

                colorSum += diff + spec;

            }
        }
        objectColor = objectIntersected->getMaterial()->getNormalizedColor() * objectIntersected->getMaterial()->ke + colorSum;
        objectColor.e[0] = std::min(objectColor.getCordX(), 1.0f);
        objectColor.e[1] = std::min(objectColor.getCordY(), 1.0f);
        objectColor.e[2] = std::min(objectColor.getCordZ(), 1.0f);
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


