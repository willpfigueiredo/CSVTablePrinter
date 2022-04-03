#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <locale>
#include "CSVTable.hpp"
#include "TablePrinter.hpp"


using namespace std;

int main(int argc, char* argv[]) {

	setlocale(LC_ALL, "en_US.UTF-8");
	
	if (argc < 2){
		cout << "No file address found. Call CSVTablePrinter [name of the file with address]";
		return -1;
	}

	string fileName = argv[1];
	cout << "File: " << fileName << endl;
	
	CSVTable csvTable;
	TablePrinter printer;
	try{
		csvTable.parseFile(fileName);
	}
	catch(const exception& excp){
		cerr<< excp.what() << endl;
		return -1;
	}
	printer.printTable(csvTable);
	return 0;
}
