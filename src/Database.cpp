#include "../include/Database.h"
#include <iostream>
using namespace std;

Database::~Database() {
    for (auto table : tables) {
        delete table;
    }
}

void Database::addTable(Table* table) {
    tables.push_back(table);
}

/*void Database::displayTables() const {
    for (const auto& table : tables) {
        cout << "Table: " << table->getTableName() << endl;
        table->display();
    }
}*/

// Save all tables in the database to separate files
void Database::saveAllTablesToFile() const {
    for (const auto& table : tables) {
        string filename = "../data/" + table->getTableName() + ".txt";
        table->saveToFile(filename);
        cout << "Table " << table->getTableName() << " saved to " << filename << endl;
    }
}

// Load all tables from their respective files
void Database::loadAllTablesFromFile() {
    for (auto& table : tables) {
        string filename = "../data/" + table->getTableName() + ".txt";
        table->loadFromFile(filename);
        cout << "Table " << table->getTableName() << " loaded from " << filename << endl;
    }
}
