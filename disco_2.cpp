#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

const int BYTES_POR_SECTOR = 4096;

struct Disco {
    int num_superficies;
    int num_pistas;
    int num_sectores;
    int num_platos;
    int fd;
    char* datos;

    Disco(int ns, int np, int nsx, int npd, const char* archivo): num_superficies(ns), num_pistas(np), num_sectores(nsx), num_platos(npd), fd(open(archivo, O_RDWR)), datos(static_cast<char*>(mmap(nullptr, capacidad_en_bytes(), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)))) {}

    ~Disco() {
        munmap(datos, capacidad_en_bytes());
        close(fd);
    }

    char& dato(int sup, int pis, int sec, int byte) {
        int posicion = ((sup * num_pistas + pis) * num_sectores + sec) * BYTES_POR_SECTOR + byte;
        return datos[posicion];
    }

    int capacidad_en_bytes() const {
        return num_superficies * num_pistas * num_sectores * BYTES_POR_SECTOR * num_platos;
    }

    double capacidad_en_gb() const {
        return static_cast<double>(capacidad_en_bytes()) / (1024 * 1024 * 1024);
    }
};

int main() {
    // Crear un disco con 2 superficies, 4 pistas, 8 sectores y 2 platos, con datos almacenados en el archivo "disco.dat"
    Disco mi_disco(2, 4, 8, 2, "disco.dat");

    // Acceder al byte en la posición (1, 2, 3, 100) del disco
    char& byte = mi_disco.dato(1, 2, 3, 100);

    // Modificar el byte en la posición (1, 2, 3, 100) del disco
    byte = 'A';

    // Acceder a la capacidad del disco en bytes y en GB
    int capacidad_bytes = mi_disco.capacidad_en_bytes();
    double capacidad_gb = mi_disco.capacidad_en_gb();

    std::cout << "Capacidad del disco: " << capacidad_bytes << " bytes (" << capacidad_gb << " GB)\n";

    return 0;
}
