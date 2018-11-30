cmake_minimum_required(VERSION 3.12)
project(PGagoravai)

set(CMAKE_CXX_STANDARD 14)

include_directories(Camera)
include_directories(Math)
include_directories(Object)
include_directories(Scene)
include_directories(Vector)

add_executable(PGagoravai
        Camera/Camera.cpp
        Camera/Camera.h
        Camera/Ray.h
        Math/secondDegreeEquation.cpp
        Math/secondDegreeEquation.h
        Object/Geometry.h
        Object/Material.cpp
        Object/Material.h
        Object/Object.cpp
        Object/Object.h
        Object/ObjectIntersectionInfo.h
        Object/Sphere.cpp
        Scene/Scene.cpp
        Scene/Scene.h
        Vector/Vec3.cpp
        Vector/Vec3.h
        main.cpp)
