//
// Created by guila on 17/11/18.
//

#include "Scene.h"


Scene::Scene() = default;


void Scene::add(Object* object){
    this->objects.push_back(object);
}

Vec3 Scene::trace(const Ray &r, int recursionLevel) const {
    //Phong
}

bool Scene::intersect(const Ray &r, ObjectIntersectionInfo *info) const {
    for(auto obj : this->objects){
        if(obj->intersect(r, info)){
            return true;
        }
    }
    return false;
}


