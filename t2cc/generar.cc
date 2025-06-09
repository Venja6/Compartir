#include <iostream>
#include <fstream>
#include <random>
#include <climits>

void generarArchivo(const std::string& nombreArchivo, int megabytes) {
    const int bytesPorMB = 1024 * 1024;
    const int bytesPorEntero = sizeof(int32_t);
    const int totalEnteros = (megabytes * bytesPorMB) / bytesPorEntero;

    std::ofstream archivo(nombreArchivo, std::ios::binary);
    if (!archivo) {
        std::cerr << "Error al crear el archivo" << std::endl;
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int32_t> distrib(INT32_MIN, INT32_MAX);

    for (int i = 0; i < totalEnteros; ++i) {
        int32_t num = distrib(gen);
        archivo.write(reinterpret_cast<const char*>(&num), sizeof(num));
    }

    std::cout << "Archivo generado: " << nombreArchivo 
              << " - Tamano: " << megabytes << " MB"
              << " - Enteros: " << totalEnteros << std::endl;
}

int main() {
    // Ejemplos de tamaños (cambiar según necesidad)
    generarArchivo("1MB_int32.bin", 1);    // 1 MB = 262,144 enteros
    generarArchivo("10MB_int32.bin", 10);   // 10 MB = 2,621,440 enteros
    generarArchivo("100MB_int32.bin", 100); // 100 MB = 26,214,400 enteros

    return 0;
}