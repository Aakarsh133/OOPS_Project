#include "../include/Table.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

Table::Table(const std::string& name, const std::vector<std::string>& fields)
    : name(name), fields(fields) {}

void Table::addRecord(const Record& record) {
    records.push_back(record);
}

void Table::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename, std::ios::trunc);  // Use trunc to overwrite the old content with the new one
    if (!outFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Write the header (field names)
    for (const auto& field : fields) {
        outFile << field << ",";
    }
    outFile << std::endl;

    // Write each record to the file
    for (const auto& record : records) {
        for (const auto& field : record.getFields()) {
            outFile << field << ",";
        }
        outFile << std::endl;
    }

    outFile.close();
}


void Table::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Clear current records before loading new data
    records.clear();
    fields.clear();

    std::string line;

    // Read the header (field names)
    if (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string field;
        while (std::getline(ss, field, ',')) {
            fields.push_back(field);  // Load field names
        }
    }

    // Read each record
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::vector<std::string> recordFields;
        std::string field;

        // Read each field in the record
        while (std::getline(ss, field, ',')) {
            recordFields.push_back(field);
        }

        // Add the record to the table
        if (!recordFields.empty()) {
            records.push_back(Record(recordFields));
        }
    }

    inFile.close();
}

std::string Table::getTableName() const {
    return name;
}

// New method to return the fields
const std::vector<std::string>& Table::getFields() const {
    return fields;
}
