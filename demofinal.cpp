#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
struct Sector {
    std::string data[100];
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
// Función para obtener el siguiente sector disponible en el disco abstracto
int obtenerSiguienteSector() {
    int sector = siguienteSector;
    siguienteSector++;
    // Considera implementar la lógica para manejar el desbordamiento de sectores aquí

    return sector;
}

// Función para crear un archivo CSV y guardar los atributos en el sector correspondiente del disco abstracto
void create(const std::string& nombreArchivo, const std::vector<std::string>& atributos, DiscoAbstracto& disco) {
    // Crear el archivo CSV
    std::string nombreCompleto = nombreArchivo + ".csv";
    std::ofstream archivo(nombreCompleto);
    if (archivo.is_open()) {
        // Escribir los atributos separados por comas
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

    // Guardar en el sector correspondiente del disco abstracto
    int sector = obtenerSiguienteSector();
    disco.platos[0].superficies[0].pista[0].sectores[0].data[sector] = nombreArchivo;
    archivo.close();
}

// Función para insertar atributos en un archivo CSV y escribirlos en el sector correspondiente del disco abstracto
void insert(const std::string& nombreArchivo, const std::vector<std::string>& atributos, DiscoAbstracto& disco) {
    // Abrir el archivo CSV en modo de escritura
    std::ofstream archivo(nombreArchivo, std::ios::app);
    if (!archivo) {
        std::cout << "Error al abrir el archivo CSV." << std::endl;
        return;
    }

    // Escribir los atributos separados por comas
    for (const auto& atributo : atributos) {
        archivo << atributo << ",";
    }
    archivo << std::endl;

    // Guardar en el sector correspondiente del disco abstracto
    // (aquí debes implementar la lógica para determinar el sector donde se guarda)
    int sector = obtenerSiguienteSector();
    disco.platos[0].superficies[0].pista[0].sectores[0].data[sector] = atributos[0];
    disco.platos[0].superficies[0].pista[0].sectores[0].data[sector] = atributos[1];
    disco.platos[0].superficies[0].pista[0].sectores[0].data[sector] = atributos[2];


    archivo.close();
}

// Función para seleccionar atributos de un archivo CSV y leerlos desde el sector correspondiente del disco abstracto
void select(const std::string& nombreArchivo, const std::vector<std::string>& atributos, const DiscoAbstracto& disco) {
    // Abrir el archivo CSV en modo de lectura
    std::string nombreCompleto = nombreArchivo + ".csv";
    std::ifstream archivo(nombreCompleto);
    if (!archivo) {
        std::cout << "Error al abrir el archivo CSV." << std::endl;
        return;
    }

    // Leer línea por línea del archivo CSV
    std::string linea;
    while (std::getline(archivo, linea)) {
        // Convertir la línea en un stream para facilitar su manipulación
        std::stringstream ss(linea);
        std::string atributo;
        std::vector<std::string> atributosEncontrados;

        // Leer los atributos separados por comas
        while (std::getline(ss, atributo, ',')) {
            atributosEncontrados.push_back(atributo);
        }


        // Comparar los atributos encontrados con los atributos solicitados
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

        // Si los atributos coinciden, imprimir la línea
        if (atributosCoinciden) {
            std::cout << linea << std::endl;
        }
    }

    archivo.close();
}

// Función para eliminar una línea correspondiente a un atributo en un archivo CSV y en el sector correspondiente del disco abstracto
void eliminar(const std::string& nombreArchivo, const std::string& atributo, const DiscoAbstracto& disco) {
    // Abrir el archivo CSV en modo de lectura
    std::ifstream archivo(nombreArchivo);
    if (!archivo) {
        std::cout << "Error al abrir el archivo CSV." << std::endl;
        return;
    }

    // Crear un archivo temporal para guardar las líneas que no se eliminarán
    std::ofstream archivoTemporal(nombreArchivo + ".tmp");
    if (!archivoTemporal) {
        std::cout << "Error al crear el archivo temporal." << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        // Convertir la línea en un stream para facilitar su manipulación
        std::stringstream ss(linea);
        std::string atributoActual;
        bool eliminarLinea = false;

        // Leer los atributos separados por comas y comparar con el atributo a eliminar
        while (std::getline(ss, atributoActual, ',')) {
            if (atributoActual == atributo) {
                eliminarLinea = true;
                break;
            }
        }

        // Si no se debe eliminar la línea, copiarla en el archivo temporal
        if (!eliminarLinea) {
            archivoTemporal << linea << std::endl;
        }
    }

    archivo.close();
    archivoTemporal.close();

    // Reemplazar el archivo original con el archivo temporal
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
