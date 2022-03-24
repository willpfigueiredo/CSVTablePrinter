#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <locale>
#include "CSVTable.hpp"


using namespace std;

void printTable(CSVTable& table) {

	for (int i = 0; i < table.getNRows(); ++i) {
		for (int j = 0; j < table.getNColumns(); ++j) {
			cout << table.getCellValue(i, j) << "|";
		}
		cout << endl;
	}
}



int main(int argc, char* argv[]) {

	setlocale(LC_ALL, "en_US.UTF-8");
	CSVTable csvTable;
	csvTable.parseFile("data.csv");
	

	printTable(csvTable);
	
	return 0;
}
