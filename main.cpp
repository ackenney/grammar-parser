// This program is an implementation of a top down parser

// Include Statements
#include <iostream>
#include <stack>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

// Using statements
using std::stack;
using std::string;
using std::cout;
using std::ofstream;
using std::vector;
using std::setw;

int main()
{
	// Declaring variables
	stack<char> myStack;
	stack<char> tempStack;
	ofstream outFile;
	string printString = "";
	bool flag1 = true;
	bool flag2 = false;
	string stackTop = " ";
	string input = "(i+i)*i$";
	string tempString = " ";
	vector<char> matched;
	string replace = " ";
	int row = 0;
	int col = 0;
	int index = 0; // For formatting
	string parseTable[6][7] =
	{

	{ " ","i","+","*","(",")","$"},

	{ "E","TE'", "?", "?", "TE'", "?", "?"},	// E [0][]

	{ "E'","?", "+TE'", "?", "?", "e", "e" },	// E'[1][]	

	{ "T", "FT'", "?", "?", "FT'", "?", "?" },	// T [2][]

	{ "T'","?", "e", "*FT'", "?", "e", "e" },	// T'[3][]

	{ "F", "i", "?", "?", "(E)", "?", "?" }		// F [4][]

	};

	// Pushing $ and start symbol 
	myStack.push('$');
	myStack.push('E');
	stackTop = " ";

	// Opening output file
	outFile.open("Output.txt");


	//Printing Header for console
	cout << "================================================================================\n"
		<< "Matched\t\t Stack\t\t Input\t\t Action\n"
		<< "--------------------------------------------------------------------------------\n";

	//Printing Header for console
	outFile
		<< "================================================================================\n"
		<< "Matched\t\t Stack\t\t Input\t\t Action\n"
		<< "--------------------------------------------------------------------------------\n";


	// Parse loop
	while (myStack.top() != '$') {


		// Printing matched characters
		for (unsigned int k = 0; k < matched.size(); k++)
		{
			// Output to console
			cout << matched.at(k);

			// Output to file
			outFile << matched.at(k);
		}
		// Formatting for console and file output
		cout << "\t" << setw(10);
		outFile << "\t" << setw(10);

		// Printing stack
		while (!myStack.empty())
		{

			tempStack.push(myStack.top()); // Keeping values in temp stack
			cout << myStack.top(); // Output to console
			outFile << myStack.top(); // Output to file
			myStack.pop(); // Removing top value
			index = index + 1; // Index for formatting
		}

		// While loop reorders the stack
		while (!tempStack.empty())
		{

			myStack.push(tempStack.top());
			printString.push_back(tempStack.top());
			tempStack.pop();
		}

		for (int i = 0; i < 11 - index; i++)
		{
			cout << " "; // Output to console
			outFile << " "; // Ouput to file
		}
		index = 0; // reset formatting index

		// Printing input to console and file
		cout << setw(13) << input;
		outFile << setw(13) << input;


	return 0;

}// End of main