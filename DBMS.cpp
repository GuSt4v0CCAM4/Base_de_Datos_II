#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
struct Sector {
    std::string data;
    int siguienteSector;
};
struct Pista {
    Sector sectores[5];
};
struct Superficie {
    Pista pista[5];
};

struct Plato {
    Superficie superficies[2];
};

struct DiscoAbstracto {
    Plato platos[2];
};

int siguienteSector = 0;
// sacar el sector disponible en el disco abstracto
int obtenerSiguienteSector() {
    int sector = siguienteSector;
    siguienteSector++;
    return sector;
}

void create(const std::string& nombreArchivo, const std::vector<std::string>& atributos, DiscoAbstracto& disco) {
    std::string nombreCompleto = nombreArchivo + ".csv";
    std::ofstream archivo(nombreCompleto);
    if (archivo.is_open()) {
        for (size_t i = 0; i < atributos.size(); i++) {
            archivo << atributos[i];
            if (i < atributos.size() - 1) {
                archivo << ",";
            }
        }
        archivo << std::endl;

        archivo.close();
        std::cout << "Archivo CSV creado exitosamente." << std::endl;
    } else {
        std::cout << "No se pudo crear el archivo CSV." << std::endl;
    }
    // tratar de guardar en el sector correspondiente del disco abstracto
    int sector = obtenerSiguienteSector();
    disco.platos[0].superficies[0].pista[0].sectores[sector].data = nombreArchivo;

    archivo.close();
}

void insert(const std::string& nombreArchivo, const std::vector<std::string>& atributos, DiscoAbstracto& disco) {
    std::ofstream archivo(nombreArchivo, std::ios::app);
    if (!archivo) {
        std::cout << "Error al abrir el archivo CSV." << std::endl;
        return;
    }

    for (const auto& atributo : atributos) {
        archivo << atributo << ",";
    }
    archivo << std::endl;


    int sector = obtenerSiguienteSector();
    disco.platos[0].superficies[0].pista[0].sectores[sector].data = atributos[0];
    disco.platos[0].superficies[0].pista[0].sectores[sector].data = atributos[1];
    disco.platos[0].superficies[0].pista[0].sectores[sector].data = atributos[2];


    archivo.close();
}

void select(const std::string& nombreArchivo, const std::vector<std::string>& atributos, const DiscoAbstracto& disco) {
    std::string nombreCompleto = nombreArchivo + ".csv";
    std::ifstream archivo(nombreCompleto);
    if (!archivo) {
        std::cout << "Error al abrir el archivo CSV." << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string atributo;
        std::vector<std::string> atributosEncontrados;

        while (std::getline(ss, atributo, ',')) {
            atributosEncontrados.push_back(atributo);
        }

        bool atributosCoinciden = true;
        for (const auto& atributoSolicitado : atributos) {
            bool encontrado = false;
            for (const auto& atributoEncontrado : atributosEncontrados) {
                if (atributoEncontrado == atributoSolicitado) {
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                atributosCoinciden = false;
                break;
            }
        }

        if (atributosCoinciden) {
            std::cout << linea << std::endl;
        }
    }

    archivo.close();
}
void eliminar(const std::string& nombreArchivo, const std::string& atributo, const DiscoAbstracto& disco) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo) {
        std::cout << "Error al abrir el archivo CSV." << std::endl;
        return;
    }

    std::ofstream archivoTemporal(nombreArchivo + ".tmp");
    if (!archivoTemporal) {
        std::cout << "Error al crear el archivo temporal." << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string atributoActual;
        bool eliminarLinea = false;

        while (std::getline(ss, atributoActual, ',')) {
            if (atributoActual == atributo) {
                eliminarLinea = true;
                break;
            }
        }

        if (!eliminarLinea) {
            archivoTemporal << linea << std::endl;
        }
    }

    archivo.close();
    archivoTemporal.close();

    std::remove(nombreArchivo.c_str());
    std::rename((nombreArchivo + ".tmp").c_str(), nombreArchivo.c_str());
}

int main() {
    DiscoAbstracto disco;

    while (true) {
        std::string consulta;
        std::cout << "Ingrese una consulta (CREATE, INSERT, SELECT, DELETE) o 'salir' para terminar: ";
        std::getline(std::cin, consulta);

        if (consulta == "salir") {
            break;
        } else if (consulta == "CREATE") {
            std::string nombreArchivo;
            std::vector<std::string> atributos;
            std::cout << "Ingrese el nombre del archivo CSV: ";
            std::getline(std::cin, nombreArchivo);
            std::cout << "Ingrese los atributos separados por coma: ";
            std::string atributosStr;
            std::getline(std::cin, atributosStr);
            std::stringstream ss(atributosStr);
            std::string atributo;
            while (std::getline(ss, atributo, ',')) {
                atributos.push_back(atributo);
            }
            create(nombreArchivo, atributos, disco);
        } else if (consulta == "INSERT") {
            std::string nombreArchivo;
            std::vector<std::string> atributos;
            std::cout << "Ingrese el nombre del archivo CSV: ";
            std::getline(std::cin, nombreArchivo);
            std::cout << "Ingrese los atributos separados por coma: ";
            std::string atributosStr;
            std::getline(std::cin, atributosStr);
            std::stringstream ss(atributosStr);
            std::string atributo;
            while (std::getline(ss, atributo, ',')) {
                atributos.push_back(atributo);
            }
            insert(nombreArchivo, atributos, disco);
        } else if (consulta == "SELECT") {
            std::string nombreArchivo;
            std::vector<std::string> atributos;
            std::string sector;
            std::cout << "Ingrese el nombre del archivo CSV: ";
            std::getline(std::cin, nombreArchivo);
            std::cout << "Ingrese los atributos separados por coma: ";
            std::string atributosStr;
            std::getline(std::cin, atributosStr);
            std::stringstream ss(atributosStr);
            std::string atributo;
            while (std::getline(ss, atributo, ',')) {
                atributos.push_back(atributo);
            }
            select(nombreArchivo, atributos, disco);
        } else if (consulta == "DELETE") {
            std::string nombreArchivo;
            std::string atributo;
            std::cout << "Ingrese el nombre del archivo CSV: ";
            std::getline(std::cin, nombreArchivo);
            std::cout << "Ingrese el atributo a eliminar: ";
            std::getline(std::cin, atributo);
            eliminar(nombreArchivo, atributo, disco);
        } else {
            std::cout << "Consulta no válida." << std::endl;
        }
    }

    return 0;
}
