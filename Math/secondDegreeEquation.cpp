//
// Created by ggfl on 07/11/18.
//

#include <cstdio>
#include <cmath>

#include "secondDegreeEquation.h"

secondDegreeEquation::secondDegreeEquation(double a, double b, double c) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->deltha = (b*b) - (4.0*a*c);
    if(deltha > 0){
        this->roots = new double[2];
        roots[0] = (-b - sqrt(deltha))/(2.0*a);
        roots[1] = (-b + sqrt(deltha))/(2.0*a);
    }

    if(deltha < 0){
        this->roots = nullptr;
    }

    else{
        this->roots = new double[1];
        roots[0] = (-b - sqrt(deltha))/(2.0*a);
    }

}

double secondDegreeEquation::getDeltha() {
    return this->deltha;
}

double *secondDegreeEquation::getRoots() {
    return this->roots;
}