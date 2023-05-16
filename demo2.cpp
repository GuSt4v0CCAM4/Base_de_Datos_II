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

void insert(string data_file)
{
    string new_data;
    cout << "Ingrese los nuevos datos separados por comas: ";
    getline(cin, new_data);

    // Escribir los nuevos datos en el archivo
    ofstream file(data_file, ios::app);
    file << new_data << endl;
    file.close();
}

void del(string data_file)
{
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
    }

    read_file.close();
    write_file.close();

    // Reemplazar el archivo original con el archivo temporal
    remove(data_file.c_str());
    rename(temp_file.c_str(), data_file.c_str());
}

void select(string data_file)
{
    string query;
    cout << "Ingrese el query de select: ";
    getline(cin, query);

    // Imprimir los datos que coinciden con el query
    ifstream file(data_file);

    string line;

    while (getline(file, line))
    {
        if (line.find(query) != string::npos)
        {
            cout << line << endl;
        }
    }

    file.close();
}

int main()
{

    string data_file = "data.txt";

    // Verificar si el archivo existe
    ifstream file(data_file);

    if (!file.is_open())
    {
        cerr << "Error al abrir el archivo" << endl;
        return 1;
    }

    file.close();

    // Aquí puedes trabajar con los datos almacenados en el archivo

    string query;

    cout << "Ingrese el query (insert, del o select): ";

    getline(cin, query);

    if (query == "insert")
        insert(data_file);

    else if (query == "del")
        del(data_file);

    else if (query == "select")
        select(data_file);

    else
        cout << "Query inválido" << endl;

    return 0;
}
