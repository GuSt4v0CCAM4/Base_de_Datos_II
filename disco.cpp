#include <iostream>
#include <vector>

using namespace std;

struct Sector {
    int numero;
    string datos;
    int capacidad;
};
struct Pista {
    int numero;
    vector<Sector> sectores;
};

struct Superficie {
    int numero;
    vector<Pista> pistas;
};

struct Plato {
    int numero;
    vector<Superficie> superficies;
};

struct Disco {
    vector<Plato> platos;
};

Sector& obtener_sector(Disco& disco, int num_plato, int num_superficie, int num_pista, int num_sector) {
    return disco.platos[num_plato].superficies[num_superficie].pistas[num_pista].sectores[num_sector];
}

int main() {
    // Disco con 16 platos, dos superficies por plato, 16384 pistas por superficie, 128 sectores por pista
    // y 4096 bytes por sector
    Disco mi_disco;
    mi_disco.platos.resize(2);
    for (int i = 0; i < 2; i++) {
        mi_disco.platos[i].numero = i;
        mi_disco.platos[i].superficies.resize(4);
        for (int j = 0; j < 4; j++) {
            mi_disco.platos[i].superficies[j].numero = j;
            mi_disco.platos[i].superficies[j].pistas.resize(3);
            for (int k = 0; k < 3; k++) {
                mi_disco.platos[i].superficies[j].pistas[k].numero = k;
                mi_disco.platos[i].superficies[j].pistas[k].sectores.resize(2);
                for (int l = 0; l < 2; l++) {
                    mi_disco.platos[i].superficies[j].pistas[k].sectores[l].numero = l;
                    mi_disco.platos[i].superficies[j].pistas[k].sectores[l].datos = "Datos del sector " + to_string(l) + " en la pista " + to_string(k) + " de la superficie " + to_string(j) + " del plato " + to_string(i);
                    mi_disco.platos[i].superficies[j].pistas[k].sectores[l].capacidad = 4096 * l * k * j * i;
                }
            }
        }
    }

    Sector& mi_sector = obtener_sector(mi_disco, 1, 1, 2, 1);
    cout << mi_sector.datos << " del disco con capacidad de " << mi_sector.capacidad << " bytes" <<endl;

    return 0;
}
