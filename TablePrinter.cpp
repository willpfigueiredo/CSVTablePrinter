#include "TablePrinter.hpp"
#include <algorithm>

using namespace std;
void TablePrinter::printTable(CSVTable& table)
{
	fillMaxLength(table);
	#ifdef _WIN32
	m_standardColorWin = 15;
	m_printColorWin = 15;
	#endif
	printRow(table.getRow(0));
	
	vector<string> separator;
	for (int colIndex = 0; colIndex < m_maxLength.size(); ++colIndex) {
		separator.push_back(string(m_maxLength.at(colIndex), '-'));
	}
	printRow(separator, '+');


	for (int rowIndex = 1; rowIndex < table.getRowsCount(); ++rowIndex) {
		#ifdef __linux__
		m_standardColor = "\033[0m";
		if(m_printColor == "\033[44m"){
			m_printColor = m_standardColor;
		}
		else{
			m_printColor = "\033[44m";
		}
		#endif

		#ifdef _WIN32
		
		if (m_printColorWin ==( 1 << 4 | 15)) {
			m_printColorWin = m_standardColorWin;
		}
		else {
			m_printColorWin = (1 << 4 | 15);
		}
		#endif


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
				m_maxLength[colIndex] = static_cast<unsigned int>(realUTF8CharLength(table.getCellValue(rowIndex, colIndex)));
			}
		}
	}

	int colLimit = 80 - table.getColumnCount();
	unsigned int lengthLimit = colLimit / table.getColumnCount();
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

size_t TablePrinter::realUTF8CharLength(const std::string& str)
{
	size_t strLen = str.length();
	setlocale(LC_ALL, "en_US.utf8");
	unsigned int index = 0;
	const char* c_str = str.c_str();
	size_t charCount = 0;
	while (index < strLen)
	{
		index += mblen(&c_str[index], strLen - index);
		charCount += 1;
	}
	return charCount;
}

void TablePrinter::printRow(vector<string>& row, char colSeparator )
{
	pair<vector<vector<string>>, int> rowInLines;
	rowInLines = splitRowInLines(row);
	vector<vector<string>> textColumns = rowInLines.first;
	int maxLines = rowInLines.second;

	//prints the row
	for (int lineIndex = 0; lineIndex < maxLines; ++lineIndex) {
#ifdef _WIN32
		HANDLE consoleHandle;
		consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(consoleHandle, m_printColorWin);
#endif
		cout << m_printColor;
		for (int colIndex = 0; colIndex < row.size(); ++colIndex) {
			
			if (lineIndex < textColumns[colIndex].size()) {
				//difference in lengths due to UTF8 double byte chars
				size_t difference = textColumns[colIndex][lineIndex].length() - realUTF8CharLength(textColumns[colIndex][lineIndex]);
				cout << left << setw(m_maxLength.at(colIndex) + difference) << textColumns[colIndex][lineIndex] << colSeparator ;
			}
			else {
				string spacesString(m_maxLength.at(colIndex), ' ');
				cout << spacesString << colSeparator;
			}
		}

		cout << m_standardColor << endl;
#ifdef _WIN32
		SetConsoleTextAttribute(consoleHandle, m_standardColorWin);
		
#endif
	}
}


pair<vector<vector<string>>, int> TablePrinter::splitRowInLines(vector<string> row)
{	
	vector<vector<string>> textColumns(row.size());//vector of columns x lines
	int maxLines = 0;
	for (int colIndex = 0; colIndex < row.size(); ++colIndex) {
		string value = row.at(colIndex);
		int nLines = 1;
		unsigned int index = 0;
		do {
			textColumns[colIndex].push_back(value.substr(0, m_maxLength.at(colIndex)));

			//better adjusts the length of the strings to the available cell length considering utf-8 characters
			size_t charToByteDifference = textColumns[colIndex].back().length() - realUTF8CharLength(textColumns[colIndex].back());
			if(charToByteDifference > 0 && value.length() > m_maxLength.at(colIndex)){
				index  = 0;
				const char* c_str = value.c_str();
				size_t strLen = value.length();
				for(int i = 0; i < charToByteDifference; ++i){
					index += mblen(&c_str[textColumns[colIndex].back().length()+index], strLen - index);
				}

				textColumns[colIndex].back() += value.substr(m_maxLength.at(colIndex), index);

			}
			
			
			if (realUTF8CharLength(value) > realUTF8CharLength(textColumns[colIndex].back())) {
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
	return pair<vector<vector<string>>, int>(textColumns, maxLines);
}