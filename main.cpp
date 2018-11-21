#include <iostream>
#include <fstream>
#include "Object/Object.h"
#include "Camera/Camera.h"
#include "Scene/Scene.h"





void saveStringToFile(std::string imagePBM){
    std::ofstream myFile;
    myFile.open("saida.pbm");
    myFile << imagePBM;
    myFile.close();
}

std::string imageRender(int sizeX, int sizeY, int sizeZ, Camera cam, Scene c ){
    std::string stringedFile;
    stringedFile.append("P3\n" + std::to_string(sizeX) + " " + std::to_string(sizeY) + "\n255\n");

    for (int j = sizeY-1; j >= 0; j--) {
        for (int i = 0; i < sizeX; i++) {
            Vec3 col(0, 0, 0);
            for (int s=0; s < sizeZ; s++) {
                float u = float(i) / float(sizeX);
                float v = float(j) / float(sizeY);
                Ray r = cam.getRay(u, v, sizeX, sizeY);
                Vec3 p = r.positionAt(2.0);
                col += c.trace(r);
            }
            col /= float(sizeZ);
            col = Vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
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
    Vec3 cPos {13,2,6};
    Vec3 cUp{0, 1,0};
    Vec3 cTarget{0,0,0};
    double fov = 0.1;
    double near = 10.0;

    Camera c(cPos, fov, cTarget, near, cUp, width, height);

    // Objeto
    Sphere sp({0,1,1},10);
    Material luca({100,100,100},0.2,0.2,0.2,0.3);

    Object o(&sp, &luca);

    //Cena
    Scene sc;
    sc.add(&o);

    saveStringToFile(imageRender(width, height,10,c,sc));

    return 0;
}