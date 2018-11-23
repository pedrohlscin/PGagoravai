//
// Created by guila on 17/11/18.
//

#include "Camera.h"

Camera::Camera(Vec3 position, double fov, Vec3 target, double near, Vec3 up, int width, int height) {
    this->axisZ = (position - target).getUnitVector();
    this->axisY = axisZ.cross(up, axisZ).getUnitVector();
    this->axisX = axisZ.cross(axisZ, axisY).getUnitVector();

    this->aspect = (float) width/ (float )height;
    this->near = near;
    this->fov = fov*M_PI/180;
    this->position = position;
}

Ray Camera::getRay(double x, double y, int width, int height) const {
    double halfHeight = this->near * tanf(this->fov/2);
    double halfWidth = aspect * halfHeight;

    double pointX =  halfWidth  * (2.0 * (x + 0.5) - 1);
    double pointY =  halfHeight * (1 - 2.0 * (y + 0.5 ));
    double pointZ = -1;

    //mudando a base
    double pX = this->axisX.getCordX() * pointX + this->axisX.getCordY() * pointY + this->axisX.getCordZ() * pointZ;
    double pY = this->axisY.getCordX() * pointX + this->axisY.getCordY() * pointY + this->axisY.getCordZ() * pointZ;
    double pZ = this->axisZ.getCordX() * pointX + this->axisZ.getCordY() * pointY + this->axisZ.getCordZ() * pointZ;

    Vec3 point(pX, pY, pZ);


    return Ray(position, (point-position).getUnitVector());
}
