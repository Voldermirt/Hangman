#include <iostream>
#include <array>
#include "Word.h"
#include <climits>
#include "StringList.h"
#include <ctime>
#include <stdlib.h>

using std::cout;
using std::endl;

void gameLoop(StringList& stringList);
void getInput(Word& word);
void drawBoard(Word& word);
bool checkForLose(Word& word);
bool checkForWin(Word& word);
bool checkLines(StringList& stringList);

int main() {
	while (true) {
		system("cls");
		int choice;
		bool isValid = false;
		StringList stringList("Lines.txt");
		while (!isValid) {
			cout << "1. Play" << endl;
			cout << "2. Lines" << endl;
			cout << "3. Quit" << endl;

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
			if (stringList.numOfLines() == 0) {
				cout << "There are no lines in 'Lines.txt'. Please add some." << endl;
				system("pause");
			}
			else if (!checkLines(stringList)) {
				system("pause");
			}
			else {
				gameLoop(stringList);
			}

		}
		else if (choice == 2) {
			stringList.openMenu();
		}
		else if (choice == 3) {
			return 0;
		}
	}
	return 0;
}

void gameLoop(StringList& stringList) {
	while (true) {
		srand(time(0));
		int randNum = rand() % stringList.numOfLines();
		std::string line = stringList.getLine(randNum);
		Word::toUpper(line);
		Word word(line);
		drawBoard(word);
		while (true) {
			getInput(word);
			drawBoard(word);
			if (checkForLose(word)) {
				cout << "You Lost." << endl;
				cout << "The word was: " << word.getWord() << endl;
				break;
			}
			if (checkForWin(word)) {
				cout << "You Won!" << endl;
				break;
			}
		}
		char input;
		bool isValid = false;
		while (!isValid) {
			cout << "Continue? y/n: ";
			std::cin >> input;
			if (!std::cin || (std::tolower(input) != 'y' && std::tolower(input) != 'n')) {
				cout << "Invalid, ";
			}
			else {
				isValid = true;
			}
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		if (std::tolower(input) == 'n') {
			break;
		}
	}
}

void getInput(Word& word) {
	bool isValid = false;
	char input;
	while (!isValid) {
		cout << "Enter a new guess: ";
		std::cin >> input;
		if (std::cin && word.guess(input)) {
			isValid = true;
		}
		else {
			cout << "Invalid, ";
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	cout << endl;
	
}

void drawBoard (Word& word) {
	system("cls");
	std::array<std::string, 11> hangman = {
		"   _______          ",
		"  | _______\\        ",
		"  | |      |        ",
		"  | |               ",
		"  | |               ",
		"  | |               ",
		"  | |               ",
		" _| |______________ ",
		"|__________________|"
	};
	int incorrectGuesses = word.getIncorrectGuesses();
	switch (incorrectGuesses) {
	case 6:
		hangman[5][12] = '\\';
	case 5:
		hangman[5][10] = '/';
	case 4:
		hangman[4][12] = '\\';
	case 3:
		hangman[4][10] = '/';
	case 2:
		hangman[4][11] = '|';
	case 1:
		hangman[3][11] = 'O';
		break;
	default:
		break;
	}
	for (std::string line : hangman) {
		cout << line << endl;
	}
	cout << endl << word.getModifiedWord(true) << endl;
	cout << "\n\nAvailable letters: " << endl;
	cout << word.getAlphabet() << endl;
	cout << endl;
}

bool checkForLose(Word& word) {
	return word.getIncorrectGuesses() >= 6;
}

bool checkForWin(Word& word) {
	return word.getModifiedWord(false) == word.getWord();
}

bool checkLines(StringList& stringList) {
	int numOfLines = stringList.numOfLines();
	for (int i = 0; i < numOfLines; i++) {
		string line = stringList.getLine(i);
		if (!Word::isAlphabet(line)) {
			cout << "Line \"" << line << "\" contains invalid characters. Please change it." << endl;
			return false;
		}
	}
	return true;
}