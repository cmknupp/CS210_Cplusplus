#pragma once


/* Project Three
 *
 * Date: 08/14/2022
 * Author: Connie Knupp
 * CS 210
 */

#include <iostream>
#include <string>

using namespace std;

//calls function in python with no parameters passed
void CallProcedure(string pName);


//calls Python function and passes string parameter
int callIntFunc(string proc, string param);

// calls function in python and passes integer as parameter
int callIntFunc(string proc, int param);


// Returns a string of length n, each character a c.
string nCharString(size_t n, char c);

// Prints Menu Choices
void printMenu(const char* strings[], unsigned int numStrings, unsigned char width);

// Gets user input for menu selection
unsigned int getMenuChoice(unsigned int maxChoice);


// Prompts for item to query and returns string input
string getItemToQuery();

//Function to get and print to screen the frequency of item sold
void queryOneItem();

// Outputs a text histogram of items and frequencies in file contents
void outputHistogram(string frequencyFileName);

//takes action depending on menu selection
void mainMenu();

//main function
int main();

