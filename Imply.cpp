//
// Created by Code on 13.11.2022.
//

#include "headers/Imply.h"
#include <fstream>
#include <regex>

using namespace std;

string Imply::encrypt(string line)
{
    int key = (int) line[0];
    string result = to_string(key) + "@";

    for(auto letter : line)
    {
        int code = (int) letter - key;
        int separator = abs(code + 33);

        if(separator <= 33) separator += 33;
        if(separator >= 48 && separator <= 57) separator += 10;

        result += to_string(code);
        result += (char) separator;
    }

    return result;
}

vector<string> Imply::split(string line, const string &delimiter)
{
    vector <string> vec{};
    string token{};
    size_t pos;

    while((pos = line.find(delimiter)) != string::npos)
    {
        token = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());

        vec.push_back(token);
    }

    vec.push_back(line);
    return vec;
}

string Imply::decrypt(string line)
{
    int key = stoi(split(line, "@")[0]);
    line.erase(0, line.find('@') + 1);

    smatch smatched;
    regex reg {"-?\\d+"};
    bool founded{};
    string result{};

    while((founded = regex_search(line, smatched, reg)))
    {
        int letterCode = (stoi(smatched.str()) + key);
        result += (char) letterCode;
        line = smatched.suffix().str();
    }

    return result;
}
