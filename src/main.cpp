#include "../include/Database.h"
#include "../include/EmployeeTable.h"
#include <iostream>
using namespace std;

int main() {
    Database db;

    // Create Employee Table
    EmployeeTable* empTable = new EmployeeTable();
    db.addTable(empTable);

    // Load all tables from files
    db.loadAllTablesFromFile();

    // Add new employee records
    empTable->addRecord(Record({"3", "Alice Johnson", "Designer", "60000"}));
    empTable->addRecord(Record({"4", "Bob Lee", "Tester", "40000"}));

    // Display all employee records
    cout << "Employee Records:" << endl;
    db.displayTables();

    // Save all tables to files
    db.saveAllTablesToFile();

    return 0;
}
