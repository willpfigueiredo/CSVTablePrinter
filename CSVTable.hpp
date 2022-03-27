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

	std::vector<std::string>& getRow(int row);

	int getRowsCount();

	int getColumnCount();

	auto begin();
	
	auto end();

private:
	std::vector<std::vector<std::string>> m_table;
};

#endif // !CSV_TABLE_H
