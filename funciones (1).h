#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <QString>

// Cargar imagen BMP usando QImage
unsigned char* loadPixels(QString input, int &width, int &height);

// Guardar imagen BMP usando QImage
bool exportImage(unsigned char* pixelData, int width, int height, QString archivoSalida);

// Cargar archivo de enmascaramiento con semilla
int loadSeedMasking(const QString& archivo, int& seed, unsigned char*& Sk, int& length);

//XOR, DESPLAZAMIENTO Y ROTACION

// funcion validar con los .txt

//funcion para ejecutar el caso 2 