//
// Created by Guildmaster Tom on 6/1/2020.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "parser.h"
#include <vector>


char inArray[100];
string line; //string version of the line
string command; //just the g or m command
const string acceptableCommands[3] = {"G1","G0","G28"}; //example commands that will be kept MAKE THIS TXT FILE LATER


//This function parses through the gcode and makes a copy gcode file
//that contains only the commands deemed worthy to be in the presence of our greatness
void parseG (string location, string outLocation, std::vector<std::string> commands) {
    ifstream infile;   //input file object
    infile.open(location, ios_base::in ); //opens the target file in read  mode.

    ofstream outfile;   //output file object
    outfile.open(outLocation ,ios_base::out); //will create new file for writing

    //checks whether the opens worked
    if(infile.is_open() && outfile.is_open()) {
        //will keep going until it can't see the next character
        //the if statement is just a redundancy that I added to make myself feel safer
        while (infile.peek() != EOF) {
            if(infile.peek() == EOF){
                if(infile.eof()){
                    break;
                }else{
                    cout << endl << endl << "something went terribly wrong" << endl << endl;
                }
            }

            infile.getline(inArray, 100); //100 is way longer than any line could reasonably be.
            line = inArray; //That's right, I overloaded the char array into a string. Deal with it.
            command = line.substr(0, line.find(' '));   //walks through the line until the first whitespace (end of the command)

            //iterates through entire Acceptable Commands array
            //the logic is for the current line to be written into the open ofstream file only if the command matches one of the listed whitelisted
            //commands or if the first character happens to be a ;comment
            //You need to flush after getting a possitive, otherwise the comment line will get written a bunch
            for (unsigned int i = 0; i < commands.size(); i = i + 1) {

                if (command == commands[i] || line.at(0) == ';') {
                    outfile.write(inArray, sizeof(line)); //dump the array onto the line
                    outfile.write("\n",1);  //getline doesn't retrieve a \n at the end, so I added one myself
                    outfile.flush();   //clear the stream. Technically not needed, but why not?
                    break;  //keeps the comments from getting printed multiple times
                }
            }
        }
    }else{cout << "Failed to find/open target files" << endl;}




    infile.close();   //close the file
    outfile.close();
    outfile.flush();    //one final flush for good luck


}
