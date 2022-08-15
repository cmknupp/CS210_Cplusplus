# Updated by Connie Knupp
# on 08/14/2022
# CS210

import re
import string
import os

fileName = "CS210_Project_Three_Input_File.txt"
 

# The following functions are commented out 
# as they are unused.  Consider removing.

# def printsomething():
#   print("Hello from python!")

# def PrintMe(v):
#   print("You sent me: " + v)
#   return 100;

# def SquareValue(v):
#   return v * v


# Function to change the input file name
# Not yet required but need for interpreting multiple 
# files anticipated. 
    # def SetInputFile (inputFileName): 
    #   fileName = inputFileName

# opens and copies contents of input file to list
# Accepts string of input file name
# Returns list of contents
def GetInputFileContents (inputFileName):
    inputFileContents = [] # creates list to add file contents too
    inputFile = open(inputFileName, "r") # opens input file
    inputFileContents = (inputFile.readlines()) # copies input file to list fileContents
    inputFile.close() # closes input file
    for i in range (0, len(inputFileContents) - 1): # loops through file contents
        inputFileContents[i] = inputFileContents[i].strip() # strips extra whitespace
    return inputFileContents # returns contents of file

# Lists items in file only once 
# Accepts list of file contents
# Returns list of items without repeats
def ListItemsOnce (listFileContents):
    items_listed = [] # creates empty list
    for element in listFileContents: # loops lines of content      
        if element not in items_listed: # checks if item is not in list
            items_listed.append(element) # appends items not found 
    return items_listed # returns new list
    

# Counts the number of occurences of a specific item
# in the input file. 
# Accepts string of item to query. 
# Returns frequency of item. 
def SpecificItemCounter(itemName): 
    # changes case to match input file formatting and strips whitespace
    itemToCount = itemName.lower().title().strip() 
    fileContents = GetInputFileContents(fileName) # gets copy of file contents
    freq = fileContents.count(itemToCount) # counts occurences 
    return freq # returns count

# Outputs a list of all items found in file with number of times sold
# No input needed.  No return value.
def ItemFrequencies():
    item_list = [] # creates empty list
    fileContents = GetInputFileContents(fileName) # gets file content
    item_list = ListItemsOnce(fileContents) # gets list of items without repeats
    for i in range (0, len(item_list) - 1): # loops list
        freq = fileContents.count(item_list[i]) # gets frequency of each item
        print('{:<15} {}'.format(item_list[i].strip(), freq)) # outputs item and frequency

# Outputs text histogram of items listed with frequency 
# Accepts string of output file name  
# Returns zero
def OutputItemFrequencies(outputFileName):
    item_list = [] # creates empty list
    fileContents = GetInputFileContents(fileName) # gets file content
    item_list = ListItemsOnce(fileContents) # gets list with repeats
    outputFile = open(outputFileName, "w") # opens output file
    for i in range (0, len(item_list) - 1): # loops items in list
        freq = fileContents.count(item_list[i]) # gets frequency
        outputFile.write("{} {}".format(item_list[i], freq)) # outputs items/frequency to file
    outputFile.close() #closes output file
    return 0
