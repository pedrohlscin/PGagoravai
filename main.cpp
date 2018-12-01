#include <iostream>
#include <fstream>
#include "Object/Object.h"
#include "Camera/Camera.h"
#include "Scene/Scene.h"
#include <cstdlib>

using namespace std;


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
                Ray r = cam.getRay(u, v);
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


void leituraDOIDA(){
    string cu;
//    while(getline(cin, cu)){
//        cout << cu << endl;
//
//    }
    int resX, resY;
    string cua;
//    cin >>cua;
    cin >> resX >> resY;
    cout << resX << " " << resY << endl;
}


int main() {
    //Resolução
    leituraDOIDA();

    int width = 480;
    int height = 320;

    float resAspect = width/height;
    //Camera
    Vec3 cTarget{0.0,-0.042612,-1.0};
    Vec3 cPos {50,52,295.6};
    Vec3 cUp{0.0,1.0,0.0};

    double fov = 90.0;
    double near = 1.0;

    Camera c(cPos, fov, cTarget, near, cUp, width, height);

    Scene sc;



    saveStringToFile(imageRender(width, height,10,c,sc));

    return 0;
}