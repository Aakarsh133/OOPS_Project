#include "../include/EmployeeTable.h"
#include <vector>
#include <string>

EmployeeTable::EmployeeTable()
    : Table("Employee", {"ID", "Name", "Position", "Salary"}) {}
