#ifndef STRING_LIST_H
#define STRING_LIST_H

#include <string>
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::cin;
using std::string;

class StringList
{
public:
	StringList(string _fileName);
	void openMenu();
	int numOfLines();
	string getLine(int ind);

private:
	string fileName;
	void deleteLine();
	void appendLine();
	int displayLines();
};

#endif