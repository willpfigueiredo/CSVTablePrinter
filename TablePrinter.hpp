#ifndef TABLE_PRINTER_H
#define TABLE_PRINTER_H

#include <iostream>
#include <iomanip>
#include <vector>
#include "CSVTable.hpp"
#include <numeric>

class TablePrinter {
public:
	void printTable(CSVTable& table);

private:
	std::vector<unsigned int> m_maxLength;//stores the max length for each column

	void fillMaxLength(CSVTable& table);

	unsigned int realUTF8CharLength(std::string& str);

	void printRow(std::vector<std::string>& row);

};

#endif // !TABLE_PRINTER_H
