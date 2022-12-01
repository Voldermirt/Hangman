#include "Word.h"
#include <iostream>

const std::vector<std::string> Word::randomWords { "DRAGONS", "UNICORN", "PHOENIX ARIZONA", "SAPPHIRA", "AMELIE", "BELLA", "ELLIOT" };
const std::string Word::alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

Word::Word(std::string _word) {
	word = _word;
}

Word::Word() {
	srand(time(0));
	int random = rand() % randomWords.size();
	word = randomWords[random];
}


bool Word::alreadyGuessed(char c) {
	return std::find(guessed.begin(), guessed.end(), std::toupper(c)) != guessed.end();
}

bool Word::guess(char guess) {
	if (alphabet.find(std::toupper(guess)) == std::string::npos)
		return false;
	if (!alreadyGuessed(guess)) {
		guessed.push_back(std::toupper(guess));
	}
	else {
		return false;
	}
	if (word.find(std::toupper(guess)) == std::string::npos) {
		std::cout << "Incorrect." << std::endl;
		incorrectGuesses++;
	}
	else {
		std::cout << "Correct!" << std::endl;
	}
	return true;
}

int Word::size() {
	return word.length();
}

std::string Word::getModifiedWord(bool includeSpaces) {
	std::string modified = "";
	for (unsigned int i = 0; i < word.size(); i++) {
		if (alreadyGuessed(word[i]) || word[i] == ' ') {
			modified += word[i];
		}
		else {
			modified += "_";
		}
		if (includeSpaces) {
			modified += " ";
		}
	}
	return modified;
}

std::string Word::getAlphabet() {
	std::string modifiedAlphabet = "";
	for (unsigned int i = 0; i < alphabet.size(); i++) {
		if (alreadyGuessed(alphabet[i])) {
			modifiedAlphabet += "_";
		}
		else {
			modifiedAlphabet += alphabet[i];
		} 
		modifiedAlphabet += " ";
	}
	return modifiedAlphabet;
}

int Word::getIncorrectGuesses() {
	return incorrectGuesses;
}

std::string Word::getWord() {
	return word;
}

void Word::toUpper(std::string& s) {
	for (unsigned int i = 0; i < s.size(); i++) {
		if (Word::alphabet.find(std::toupper(s[i])) != std::string::npos) {
			s[i] = std::toupper(s[i]);
		}
	}
}

bool Word::isAlphabet(std::string s) {
	for (char c : s) {
		if (alphabet.find(std::toupper(c)) == std::string::npos) {
			return false;
		}
	}
	return true;
}