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
            for(int k=0; k<samples; k++){
                float random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float u = (i+random) / float(sizeX);
                float v = (j+random) / float(sizeY);
                Ray r = cam.getRay(u, v, sizeX, sizeY);
                col += c.trace(r);
            }

            col/=samples;
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

    //Câmera
    Vec3 cTarget{0,0,0};
    Vec3 cPos {0,0,-2};
    Vec3 cUp{0,1,0};

    double fov = 40;
    double near = 1;

    Camera c(cPos, fov, cTarget, near, cUp, width, height);

    // Objeto
    Sphere sp({10000,0,0},9999);
    Sphere sp2({-10000,0,0},9999);
    Sphere sp3({0,10000,0},9999);
    Sphere sp4({0,-10000,0},9999);
    Sphere sp5({10000,0,-10000},9999);
    Sphere sp6({0,-1,0},1);
    //ks kd ke alp
    Sphere sp7({0,0,0},1);

    Material luca({255,20,20},0,0.7,0,1.0);
    Material luca2({255,20,20},0,0.7,0,1.0);
    Material luca3({20,255,20},0,0.7,0,1.0);
    Material luca4({20,20,255},0,0.7,0,1.0);
    Material luca5({100,100,100},0,0.7,0,1.0);

    Material luca6({145,155,155},0.0,0.7,0.2,1.0);
    Material luca7({255,255,255},1.0,0.0,0,1.0);
    //Cena
    Object o1(&sp, &luca);
    Object o2(&sp2, &luca2);
    Object o3(&sp3, &luca3);
    Object o4(&sp4, &luca4);
    Object o5(&sp5, &luca5);
    Object o6(&sp6, &luca6);
    Object o7(&sp7, &luca7);
    Scene sc;
    sc.add(&o1);
    sc.add(&o2);
    saveStringToFile(imageRender(width, height,10,c,sc));

    return 0;
}