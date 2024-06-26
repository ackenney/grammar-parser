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
using std::endl;

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

		// Printing action
		// if flag2 is false its an output action if its true then its a matched action
		if (flag2 == false)
		{
			if (parseTable[row][col] == " ")
			{
				cout << "\t\n";
				outFile << "\t\n";
			}
			else
			{
				cout << "\t";
				// print action to console
				cout << " Output" << stackTop << "->" << parseTable[row][col] << endl;

				outFile << "\t";
				// print action to file
				outFile << " Output" << stackTop << "->" << parseTable[row][col] << endl;

			}


		}
		if (flag2 == true)
		{
			// Printing matched action to file and console
			cout << "\t";
			cout << " Match " << stackTop << endl;
			outFile << "\t";
			outFile << " Match " << stackTop << endl;
			flag2 = false;
		}

		tempString = input[0]; // Setting tempChar to the first
		stackTop = myStack.top(); // setting stackTop();

		// Handling ' stack values
		tempStack.push(myStack.top());
		myStack.pop();
		if (myStack.top() == '\'')
		{
			stackTop.push_back(myStack.top());
			myStack.push(tempStack.top());
		}
		else if (myStack.top() != '\'')
		{
			myStack.push(tempStack.top());
		}
		tempStack.pop();

		// Checking if its non teminal and getting the row and column index
		for (int i = 0; i < 6; i++)
		{
			if (stackTop == parseTable[i][0]) // Then it is a non terminal
			{
				row = i;
				flag1 = true;
				break;
			}

		}
		for (int i = 0; i < 7; i++)
		{
			if (tempString == parseTable[0][i])
			{
				col = i;
				break;
			}
		}
		// setting replace to parse table value
		replace = parseTable[row][col];

		// Checking if the top value is a match
		if (myStack.top() == input[0])
		{
			matched.push_back(input[0]);
			input.erase(0, 1);
			tempString = input[0];
			myStack.pop();
			flag2 = true;
		}

		// Replacing non terminal value
		else if (flag1 == true)
		{

			myStack.pop();
			while (myStack.top() == '\'')
			{
				myStack.pop();
			}
			while (!replace.empty())
			{
				myStack.push(replace.back());
				replace.pop_back();
			}

		}
		// Removing top value and adding value from the table in the correct order
		if (myStack.top() == 'e')
		{
			myStack.pop();
		}

	}


	return 0;

}// End of main