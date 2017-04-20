#include <iostream>
#include "help.h"

vector<string>& split(const string& str,char delim,vector<string>& result)
{
    string::size_type pos1 = 0,pos2 = str.find(delim);
    while(string::npos != pos2){
        result.push_back(str.substr(pos1,pos2-pos1));

        pos1 = pos2 + 1;
        pos2 = str.find(delim,pos1);

    }
    result.push_back(str.substr(pos1));
    return result;
}
