#ifndef PG_VEC3_H
#define PG_VEC3_H

#include <math.h>
#include <stdlib.h>
#include <iostream>

class Vec3  {
private:
    float e[3];

public:
    Vec3() {}
    Vec3(float e0, float e1, float e2);
    inline float getCordX() const ;
    inline float getCordY() const;
    inline float getCordZ() const;
    inline float getColorR() const ;
    inline float getColorG() const;
    inline float getColorB() const;


    // Overloading useful unary operators
    inline Vec3 operator-() const;
    inline float operator[](int i) const;
    inline float& operator[](int i);


    friend Vec3 operator+(const Vec3 &v1, const Vec3 &v2);
    friend Vec3 operator-(const Vec3 &v1, const Vec3 &v2);
    friend Vec3 operator*(const Vec3 &v1, const Vec3 &v2);
    friend Vec3 operator/(const Vec3 &v1, const Vec3 &v2);
    friend Vec3 friend operator*(float t, const Vec3 &v);
    friend Vec3 operator/(Vec3 v, float t);
    friend Vec3 operator*(const Vec3 &v, float t);

    inline Vec3& operator+=(const Vec3 &v2);
    inline Vec3& operator-=(const Vec3 &v2);
    inline Vec3& operator*=(const Vec3 &v2);
    inline Vec3& operator/=(const Vec3 &v2);
    inline Vec3& operator*=(const float t);
    inline Vec3& operator/=(const float t);

    inline float length() const;
    inline float squared_length() const;
    inline void make_unit_vector();

    inline float dotProduct(const Vec3 &v1, const Vec3 &v2);
    inline Vec3 cross(const Vec3 &v1, const Vec3 &v2);
    inline Vec3 getUnitVector(Vec3 v);

};


#endif //PG_VEC3_H