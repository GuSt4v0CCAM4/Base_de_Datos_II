#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct Record {
    int id;
    string name;
    string email;
    string phone;
};

class DBMS {
public:
    DBMS() {
        ifstream infile("database.txt");
        if (!infile.good()) {
            ofstream outfile("database.txt");
            outfile.close();
        }
    }
    void execute_query(string query) {
        stringstream ss(query);
        string operation;
        ss >> operation;
        if (operation == "INSERT") {
            insert_record(ss);
        }
        else if (operation == "FIND") {
            find_record(ss);
        }
        else if (operation == "LIST") {
            list_all_records();
        }
        else if (operation == "CREATE") {
            create_record(ss);
        }
        else {
            cout << "Query invalidado" << endl;
        }
    }

private:
    void insert_record(stringstream& ss) {
        Record record;
        ss >> record.id >> record.name >> record.email >> record.phone;

        ofstream outfile("database.txt", ios_base::app);
        outfile << record.id << ' ' << record.name << ' ' << record.email << ' ' << record.phone << endl;
        outfile.close();

        cout << "Registro agregado" << endl;
    }

    void find_record(stringstream& ss) {
        int id;
        ss >> id;

        ifstream infile("database.txt");
        string line;
        while (getline(infile, line)) {
            stringstream record_ss(line);
            int record_id;
            record_ss >> record_id;
            if (record_id == id) {
                Record record;
                record.id = record_id;
                record_ss >> record.name >> record.email >> record.phone;
                print_record(record);
                return;
            }
        }

        cout << "Registro no encontrado" << endl;
    }

    void list_all_records() {
        ifstream infile("database.txt");
        string line;
        while (getline(infile, line)) {
            stringstream record_ss(line);
            Record record;
            record_ss >> record.id >> record.name >> record.email >> record.phone;
            print_record(record);
        }
    }

    void create_record(stringstream& ss) {
        vector<string> attributes;
        string attribute;
        while (ss >> attribute) {
            attributes.push_back(attribute);
        }

        ofstream outfile("database.txt", ios_base::app);
        outfile << generate_id() << ' ';
        for (const auto& attr : attributes) {
            outfile << attr << ' ';
        }
        outfile << endl;
        outfile.close();

        cout << "Registro agregado" << endl;
    }

    int generate_id() {
        int max_id = 0;
        ifstream infile("database.txt");
        string line;
        while (getline(infile, line)) {
            stringstream record_ss(line);
            int record_id;
            record_ss >> record_id;
            max_id = max(max_id, record_id);
        }
        return max_id + 1;
    }

    void print_record(const Record& record) {
        cout << "ID: " << record.id << endl;
        cout << "Name: " << record.name << endl;
        cout << "Email: " << record.email << endl;
        cout << "Phone: " << record.phone << endl;
        cout << endl;
    }
};

int main() {
    DBMS dbms;
    string query;
    cout << "Escribe 'QUIT' para salir: " << endl;
    getline(cin, query);
    while (query != "QUIT") {
        dbms.execute_query(query);
        getline(cin, query);
    }
}

