#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void create()
{
    string file_name;
    cout << "Ingrese el nombre del archivo: ";
    getline(cin, file_name);

    // Crear el archivo con el nombre especificado por el usuario
    ofstream file(file_name + ".txt");

    // Pedir al usuario que ingrese los atributos
    string attributes;
    cout << "Ingrese los atributos separados por comas: ";
    getline(cin, attributes);

    // Escribir los atributos en el archivo
    file << attributes << endl;

    file.close();
}
//funcion para leer archivos csv

void insert(string data_file)
{
    // Verificar si el archivo existe
    ifstream file(data_file);

    if (!file.is_open())
    {
        cerr << "Error al abrir el archivo" << endl;
        return;
    }

    file.close();

    // Pedir al usuario que ingrese los nuevos datos
    string new_data;
    cout << "Ingrese los nuevos datos separados por comas: ";
    getline(cin, new_data);

    // Verificar que los atributos existan en el archivo
    ifstream read_file(data_file);

    string line;

    getline(read_file, line);

    read_file.close();

    size_t pos = 0;

    while ((pos = line.find(",")) != string::npos)
    {
        string attribute = line.substr(0, pos);

        if (new_data.find(attribute) == string::npos)
        {
            cerr << "Error: El atributo " << attribute << " no existe en el archivo" << endl;
            return;
        }

        line.erase(0, pos + 1);

        if (line.empty())
            break;
    }

    // Escribir los nuevos datos en el archivo
    ofstream write_file(data_file, ios::app);

    write_file << new_data << endl;

    write_file.close();
}

void del(string data_file)
{
    // Verificar si el archivo existe
    ifstream file(data_file);

    if (!file.is_open())
    {
        cerr << "Error al abrir el archivo" << endl;
        return;
    }

    file.close();

    // Pedir al usuario que ingrese el query de delete
    string query;

    cout << "Ingrese el query de delete: ";

    getline(cin, query);

    // Crear un archivo temporal para almacenar los datos que no coinciden con el query
    string temp_file = "temp.txt";

    ifstream read_file(data_file);

    ofstream write_file(temp_file);

    string line;

    while (getline(read_file, line))
    {
        if (line.find(query) == string::npos)
        {
            write_file << line << endl;
        }

        else
        {
            cout << "Se eliminó la siguiente línea: " << line << endl;
        }

        line.clear();

        if (read_file.eof())
            break;

        read_file.seekg(read_file.tellg());

        read_file.peek();

        if (read_file.eof())
            break;

        read_file.seekg(-1, ios::cur);

        char c = read_file.peek();

        if (c == '\n')
            write_file << endl;

        else if (read_file.eof())
            break;

        else if (read_file.tellg() == 0)
            write_file << c;

        else
            write_file << c;

        read_file.ignore();

        if (read_file.eof())
            break;

        read_file.seekg(read_file.tellg());

        read_file.peek();

        if (read_file.eof())
            break;

        read_file.seekg(-1, ios::cur);

        c = read_file.peek();

        if (c == '\n')
            write_file << endl;

        else if (read_file.eof())
            break;

        else if (read_file.tellg() == 0)
            write_file << c;

        else
            write_file << c;

        read_file.ignore();

        if (read_file.eof
