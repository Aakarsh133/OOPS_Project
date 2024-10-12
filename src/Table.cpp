#include "../include/Table.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

Table::Table(const string& name, const vector<string>& columns)
    : tableName(name), columns(columns) {}

void Table::addRecord(const Record& record) {
    records.push_back(record);
}

void Table::display() const {
    for (const auto& col : columns) {
        cout << col << " ";
    }
    cout << endl;

    for (const auto& record : records) {
        record.display();
    }
}

// Save table data to a file
void Table::saveToFile(const string& filename) const {
    ofstream outFile(filename);

    // Write column headers
    for (size_t i = 0; i < columns.size(); ++i) {
        outFile << columns[i];
        if (i < columns.size() - 1) outFile << ",";
    }
    outFile << endl;

    // Write each record as a CSV line
    for (const auto& record : records) {
        for (size_t i = 0; i < record.getFields().size(); ++i) {
            outFile << record.getField(i);
            if (i < record.getFields().size() - 1) outFile << ",";
        }
        outFile << endl;
    }

    outFile.close();
}

// Load table data from a file
void Table::loadFromFile(const string& filename) {
    ifstream inFile(filename);
    string line;

    // Read column headers (we assume the columns in the file match the table)
    getline(inFile, line);

    // Read each record line by line
    while (getline(inFile, line)) {
        istringstream recordStream(line);
        vector<string> fields;
        string field;

        // Parse each field separated by commas
        while (getline(recordStream, field, ',')) {
            fields.push_back(field);
        }

        // Add the record to the table
        addRecord(Record(fields));
    }

    inFile.close();
}
