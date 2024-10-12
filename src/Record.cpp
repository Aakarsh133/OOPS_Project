#include "../include/Record.h"
#include <iostream>
using namespace std;

Record::Record(const vector<string>& fields) : fields(fields) {}

string Record::getField(int index) const {
    if (index >= 0 && index < fields.size()) {
        return fields[index];
    }
    return "";
}

void Record::setField(int index, const string& value) {
    if (index >= 0 && index < fields.size()) {
        fields[index] = value;
    }
}

vector<string> Record::getFields() const {
    return fields;
}

void Record::display() const {
    for (const auto& field : fields) {
        cout << field << " ";
    }
    cout << endl;
}
