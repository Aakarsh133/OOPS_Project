#ifndef DATABASE_H
#define DATABASE_H

#include "../include/Table.h"
#include <vector>
#include <string>

class Database {
private:
    std::vector<Table*> tables;

public:
    ~Database();

    void addTable(Table* table);
    void displayTables() const;

    // New file handling methods for the entire database
    void saveAllTablesToFile() const;
    void loadAllTablesFromFile();

};

#endif
