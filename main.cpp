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
    int samples=5;
    //Iterando ao longo dos pixels e renderizando
    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {

            for(int k=0; k<samples; k++){
                float random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float u = (j+random) / float(sizeX);
                float v = (i+random) / float(sizeY);
                Ray r = cam.getRay(u, v, sizeX, sizeY);
                col += c.trace(r);
            }

            col = col / samples;
            int ir = std::min(255, int(col[0]));
            int ig = std::min( 255, int(col[1]));
            int ib = std::min( 255, int(col[2]));
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
    Sphere sp({0,-1,4},0.25);
    Material luca({255,255,255},0,0,1,1);

    Object o(&sp, &luca);


    Sphere ceilling({0,-10000,0},9999);
    Material ceillingMat({255,0,0},0,1.0,0,1);
    Object ceillingObj(&ceilling, &ceillingMat);

    Sphere floor({0,10000,0},9999);
    Material floorMat({0,255,0},0,1.0,0,1);
    Object floorObj(&floor, &floorMat);

    Sphere rWall({11000,0,4},9999);
    Material rWallMat({0,0,255},0,1.0,0,1);
    Object rWallObj(&rWall, &rWallMat);



    //Cena
    Scene sc;
    sc.add(&o);

    sc.add(&ceillingObj);
    sc.add(&floorObj);
    saveStringToFile(imageRender(width, height,10,c,sc));

    return 0;
}