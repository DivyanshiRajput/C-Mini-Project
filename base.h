#ifndef BASE
#define BASE
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <vector>
#include <utility>
using namespace std;
class base
{
protected:
    string inp,out;
    ifstream file1;
    ofstream file2;
    int i;
public:
    base();
    ~base();
    virtual void read(char*filename) = 0;
    virtual void execute() = 0;
    virtual void write() = 0;
};
#endif 