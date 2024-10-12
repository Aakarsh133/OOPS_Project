#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <vector>

class Record {
private:
    std::vector<std::string> fields;  // Data fields for each record

public:
    Record() = default;
    Record(const std::vector<std::string>& fields);

    std::string getField(int index) const;
    void setField(int index, const std::string& value);

    std::vector<std::string> getFields() const;

    void display() const;
};

#endif
