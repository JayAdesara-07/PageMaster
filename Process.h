#pragma once

#include <vector>
#include <string>
using namespace std;

class Process {
public:
    string fileName;
    int pid;
    int size;
    bool inMain;
    vector<int> pageTable;

    bool isFileNameValid();
};