//
// Created by Code on 13.11.2022.
//

#ifndef IMPLY_IMPLY_H
#define IMPLY_IMPLY_H

#include <string>
#include <vector>

using namespace std;

namespace Imply
{
    string encrypt(string line);
    vector<string> split(string line, const string& delimiter);
    string decrypt(string line);
}

#endif //IMPLY_IMPLY_H
