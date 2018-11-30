#include <iostream>
#include <fstream>
#include "Object/Object.h"
#include "Camera/Camera.h"
#include "Scene/Scene.h"
#include <cstdlib>




//Apernas criando a imagem
void saveStringToFile(std::string imagePBM){
    std::ofstream myFile;
    myFile.open("saida.pbm");
    myFile << imagePBM;
    myFile.close();
}

std::string imageRender(int sizeX, int sizeY, int sizeZ, Camera cam, Scene c ){
    std::string stringedFile = "";
    stringedFile.append("P3\n" + std::to_string(sizeX) + " " + std::to_string(sizeY) + "\n255\n");
    Vec3 col(0, 0, 0);
    int samples=3;
    //Iterando ao longo dos pixels e renderizando
    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {
            float u = float(j) / float(sizeX);
            float v = float(i) / float(sizeY);
            //std::cout << u << " " << v << std::endl;
            Ray r = cam.getRay(u, v, sizeX, sizeY);
            col = c.trace(r);
            int ir = int(col[0]);
            int ig = int(col[1]);
            int ib = int(col[2]);
            //Escrevendo os pixels na imagem
            stringedFile.append(std::to_string(ir) + " " + std::to_string(ig) + " " + std::to_string(ib) + "\n");
        }
    }

    return stringedFile;
}


int main() {
    //Resolução
    float resAspect = 320/200;
    int width = 320;
    int height = 200;

    //Camera
    Vec3 cTarget{0,0,1};
    Vec3 cPos {0,0,0};
    Vec3 cUp{0,1,0};

    double fov = 40;
    double near = 1;

    Camera c(cPos, fov, cTarget, near, cUp, width, height);

    // Objeto
    Sphere sp({0,0,4},0.5);
    Material luca({200,80,13},0.5,0.5,0.1,1);

    Object o(&sp, &luca);


    Sphere ceilling({0,-10500,4},9999);
    Material ceillingMat({255,255,255},0.4,0.4,1.0,1);
    Object ceillingObj(&ceilling, &ceillingMat);


    Sphere rightWall({-11300,0,4},9999);
    Material rightWallMat({0,255,0},0.4,0.4,1.0,1);
    Object rightWallObj(&rightWall, &rightWallMat);


    Sphere leftWall({11300,0,4},9999);
    Material leftWallMat({255,0,0},0.4,0.4,1.0,1);
    Object leftWallObj(&leftWall, &leftWallMat);


    Sphere floor({0,10500,4},9999);
    Material floorMat({255,255,255},0.4,0.4,1.0,1);
    Object floorObj(&floor, &floorMat);

    //Cena
    Scene sc;
    sc.add(&o);
    sc.add(&ceillingObj);
    sc.add(&rightWallObj);
    sc.add(&leftWallObj);
    sc.add(&floorObj);
    saveStringToFile(imageRender(width, height,10,c,sc));

    return 0;
}