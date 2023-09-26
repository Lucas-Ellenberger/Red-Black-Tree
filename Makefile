#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 8
#  Lucas Ellenberger
#  lmellenb
#  pa8
#  
#  make                     makes WordFrequency and Order
#  make WordFrequency		makes WordFrequency
#  make Order				makes Order
#  make DictionaryTest      makes DictionaryTest
#  make clean               removes all binaries
#  make WordFrequencyCheck  runs WordFrequency under valgrind on Gutenberg.txt
#  make OrderCheck          runs Order under valgrind on in3 junk3
#  make DictionaryCheck     runs DictionaryTest under valgrind
#------------------------------------------------------------------------------

MAIN           = WordFrequency
MAIN2				   = Order
ADT            = Dictionary
SOURCE         = $(MAIN).cpp
OBJECT         = $(MAIN).o
ADT_TEST       = $(ADT)Test
ADT_SOURCE     = $(ADT).cpp
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
COMPILE        = g++ -std=c++17 -Wall -Ofast -c
LINK           = g++ -std=c++17 -Wall -Ofast -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full
.PHONY:all
all: $(MAIN) $(MAIN2)

$(MAIN): $(OBJECT) $(ADT_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT_OBJECT)

$(MAIN2): $(OBJECT) $(ADT_OBJECT)
	$(LINK) $(MAIN2) $(OBJECT) $(ADT_OBJECT)

$(ADT_TEST): $(ADT_TEST).o $(ADT_OBJECT)
	$(LINK) $(ADT_TEST) $(ADT_TEST).o $(ADT_OBJECT)

$(OBJECT): $(SOURCE) $(ADT_HEADER)
	$(COMPILE) $(SOURCE)

$(ADT_TEST).o: $(ADT_TEST).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_TEST).cpp

$(ADT_OBJECT): $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

clean:
	$(REMOVE) $(MAIN) $(MAIN2) $(ADT_TEST) $(OBJECT) $(ADT_TEST).o $(ADT_OBJECT)

$(MAIN)Check: $(MAIN)
	$(MEMCHECK) $(MAIN) Gutenberg.txt WF-Gutenberg-out.txt

$(MAIN2)Check: $(MAIN2)
	$(MEMCHECK) $(MAIN2) in3 junk3

$(ADT)Check: $(ADT_TEST)
	$(MEMCHECK) $(ADT_TEST)

