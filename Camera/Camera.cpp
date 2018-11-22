//
// Created by guila on 17/11/18.
//

#include "Camera.h"

Camera::Camera(Vec3 position, double fov, Vec3 target, double near, Vec3 up, int width, int height) {
    this->axisZ = (position - target).getUnitVector();
    this->axisX = axisZ.cross(up, axisZ).getUnitVector();
    this->axisY = axisZ.cross(axisZ, axisX).getUnitVector();

    this->aspect = (float) width/ (float )height;
    this->near = near;
    this->fov = fov*M_PI/180;
    this->position = position;
}

Ray Camera::getRay(double x, double y, int width, int height) const {
    double halfHeight = this->near * tanf(this->fov/2);
    double halfWidth = aspect * halfHeight;

    // Erro pode estar aqui - Temos que mudar a base
    double pointX = halfHeight * (2.0 * ((x/width) - 0.5 ));
    double pointY = -halfWidth  * (2.0 * ((y/height) - 0.5));
    double pointZ = -this->near;

    //mudando a base
    pointX = this->axisX.getCordX() * pointX + this->axisX.getCordY() * pointY + this->axisX.getCordZ() * pointZ;
    pointY = this->axisY.getCordX() * pointX + this->axisY.getCordY() * pointY + this->axisY.getCordZ() * pointZ;
    pointZ = this->axisZ.getCordX() * pointX + this->axisZ.getCordY() * pointY + this->axisZ.getCordZ() * pointZ;

    Vec3 point(pointX, pointY, pointZ);


    return Ray(position, point-position);
}
