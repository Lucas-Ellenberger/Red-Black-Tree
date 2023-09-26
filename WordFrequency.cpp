/*****************************************************
 * WordFrequency.cpp
 * Implementation file Client interface with Dictionary ADT
 * Lucas Ellenberger
 * lmellenb
 * pa8
 ****************************************************/
#include<iostream>
#include<fstream>
#include<string>
#include<locale>         // std::locale, std::tolower

#include "Dictionary.h"

using namespace std;

#define MAX_LEN 4096

int main(int argc, char * argv[]){
   size_t begin, end, len;
   ifstream in;
   ofstream out;
   string line;
   string token;
   string lower_token;
   std::locale loc;
   // string delim = " "; 
   string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

   // check command line for correct number of arguments
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }

   Dictionary * dict = new Dictionary();
   // read each line of input file, then count and print tokens 
   while( getline(in, line) )  {
      len = line.length();

      // get first token
      begin = min(line.find_first_not_of(delim, 0), len);
      end   = min(line.find_first_of(delim, begin), len);
      token = line.substr(begin, end-begin);
      lower_token = "";
      for (std::string::size_type i=0; i < token.length(); i++) {
         lower_token += std::tolower(token[i],loc);
      }
      
      while( lower_token!="" ){
         if (dict->contains(lower_token)) {
            (dict->getValue(lower_token))++;
         } else {
            dict->setValue(lower_token, 1);
         }
         // get next token
         begin = min(line.find_first_not_of(delim, end+1), len);
         end   = min(line.find_first_of(delim, begin), len);
         token = line.substr(begin, end-begin);
         lower_token = "";
         for (std::string::size_type i=0; i < token.length(); i++) {
            lower_token += std::tolower(token[i],loc);
         }
      }
   }

   out << (*dict) << endl;

   delete dict;

   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}

