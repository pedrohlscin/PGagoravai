#include <iostream>
#include <fstream>
#include "Object/Object.h"
#include "Camera/Camera.h"
#include "Scene/Scene.h"




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
    //Iterando ao longo dos pixels e renderizando
    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {
            float u = float(j) / float(sizeX);
            float v = float(i) / float(sizeY);
            //std::cout << u << " " << v << std::endl;
            Ray r = cam.getRay(u, v, sizeX, sizeY);
            col = c.trace(r);
            col/=4;
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
    Vec3 cTarget{0,0,1};
    Vec3 cPos {0,0,0};
    Vec3 cUp{0,1,0};

    double fov = 40;
    double near = 1;

    Camera c(cPos, fov, cTarget, near, cUp, width, height);

    // Objeto
    Sphere sp({0,0,4},0.5);
    Material luca({200,80,13},0.2,0.2,0.7,0.3);

    Object o(&sp, &luca);

    Sphere floor({0,-1.5,4},0.5);
    Material floor_mat({255,255,255},0.1,0.2,1.0,0.3);
    Object floor_obj(&floor, &floor_mat);

    //Cena
    Scene sc;
    sc.add(&o);
    sc.add(&floor_obj);

    saveStringToFile(imageRender(width, height,10,c,sc));

    return 0;
}