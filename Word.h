#ifndef WORD_H
#define WORD_H

#include <string>
#include <vector>
#include <array>
#include <stdlib.h>
#include <ctime>

class Word
{
public:
	Word(std::string);
	Word();
	bool alreadyGuessed(char c);
	bool guess(char guess);
	int size();
	std::string getModifiedWord(bool includeSpaces);
	std::string getAlphabet();
	int getIncorrectGuesses();
	std::string getWord();
	static const std::string alphabet;
	static void toUpper(std::string& s);
	static bool isAlphabet(std::string s);
private:
	int incorrectGuesses = 0;
	std::string word;
	std::vector<char> guessed;
	static const std::vector<std::string> randomWords;
};

#endif