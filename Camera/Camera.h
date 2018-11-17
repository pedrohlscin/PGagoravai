//
// Created by guila on 17/11/18.
//

#ifndef PGAGORAVAI_CAMERA_H
#define PGAGORAVAI_CAMERA_H


#include "../Vector/Vec3.h"

class Camera {
private:
    Vec3 position;
    Vec3 axisX;
    Vec3 axisY;
    Vec3 axisZ;
    double fov;
    double near;

public:
    Camera(double, Vec3, double, Vec3, double, Vec3);

    Ray getRay(double, double, int, int) const;
};


#endif //PGAGORAVAI_CAMERA_H
