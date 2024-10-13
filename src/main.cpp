#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Record {
    std::vector<std::string> fields;

public:
    Record(const vector<string>& fields) : fields(fields) {}

    const vector<string>& getFields() const {
        return fields;
    }

    void displayRecord() const {
        for (const auto& field : fields) {
            cout << field << " ";
        }
        cout << endl;
    }
};

class Table {
    string name;
    vector<string> fields;
    vector<Record> records;

public:
    Table(const string& name, const vector<string>& fields) : name(name), fields(fields) {}

    const string& getName() const {
        return name;
    }

    const vector<string>& getFields() const {
        return fields;
    }

    void addRecord(const Record& record) {
        records.push_back(record);
    }

    void saveToFile(const string& filename) const {
        ofstream outFile(filename, ios::trunc);  // Truncate the file before writing new data
        if (!outFile) {
            cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        // Write field names
        for (const auto& field : fields) {
            outFile << field << ",";
        }
        outFile << std::endl;

        // Write each record
        for (const auto& record : records) {
            for (const auto& field : record.getFields()) {
                outFile << field << ",";
            }
            outFile << std::endl;
        }

        outFile.close();
    }

    void loadFromFile(const std::string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    records.clear();  // Clear the existing records before loading

    // Load field names (first line of the file)
    string line;
    if (getline(inFile, line)) {
        fields.clear();
        string field;
        istringstream ss(line);
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
    }

    // Read each record from the file
    while (getline(inFile, line)) {
        vector<std::string> recordFields;
        string field;
        istringstream ss(line);

        while (getline(ss, field, ',')) {
            recordFields.push_back(field);
        }

        // Add the record to the table
        if (!recordFields.empty()) {
            records.emplace_back(recordFields);
        }
    }

    inFile.close();
}


    void displayTable() const {
        cout << "Table: " << name << endl;

        // Display field names
        for (const auto& field : fields) {
            cout << field << " ";
        }
        cout << endl;

        // Display each record
        for (const auto& record : records) {
            record.displayRecord();
        }
    }
};

class Database {
private:
    vector<Table*> tables;

public:
    void addTable(Table* table) {
        tables.push_back(table);
    }

    void loadAllTablesFromFile() {
        for (auto& table : tables) {
            string filename = "../data/" + table->getName() + ".txt";
            table->loadFromFile(filename);
        }
    }

    void saveAllTablesToFile() const {
        for (const auto& table : tables) {
            string filename = "../data/" + table->getName() + ".txt";
            table->saveToFile(filename);
        }
    }

    void displayTables() const {
        for (const auto& table : tables) {
            table->displayTable();
        }
    }
};

void manageTable(Database& db) {
    Table* userTable = nullptr;
    string tableName;
    
    // Get table name from the user
    cout << "Enter the name of the table: ";
    getline(cin, tableName);

    // Check if the table already exists (by trying to load it from a file)
    string filename = "../data/" + tableName + ".txt";
    ifstream infile(filename);
    
    if (infile.good()) {
        // If the file exists, load the table
        userTable = new Table(tableName, {});  // Fields will be populated by loadFromFile
        userTable->loadFromFile(filename);
        cout << "Table " << tableName << " loaded from file." << endl;
    } else {
        // If the file doesn't exist, create a new table with user-defined fields
        vector<string> fields;
        int numFields;
        cout << "Enter the number of fields: ";
        cin >> numFields;
        cin.ignore();  // Ignore the newline after the number input

        // Collect the field names
        for (int i = 0; i < numFields; ++i) {
            string field;
            cout << "Enter field " << (i + 1) << ": ";
            getline(cin, field);
            fields.push_back(field);
        }

        // Create a new table with the given fields
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
}




int main() {
    Database db;
    manageTable(db);

    return 0;
}
