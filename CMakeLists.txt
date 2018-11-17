cmake_minimum_required(VERSION 3.12)
project(PGagoravai)

set(CMAKE_CXX_STANDARD 14)

add_executable(PGagoravai main.cpp Camera/Camera.cpp Camera/Camera.h Vector/Vec3.cpp Vector/Vec3.h Math/secondDegreeEquation.cpp Object/Geometry.cpp)

