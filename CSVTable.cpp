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
		cout << line << endl;

		istringstream strStream(line);
		vector<string> rowValues;
		while (!strStream.eof()) {
			string value = "";
			getline(strStream, value, ';');
			cout << "Field: " << value << endl;
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

int CSVTable::getNRows()
{
	return m_table.size();
}

int CSVTable::getNColumns()
{
	return m_table[0].size();
}


