#ifndef TABLE_PRINTER_H
#define TABLE_PRINTER_H

#include <iostream>
#include <iomanip>
#include <vector>
#include "CSVTable.hpp"

class TablePrinter {
public:
	void printTable(CSVTable& table);

private:
	std::vector<int> m_maxLength;//stores the max length for each column

	void fillMaxLength(CSVTable& table);

};

#endif // !TABLE_PRINTER_H
