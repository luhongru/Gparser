#ifndef PARSER_H
#define PARSER_H

//
// Created by Eric Chandler on 6/1/2020.
//

#include "string"
#include <vector>
using namespace std;

#ifndef GCODEPARSER_GCODEPARSER_H
#define GCODEPARSER_GCODEPARSER_H

void parseG (string location, string outLocation, std::vector<std::string> commands);

string findfile();

void fileRenamer (const char *old,const char *newold, const char *replacement);

#endif //GCODEPARSER_GCODEPARSER_H


#endif // PARSER_H
