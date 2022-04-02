#ifndef TABLE_PRINTER_H
#define TABLE_PRINTER_H

#include <iostream>
#include <iomanip>
#include <vector>
#include "CSVTable.hpp"
#include <numeric>

class TablePrinter {
public:
/**
 * @brief prints the data of a CSVTable as a fomatted table
 * 
 * @param table 
 */
	void printTable(CSVTable& table);

protected:
	std::vector<unsigned int> m_maxLength;//stores the max length for each column

	void fillMaxLength(CSVTable& table);

	
	/**
	 * @brief gets the real length of a screen with special utf-8 characters
	 * 
	 * @param str 
	 * @return unsigned int 
	 */
	unsigned int realUTF8CharLength(const std::string& str);

	
	/**
	 * @brief prints a row of the table
	 * 
	 * @param row 
	 */
	void printRow(std::vector<std::string>& row);
	
	/**
	 * @brief split the row content in lines for printing
	 * 
	 * @param row 
	 * @return std::pair<std::vector<std::vector<std::string>>, int> 
	 */
	std::pair<std::vector<std::vector<std::string>>, int> splitRowInLines(std::vector<std::string> row);

};

#endif // !TABLE_PRINTER_H
