#include "TablePrinter.hpp"
#include <algorithm>

using namespace std;
void TablePrinter::printTable(CSVTable& table)
{
	fillMaxLength(table);

	printRow(table.getRow(0));

	vector<string> separator;
	for (int colIndex = 0; colIndex < m_maxLength.size(); ++colIndex) {
		separator.push_back(string(m_maxLength.at(colIndex), '*'));
	}
	printRow(separator);

	for (int rowIndex = 1; rowIndex < table.getRowsCount(); ++rowIndex) {
		printRow(table.getRow(rowIndex));
	}
}

void TablePrinter::fillMaxLength(CSVTable& table)
{
	m_maxLength.resize(table.getColumnCount());
	fill(begin(m_maxLength), end(m_maxLength), 0);
	
	//stores the maximum length for every column in m_maxLength
	for (int rowIndex = 0; rowIndex < table.getRowsCount(); ++rowIndex) {
		for (int colIndex = 0; colIndex < table.getColumnCount(); ++colIndex) {
			if (realUTF8CharLength(table.getCellValue(rowIndex, colIndex)) > m_maxLength[colIndex]) {
				m_maxLength[colIndex] = realUTF8CharLength(table.getCellValue(rowIndex, colIndex));
			}
		}
	}

	int colLimit = 80 - table.getColumnCount();
	int lengthLimit = colLimit / table.getColumnCount();
	int underLimitAccum = 0;
	int overLimitAccum = 0;
	for (int i = 0; i < m_maxLength.size(); ++i) {
		if (m_maxLength.at(i) <= lengthLimit) {
			underLimitAccum += m_maxLength.at(i);
		}
		else {
			overLimitAccum += m_maxLength.at(i);
		}
	}

	int sublimit = (colLimit - underLimitAccum);
	for (int i = 0; i < m_maxLength.size(); ++i) {
		if (m_maxLength.at(i) > lengthLimit) {
			
			m_maxLength[i] = sublimit*m_maxLength.at(i)/overLimitAccum;
		}
	
	}
	
}

unsigned int TablePrinter::realUTF8CharLength(std::string& str)
{
	unsigned int strLen = str.length();
	setlocale(LC_ALL, "en_US.utf8");
	unsigned int index = 0;
	const char* c_str = str.c_str();
	unsigned int charCount = 0;
	while (index < strLen)
	{
		index += mblen(&c_str[index], strLen - index);
		charCount += 1;
	}
	return charCount;
}

void TablePrinter::printRow(vector<string>& row)
{
	vector<vector<string>> textColumns(row.size());//vector of columns x lines
	int maxLines = 0;
	//assemble text lines for each row
	for (int colIndex = 0; colIndex < row.size(); ++colIndex) {
		string value = row.at(colIndex);
		int nLines = 1;
		do {
			//int substringSize = min(temp.length(), m_maxLength.at(colIndex));
			textColumns[colIndex].push_back(value.substr(0, m_maxLength.at(colIndex)));
			if (value.length() > textColumns[colIndex].back().length()) {
				string temp = value.substr(textColumns[colIndex].back().length(), 999);
				value = temp;
				++nLines;
			}
			else {
				value = "";
				maxLines = nLines > maxLines ? nLines : maxLines;
			}
		} while (value.length() > 0);
	}


	//prints the row
	for (int lineIndex = 0; lineIndex < maxLines; ++lineIndex) {
		for (int colIndex = 0; colIndex < row.size(); ++colIndex) {
			
			if (lineIndex < textColumns[colIndex].size()) {
				//difference in lengths due to UTF8 double byte chars
				unsigned int difference = textColumns[colIndex][lineIndex].length() - realUTF8CharLength(textColumns[colIndex][lineIndex]);
				cout << left << setw(m_maxLength.at(colIndex) + difference) << textColumns[colIndex][lineIndex] << "|";
			}
			else {
				string spacesString(m_maxLength.at(colIndex), ' ');
				cout << spacesString << "|";
			}
		}

		cout << endl;
	}
}
