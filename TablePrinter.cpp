#include "TablePrinter.hpp"

using namespace std;
void TablePrinter::printTable(CSVTable& table)
{
	fillMaxLength(table);
	for (int rowIndex = 0; rowIndex < table.getRowsCount(); ++rowIndex) {
		for (int colIndex = 0; colIndex < table.getColumnCount(); ++colIndex) {
			cout << left << setw(m_maxLength.at(colIndex)) << table.getCellValue(rowIndex, colIndex)<<"|";
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
			if (table.getCellValue(rowIndex, colIndex).length() > m_maxLength[colIndex]) {
				m_maxLength[colIndex] = table.getCellValue(rowIndex, colIndex).length();
			}
		}
	}
}
