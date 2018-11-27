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
        Material *m = objectIntersected->getMaterial();
        Vec3 colorSum{0,0,0};
        for (auto obj: this->objects){
            // Checar se ta batendo nele mesmo - Tem que fazer
            Ray objetToLight = {oii.pHit, obj->getPoint()};
            if(obj != objectIntersected && obj->isLight() && !this->intersect(objetToLight)){
                Vec3 cL = obj->getMaterial()->ke * obj->getMaterial()->color;
                Vec3 dC = objectIntersected->getMaterial()->kd * objectIntersected->getMaterial()->color;
                Vec3 v;
                float nl = v.dotProduct(oii.normal, objetToLight.direction());
                float nv = v.dotProduct(r.direction(), objetToLight.direction());
                Vec3 diff = cL * dC * nl;
                Vec3 spec = cL * nv;

                colorSum += diff + spec;

            }
        }
        objectColor = oii.o->getMaterial()->color * oii.o->getMaterial()->ke + colorSum;
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


