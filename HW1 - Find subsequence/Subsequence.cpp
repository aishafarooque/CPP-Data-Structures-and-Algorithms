//============================================================================
// Name        : main.cpp
// Author      : Aisha Farooque
// Class       : COSC2430: Data Structures
// Instructor  : Dr. Nouhad Rizk
// Description : The purpose of this program is to can find 
// 				 out a subsequence of common characters from a list of strings.

#include <iostream>
#include <fstream>
#include <string>
#include "ArgumentManager.h"

int knapsack2(string x, string y);
int min(int a, int b);
int max(int a, int b);

int main(int argc, char *argv[]) {
	if (argc != 3 && argc != 2) {
		cout << "Insufficient Arguments" << endl;
		return 1;
	} //end if-else

	ArgumentManager am(argc, argv);
	string input = am.get("input"), output = am.get("output"), line, lines[4] = {"","","",""};
	int number_of_lines = 0;
	ifstream inFS(input);
	ofstream outFS(output);

	while (getline(inFS, line)) {
		if (line == "") continue;
		lines[number_of_lines++] = line;
	} //end while


	if (number_of_lines <= 1) {
		cout << "Please enter 2 or more strings" << endl;
		// return 1;
	}

	if (number_of_lines == 2) {
		outFS << "Len: " << knapsack2(lines[0], lines[1]);
	} else if (number_of_lines == 3) {
		outFS << "Len: " << min(min(knapsack2(lines[0], lines[1]), knapsack2(lines[0], lines[2])),
								   knapsack2(lines[1], lines[2]));
	} else if (number_of_lines == 4) {
		string x = lines[0], y = lines[1], z = lines[2], a = lines[3];
		outFS << "Len: " << min(min(knapsack2(x,y), knapsack2(x, z)), min(min(knapsack2(x, a), 
			knapsack2(y, z)), min(knapsack2(y,a), knapsack2(z, a))));
	} //end if-else 

	
	/*Debugging*/
	cout << lines[0] << endl << lines[1] << endl << lines[2] << endl << lines[3] << endl;
	cout << "number_of_lines: " << number_of_lines << endl;

	inFS.close();
	outFS.close();
	return 0;
} //end main

int knapsack2(string x, string y) {
	/*Calculated the subsequence for two strings*/
	/*I wrote this with the help of Sunny Trang and GeeksforGeeks.com*/
	int row = x.length(), column = y.length();
	int table[row+1][column+1];
	for (int i = 0; i <= row; i++) {
		for (int j = 0; j <= column; j++) {
			if (i == 0 || j == 0) table[i][j] = 0;								
			else if (x[i-1] == y[j-1]) table[i][j] = 1 + table[i-1][j-1];		
			else table[i][j] = max(table[i-1][j], table[i][j-1]);
		}
	} //end for loop
	return table[row][column];
} //end knapsack2

int min(int a, int b) {
	return (a < b) ? a : b;
} //end min

int max(int a, int b) {
	return (a > b) ? a : b;
} //end max

/*	Pseudocode:
	//make tableof row size xLen and yLen, +1 to count '\0'
	//for loop through x length
		//for loop through y length
			//if it is edge row=0 column=0, you can't look up or else 
				//then you set to 0
			//else if they match (left and top)
				//get the top value increase by 1
			//otherwise get the max from top and left value and return
	*edge means the top row and the left most column, don't mark the right and bottom lines
*/
