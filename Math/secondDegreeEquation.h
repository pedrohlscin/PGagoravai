//
// Created by ggfl on 07/11/18.
//

#ifndef PG_SECONDDEGREEEQUATION_H
#define PG_SECONDDEGREEEQUATION_H



class secondDegreeEquation {
private:
    double a;
    double b;
    double c;
    double deltha;
    double *roots;
public:
    secondDegreeEquation(double a, double b, double c);

    double getDeltha();

    double *getRoots();


};


#endif //PG_SECONDDEGREEEQUATION_H