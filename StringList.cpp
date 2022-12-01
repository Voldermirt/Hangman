#include "StringList.h"
#include "Word.h"

StringList::StringList(string _fileName) {
	fileName = _fileName;
}

void StringList::openMenu() {
	while (true) {
		system("cls");
		int choice;
		bool isValid = false;
		while (!isValid) {
			cout << "1. Delete line" << endl;
			cout << "2. Append line" << endl;
			cout << "3. Back" << endl;

			cout << "Choose one: ";
			cin >> choice;
			if (!cin || (choice != 1 && choice != 2 && choice != 3)) {
				cout << "Invalid. Try again." << endl;
			}
			else {
				isValid = true;
			}

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		if (choice == 1) {
			deleteLine();
		}
		else if (choice == 2) {
			appendLine();
		}
		else if (choice == 3) {
			return;
		}
	}

}

void StringList::deleteLine() {
	int numOfLines = displayLines();
	int choice;
	bool isValid = false;
	while (!isValid) {
		cout << "Choose a line to delete or type \"-1\" to go back: ";
		cin >> choice;
		if (choice == -1 && cin) {
			return;
		}
		if ((!cin || choice <= 0 || choice > numOfLines) && numOfLines > 0) {
			cout << "Invalid, ";
		}
		else {
			isValid = true;
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	std::ofstream fout("Temp.txt", std::ios_base::app);
	std::ifstream fin(fileName);

	int i = 0;
	string line;
	while (std::getline(fin, line)) {
		i++;
		cout << i << endl;
		if (i != choice) {
			fout << line;
			if (i != numOfLines) {
				fout << endl;
			}
		}
	}
	fout.close();
	fin.close();

	//Swap files
	rename(fileName.c_str(), "Temp2.txt");
	rename("Temp.txt", fileName.c_str());
	rename("Temp2.txt", "Temp.txt");
	remove("Temp.txt");

	displayLines();
	system("pause");
	displayLines();
}

void StringList::appendLine() {
	int numOfLines = displayLines();
	bool isValid = false;
	string line;
	while (!isValid) {
		cout << "What would you like to add? (type \"-1\" to go back): ";
		std::getline(cin, line);
		if (line == "-1") {
			return;
		}
		if (Word::isAlphabet(line) && !line.empty()) {
			isValid = true;
		}
		else {
			cout << "Invalid, may contain spaces but at least one letter." << endl;
		}
	}

	std::ofstream fout(fileName, std::ios_base::app);
	Word::toUpper(line);
	fout << line << endl;
	fout.close();

	displayLines();

	system("pause");
	system("cls");
}

int StringList::displayLines() {
	system("cls");
	std::ifstream fin(fileName);
	int numOfLines = 0;
	string line;
	while (std::getline(fin, line)) {
		numOfLines++;
		cout << numOfLines << ". " << line << endl;
	}
	fin.close();
	cout << endl;
	return numOfLines;
}

int StringList::numOfLines() {
	int num = 0;

	std::ifstream fin(fileName);
	string line;
	while (std::getline(fin, line)) {
		num++;
	}
	fin.close();
	return num;
}

string StringList::getLine(int ind) {
	int current = 0;
	std::ifstream fin(fileName);
	string line;
	while (std::getline(fin, line)) {
		if (current == ind) {
			return line;
		}
		current++;
	}
	return NULL;
}