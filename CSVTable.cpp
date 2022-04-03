#include "CSVTable.hpp"
#include <unistd.h>


using namespace std;


void CSVTable::parseFile(std::string fileName)
{
	

	ifstream inputFile(fileName);
	if (!inputFile.good()) {
		
		throw invalid_argument ("Error opening the file. Wrong address or the file does not exist");
		
	}

	if(inputFile.peek() == EOF){
		throw invalid_argument("File is empty");
	}

	string line = "";
	while (!inputFile.eof()) {
		getline(inputFile, line);

		istringstream strStream(line);
		vector<string> rowValues;
		while (!strStream.eof()) {
			string value = "";
			getline(strStream, value, ';');
			rowValues.push_back(value);
		}
		m_table.push_back(rowValues);
	}


	inputFile.close();
}


std::string CSVTable::getCellValue(int row, int column)
{
	return m_table[row][column];
}

std::vector<std::string>& CSVTable::getRow(int row)
{
	return m_table[row];
}

int CSVTable::getRowsCount()
{
	return m_table.size();
}

int CSVTable::getColumnCount()
{
	return m_table[0].size();
}


