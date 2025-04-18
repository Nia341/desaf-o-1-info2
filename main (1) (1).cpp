#include <QCoreApplication>
#include <QImage>
#include <iostream>
#include "funciones.h"

using namespace std;

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // Cargar la imagen de entrada
    int width, height;
    unsigned char* ID = loadPixels("ID.bmp", width, height);
    if (!ID) {
        cerr << "No se pudo cargar la imagen ID.bmp" << endl;
        return 1;
    }

    unsigned char* IM = loadPixels("IM.bmp", width, height);
    if (!IM) {
        cerr << "No se pudo cargar la imagen IM.bmp" << endl;
        return 1;
    }

    unsigned char* M = loadPixels("M.bmp", width, height);
    if (!M) {
        cerr << "No se pudo cargar la imagen M.bmp" << endl;
        return 1;
    }

    QString archivos[] = { "M1.txt", "M2.txt", "M3.txt", "M4.txt", "M5.txt", "M6.txt", "M7.txt" };
    unsigned char* Sk[7];
    int s[7];
    int length[7];

    for (int i = 0; i < 7; ++i) {
        Sk[i] = nullptr;
        s[i] = 0;
        length[i] = 0;
        int resultado = loadSeedMasking(archivos[i], s[i], Sk[i], length[i]);
        if (resultado != 0) {
            cerr << "Error cargando " << archivos[i].toStdString() << endl;
            return 1;
        }
    }

    ejecutarCaso2(ID, IM, M, width, height, Sk, s, length);

    delete[] ID;
    delete[] IM;
    delete[] M;
    for (int i = 0; i < 7; ++i) {
        delete[] Sk[i];
    }

    return 0;
}

