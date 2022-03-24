#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <locale>


using namespace std;

void printTable(vector<vector<string>>& table) {

	for (vector<string> line : table) {
		for (string& field : line) {
			cout << field << "|";
		}
		cout << endl;
	}
}



int main(int argc, char* argv[]) {

	setlocale(LC_ALL, "en_US.UTF-8");

	ifstream inputFile("data.csv");
	if (!inputFile.good()) {
		cout << "Error opening file" << endl;
		return -1;
	}

	string line = "";
	vector<vector<string>> csvTable;
	while (!inputFile.eof()) {
		getline(inputFile, line);
		cout << line << endl;

		istringstream strStream(line);
		vector<string> csvColumns;
		while (!strStream.eof()) {
			string field = "";
			getline(strStream, field, ';');
			cout << "Field: " << field << endl;
			csvColumns.push_back(field);
		}
		csvTable.push_back(csvColumns);
	}
	

	inputFile.close();

	printTable(csvTable);
	
	return 0;
}
