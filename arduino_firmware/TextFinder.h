/*  
  TextFinder.h - a simple text parser for Arduino data streams
  Copyright (c) 2009 Michael Margolis.  All right reserved.
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
 
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
 
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/  

#ifndef TextFinder_h
#define TextFinder_h

#include <WProgram.h>
#include <Client.h>


class TextFinder {
private:
  Client *clientStream;
  HardwareSerial *serialStream;

  unsigned long timeout;    // number of seconds to wait for the next char before aborting read
  unsigned long startMillis; // used for timeout measurement

  char read();             // private function to read from the stream 

public:
  // constructor: 
  // default timeout is 5 seconds
  TextFinder(Client &stream, int timeout = 5);          // Ethernet constructor
  TextFinder(HardwareSerial &stream, int timeout = 5);  // Serial constructor

  // find methods - these seek through the data but do not return anything
  // they are useful to skip past unwanted data  
  //
  boolean find(char *target);   // reads data from the stream until the target string is found 
  // returns true if target string is found

  boolean findUntil(char *target, char *terminate);   // as above but search ends if the terminate string is found

  
  // get methods - these get a numeric value or string from the data stream  
  //
  long getValue();    // returns the first valid (long) integer value from the current position.
  // initial characters that are not digits (or the minus sign) are skipped
  // integer is terminated by the first character that is not a digit.

  long getValue(char skipChar); // as above but the given skipChar is ignored
  // this allows format characters (typically commas) in values to be ignored

  float getFloat();  // float version of getValue
  float getFloat(char skipChar);  // as above but the given skipChar is ignored
    
  int getString( char *pre_string, char *post_string, char *buffer, int length); //puts string found between given delimiters in buffer
  // string will be truncated to fit the buffer length
  // end of string determined by a match of a character to the first char of close delimiter
  // returns the number of characters placed in the buffer (0 means no valid data found) 

  };

#endif
