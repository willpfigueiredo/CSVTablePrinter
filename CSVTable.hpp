#ifndef CSV_TABLE_H
#define CSV_TABLE_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>



class CSVTable {
public:
	void parseFile(std::string fileName);

	std::string getCellValue(int line, int row);

	int getNRows();

	int getNColumns();

private:
	std::vector<std::vector<std::string>> m_table;
};

#endif // !CSV_TABLE_H
