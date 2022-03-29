#include "CSVTable.hpp"

using namespace std;

void CSVTable::parseFile(std::string fileName)
{
	ifstream inputFile(fileName);
	if (!inputFile.good()) {
		cout << "Error opening file" << endl;
		return;
		//handle this with exception
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

auto CSVTable::begin()
{
	return m_table.begin();
}

auto CSVTable::end()
{
	return m_table.end();
}


