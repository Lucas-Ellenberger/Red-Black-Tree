# Lucas Ellenberger pa8 README

## Note to the grader

Nothing to note as of now.

## Dictionary.h

This file contains the header for Dictionary.cpp and is required for the compilation of the code, as it has important include statements and function declarations.

## Dictionary.cpp

This file contains the implementation (function definitions) of the Dictionary ADT. It will construct, destruct, access, and manipulate the Dictionary ADT through the various fuinctions declared in Dictionary.h

## DictionaryTest.cpp

This file is a simple test for our Dictionary ADT. It outputs the actual values from all functions to the command line which can be compared to the expected output. Although the tests are simple, it is a quick and easy way to make sure all the Dictionary ADT functions work for some cases. Helpful for early developement of the Dictionary ADT.

## Order.cpp

This is one of the files containing the main function and is one of the file to be compiled into an executable binary. This program takes two command line arguments, an infile and an outfile. First, the program continually reads from the infile. Each infile line is the key to the dictionary and the line number is the value. Then, the program prints the following string represenation to the outfile: The key : value pairs printed in alpahbetical key order, one per line. Then, all the keys, one per line, in alphabetical order. Finally, the program will free all associated memory and close the infile and outfile before terminating.

## WordFrequency.cpp

This is one of the files containing the main function and is one of the file to be compiled into an executable binary. This program takes two command line arguments, an infile and an outfile. The program parses words from the infile based on the delimiting string. All words are put to lower case and added to a dictionary. The value associated with each key is the frequency of the word. After reading in every word and storing the associated frequency in the dictionary, the in order representation of the dictionary is printed to the outfile. Finally, the program will free all associated memory and close the infile and outfile before terminating.

## Makefile

This file takes the .cpp files and .h file and creates the Order and testing executables.
Standard Makefile as provided on the website.

### make

makes WordFrequency and Order

### make WordFrequency

makes WordFrequency

### make Order

makes Order

### make DictionaryTest

makes DictionaryTest

### make clean

removes all binaries and .o files

### make WordFrequencyCheck

runs WordFrequency under valgrind on Gutenberg.txt

### make OrderCheck

runs Order under valgrind on in3 junk3

### make DictionaryCheck

runs DictionaryTest under valgrind

