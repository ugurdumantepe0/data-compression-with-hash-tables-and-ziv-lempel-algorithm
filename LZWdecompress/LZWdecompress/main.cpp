// LZWdecompress.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HashTable.hpp"
#include<string>
#include <sstream>
int main()
{

	HashTable<int,string> myTable(4096);

	string str;
	ifstream input("compout");
	ofstream dout("decompout");
	getline(input, str);
	input.close();
	vector<int> intVector;

	char ch;
	for (int i = 0; i < 256; ++i) {
		ch = i;
		myTable.insert(i, string(1, ch));
	}

	stringstream ss(str);
	string s;

	while (getline(ss, s, ' ')) {
		intVector.push_back(stoi(s));
	}

	
	int biggest = 255;
	for (int i = 0; i < intVector.size(); ++i) {
		if (i == 0) {
			dout << myTable.getValueForKey(intVector[i]);
			continue;
		}

		if (myTable.keyExists(intVector[i])) {
			string prev = myTable.getValueForKey(intVector[i - 1]);
			string prefix = myTable.getValueForKey(intVector[i]);
			dout << prefix;
			prefix = prefix.substr(0, 1);
			string newValue = prev + prefix;
			if (intVector[i] > biggest)
				biggest = intVector[i];
			biggest++;
			myTable.insert(biggest, newValue);

		}
		else {
			string prev = myTable.getValueForKey(intVector[i - 1]);
			string newValue = prev + prev.substr(0, 1);
			myTable.insert(intVector[i],newValue);
			if (intVector[i] > biggest)
				biggest = intVector[i];
			dout << newValue;

		}

	}


	cout << endl << "decompression is finished. press any key ..." << endl;
	dout.close();
	getchar();



    return 0;
}

