// LZW.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include<functional>
#include <fstream>
#include <streambuf>
#include "HashTable.hpp"

using namespace std;

int main()
{

	int tableSize = 4096;
	HashTable<string, int> myTable(tableSize);
	ifstream input("compin");

	ofstream dout("compout");
	
	string str((istreambuf_iterator<char>(input)),istreambuf_iterator<char>());
	
	input.close();
	
	string sortedSTr = string(str);
	
	std::sort(sortedSTr.begin(), sortedSTr.end());
	sortedSTr.erase(std::unique(sortedSTr.begin(), sortedSTr.end()), sortedSTr.end());

	for (auto const & elem : sortedSTr) {
		
		int ch = (int)elem;
		if (ch < 0) {
			ch += 256;
		}

		 myTable.insert(string(1, elem), ch);
	}

		
	int beginIndex = 0;
	int endIndex = 1;
	int elemIndex = 256;
	string prefix = string(1, str[beginIndex]);

	int value = 0;
	int insertCount = 0;
	while (1) {
		while (myTable.keyExists(str.substr(beginIndex, endIndex)) && beginIndex+endIndex<=str.size()) {
			endIndex++;
		}
		if (beginIndex + endIndex > str.size()) {
			value = myTable.getValueForKey(str.substr(beginIndex, endIndex ));
			dout <<  value << " ";
			break;
		}

		if (insertCount>(tableSize-256-1)) {
			value = myTable.getValueForKey(str.substr(beginIndex, endIndex - 1));
			dout << value << " ";
			beginIndex += endIndex - 1;
			endIndex = 1;
			continue;
		}

		myTable.insert(str.substr(beginIndex, endIndex), elemIndex);
		insertCount++;
		value = myTable.getValueForKey(str.substr(beginIndex, endIndex - 1));

		dout << value << " ";

		beginIndex += endIndex-1;
		endIndex = 1;
		elemIndex++;

	}

	cout <<endl<< "compression is finished. press any key ..." << endl;
	dout.close();
	getchar();
    return 0;
}

