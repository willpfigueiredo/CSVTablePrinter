#include "TablePrinter.hpp"

using namespace std;
void TablePrinter::printTable(CSVTable& table)
{
	fillMaxLength(table);
	for (int rowIndex = 0; rowIndex < table.getRowsCount(); ++rowIndex) {
		for (int colIndex = 0; colIndex < table.getColumnCount(); ++colIndex) {
			//difference in lengths due to UTF8 double byte chars
			unsigned int difference = table.getCellValue(rowIndex, colIndex).length() - realUTF8CharLength(table.getCellValue(rowIndex, colIndex));
			cout << left << setw(m_maxLength.at(colIndex)+difference) << table.getCellValue(rowIndex, colIndex)<<"|";
		}
		cout << endl;
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
