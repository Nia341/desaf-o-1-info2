#include "funciones.h"
#include <QImage>
#include <QFile>
#include <QTextStream>
#include <iostream>
using namespace std;

unsigned char* loadPixels(QString input, int &width, int &height) {//funcion dada por el profe
    QImage image;
    if (!image.load(input)) {
        cout << "No se pudo cargar la imagen." << endl;
        return nullptr;
    }

    width = image.width();
    height = image.height();
    int size = width * height * 3;

    unsigned char* pixels = new unsigned char[size];

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            QRgb color = image.pixel(x, y);
            int index = (y * width + x) * 3;
            pixels[index] = qRed(color);
            pixels[index + 1] = qGreen(color);
            pixels[index + 2] = qBlue(color);
        }
    }

    return pixels;
}

bool exportImage(unsigned char* pixelData, int width, int height, QString archivoSalida) {//funcion dada por el profe
    QImage nuevaImagen(width, height, QImage::Format_RGB888);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = (y * width + x) * 3;
            int r = pixelData[index];
            int g = pixelData[index + 1];
            int b = pixelData[index + 2];
            nuevaImagen.setPixel(x, y, qRgb(r, g, b));
        }
    }

    return nuevaImagen.save(archivoSalida);
}

int loadSeedMasking(const QString& archivo, int& seed, unsigned char*& Sk, int& length) {//funcion dada por el profe
    QFile file(archivo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cerr << "No se pudo abrir el archivo " << archivo.toStdString() << endl;
        return -1;
    }

    QTextStream in(&file);
    if (in.atEnd()) return -1;

    QStringList primeraLinea = in.readLine().split(',');
    if (primeraLinea.size() < 4) return -1;

    seed = primeraLinea[0].toInt();
    int width = primeraLinea[1].toInt();
    int height = primeraLinea[2].toInt();
    length = width * height * 3;

    Sk = new unsigned char[length];
    int index = 0;

    while (!in.atEnd() && index < length) {
        QString linea = in.readLine();
        QStringList valores = linea.split(',');

        if (valores.size() < 3) continue;

        Sk[index++] = static_cast<unsigned char>(valores[0].toInt());
        Sk[index++] = static_cast<unsigned char>(valores[1].toInt());
        Sk[index++] = static_cast<unsigned char>(valores[2].toInt());
    }

    file.close();
    return 0;
}

// operaciones inversas(XOR, Rotaciones y Desplazamiento)

// funcion validar con los .txt

//funcion para ejecutar el caso 2 