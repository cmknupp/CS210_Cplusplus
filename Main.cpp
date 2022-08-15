/*Updated by Connie Knupp
 * on 8/15/22
 * CS-210
 */

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>
#include "Main.h"

using namespace std;

int toContinue = 0; // variable for the to continue loop

// array with menu selections
const char* menuChoices[4] = { "View List of All Items Sold", "Query Quantity Sold of Specific Item ",
							   "Graph of Items/Quantities Sold","Exit Program" };
/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


/**
 * Returns a string of length n, each character a c.
 * @param n string length, >=0
 */
string nCharString (size_t n, char c) {
	string charString = ""; // empty string for loop
	int i; // variable for loop iterations
	for (i = 0; i < n; ++i) { //loops through n times
		charString = charString + c; // adds character to string
	}
	return charString; 
}


//Prints Menu Choices
void printMenu(const char* strings[], unsigned int numStrings, unsigned char width) {
	int i; //variable for loop iterations
	string currentLine = ""; //empty string for line
	int spacesNeeded; // variable for number of spacses needed to fill line
	
	cout << endl; // whitespace for aesthetics
	cout << nCharString(width, '*') << endl; // border for menu
	for (i = 0; i < numStrings; i++) { //loops through menu choices
		currentLine = "* " + to_string(i + 1) + " - " + strings[i]; // prints menu choice
		spacesNeeded = (width - currentLine.length()) - 1; // calculates spaces needed
		currentLine = currentLine + nCharString(spacesNeeded, ' ') + "*"; // formats border
		cout << currentLine << endl; // prints currentl line
		if (i < (numStrings - 1)) { // if not last choice
			cout << endl; // adds line between items
		}
	}
	cout << nCharString(width, '*') << endl; // border for menu
}

/*Gets user input for menu selection
* Accepts max choice of menu as a positive number
* Returns user choice when valid
*/
unsigned int getMenuChoice(unsigned int maxChoice) {
	int userChoice = 0; //create variable
	cin >> userChoice; // get inputs
	while ((cin.fail()) || (userChoice < 1) || (userChoice > maxChoice)) { //checks for error or number out of range
		//clear input stream
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Invalid Entry" << endl; //report error to user
		cout << "Select Option 1-" << maxChoice << endl; //prompt new input
		cin >> userChoice; //get new choice
	}
	return userChoice;
}
/*
*Prompts for item to query and returns string input
* no input accepted
*/
string getItemToQuery() {
	string userInput = ""; //create variable
	cout << "What item would you like to query?" << endl; //prompt input
	cin >> userInput; // get input
	if (cin.fail()) { //checks for input error
		while (cin.fail()) { // if failed
			cout << "Invalid Entry" << endl; // report error
			cin.clear(); //clear input stream
			cin.ignore(INT_MAX, '\n');
			cin >> userInput; //gets new input
		}
	}
	return userInput;
}
/*
*Function to get and print to screen the frequency of item sold
* no input accepted
* no return
*/
void queryOneItem() {
	int itemFrequency = 0; // create variable for frequency
	string itemLookup = ""; //create variable for item to be queried
	itemLookup = getItemToQuery(); // calls function to get input string and assigns string to variable
	itemFrequency = callIntFunc("SpecificItemCounter", itemLookup); // calls python function to query frequency of item
	cout << "Item: " << itemLookup << " Quantity Sold: " << itemFrequency << endl; // outputs statement containing frequency
}

/*
* Outputs a text histogram of items and frequencies in file contents
* Accepts string of file name containing frequency data
* no return
*/
void outputHistogram(string frequencyFileName) {
	ifstream inputFile(frequencyFileName, ios::in);  // open file to read
	string itemName; // stores item from input file line
	int itemFrequency; //stores frequency from input file line
	
	//string outputContents = ""; //holds string of data to write to output file
	if (inputFile.is_open()) { // checks if open
		while (inputFile >> itemName >> itemFrequency) { //loop to read input from file
			//outputs each line as histogram
			cout << setw(13) << left << itemName << nCharString(itemFrequency, '*') << endl;
		}
		inputFile.close(); //closes input file
	}
	else {
		cout << "File failed to open input file."; // outputs statement if filed fails to open
	}
}


//takes action depending on menu selection
//no input or return
void mainMenu() {
	cout << "Select an Option" << endl; // prompt input
	int userPicked = getMenuChoice(4); // gets choice from user, checks if valid
	//clears input stream
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	switch (userPicked) { // branches for menu choices 
	case 1:  // option 1
		cout << endl;
		CallProcedure("ItemFrequencies"); //gets all items and frequencies
		break;
	case 2: // option two
		cout << endl;
		queryOneItem(); // queries one item - function calls python function then prints return
		break;
	case 3: // option 3
		cout << endl;
		cout << "Creating file: frequency.dat" << endl; //outputs statesment
		callIntFunc("OutputItemFrequencies", "frequency.dat"); //outputs items and frequencies to file
		outputHistogram("frequency.dat"); // reads frequency data and displays histogram
		cout << endl;
		break;
	case 4:
		cout << "Goodbye" << endl; // output statement
		toContinue = 1; //breaks loop to exit
		break;
	default: // prints statement if user's choice is not valid.
		//clear input stream
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Invalid Entry" << endl;
		break;
	}
}

//main function
int main()
{
	while (toContinue == 0) {
		printMenu(menuChoices, 4, 55); //prints menu
		mainMenu(); // gets input and does action selected
	}
	return 0;
}