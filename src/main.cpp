#include "../include/Database.h"
#include "../include/Table.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    Database db;
    Table* userTable = nullptr;

    // Get table name from user
    string tableName;
    cout << "Enter the name of the table: ";
    getline(cin, tableName);

    // Check if table already exists (by trying to load it from a file)
    string filename = "../data/" + tableName + ".txt";
    ifstream infile(filename);
    if (infile.good()) {
        // If file exists, load the table
        vector<string> dummyFields;  // Fields will be overwritten by loadFromFile
        userTable = new Table(tableName, dummyFields);
        userTable->loadFromFile(filename);
        cout << "Table " << tableName << " loaded from file." << endl;
    } else {
        // If file doesn't exist, create a new table with user-defined fields
        vector<string> fields;
        int numFields;
        cout << "Enter the number of fields: ";
        cin >> numFields;
        cin.ignore();  // Ignore the newline after the number input

        for (int i = 0; i < numFields; ++i) {
            string field;
            cout << "Enter field " << (i + 1) << ": ";
            getline(cin, field);
            fields.push_back(field);
        }

        // Create a new table
        userTable = new Table(tableName, fields);
        db.addTable(userTable);
    }

    // Main loop: Allow user to add records repeatedly
    char choice;
    do {
        // Collect a new record from the user
        vector<string> recordFields;
        for (const string& field : userTable->getFields()) {
            string value;
            cout << "Enter " << field << ": ";
            getline(cin, value);
            recordFields.push_back(value);
        }

        // Add the new record to the table
        userTable->addRecord(Record(recordFields));

        // Ask if the user wants to add another record
        cout << "Do you want to add another record? (y/n): ";
        cin >> choice;
        cin.ignore();  // Ignore the newline after the choice input
    } while (choice == 'y' || choice == 'Y');

    // Save the table back to the file (appending new records)
    userTable->saveToFile(filename);

    return 0;
}
