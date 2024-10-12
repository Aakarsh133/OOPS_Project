#ifndef TABLE_H
#define TABLE_H

#include "../include/Record.h"
#include <vector>
#include <string>

class Table {
private:
    std::string tableName;
    std::vector<std::string> columns;
    std::vector<Record> records;

public:
    Table(const std::string& name, const std::vector<std::string>& columns);

    void addRecord(const Record& record);
    void display() const;

    // File handling methods
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    std::string getTableName() const { return tableName; }
};

#endif
