cmake_minimum_required(VERSION 3.12)
project(PGagoravai)

set(CMAKE_CXX_STANDARD 14)

add_executable(PGagoravai main.cpp
        Camera/Camera.cpp
        Camera/Camera.h
        Vector/Vec3.cpp
        Vector/Vec3.h
        Math/secondDegreeEquation.cpp
        Math/secondDegreeEquation.h
        Scene/Scene.cpp
        Scene/Scene.h
        Object/Object.cpp
        Object/Sphere.cpp
        Object/Geometry.h Object/Object.h Object/Material.cpp Object/Material.h Object/ObjectIntersectionInfo.h)

