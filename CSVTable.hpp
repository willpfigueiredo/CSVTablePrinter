#ifndef CSV_TABLE_H
#define CSV_TABLE_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>



class CSVTable {
public:
	/**
	 * @brief reades the csv file and stores its values in a table.
	 * 
	 * @param fileName name of the file to parse
	 */
	virtual void parseFile(std::string fileName);

	/**
	 * @brief returns the value of a cell of the table
	 * 
	 * @param row 
	 * @param column 
	 * @return std::string 
	 */
	virtual std::string getCellValue(int line, int row);

	/**
	 * @brief Get a row of the table as a vector of strings
	 * 
	 * @param row index of the row
	 * @return std::vector<std::string>& 
	 */
	virtual std::vector<std::string>& getRow(int row);

	/**
	 * @brief Get the number of rows
	 *  
	 * @return int 
	 */
	virtual int getRowsCount();

	/**
	 * @brief Get the number of columns
	 * 
	 * @return int 
	 */
	virtual int getColumnCount();

protected:
	std::vector<std::vector<std::string>> m_table;///table with data from the csv file
};

#endif // !CSV_TABLE_H
