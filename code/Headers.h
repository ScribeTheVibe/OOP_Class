#ifndef Headers_H
#define Headers_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::left;
using std::ofstream;
using std::setw;
using std::sort;
using std::string;
using std::vector;

struct studentas
{
    string vardas, pavarde;
    vector<int> pazimys;
    int rezultatas = 0;
    double vidurkis = 0;
    double mediana = 0;
    double galVid = 0;
    double galMed = 0;
};

double skaiciuotiMediana(vector<int> &v);
int saugusInt(string tekstas, int min, int max);
void sortS(vector<studentas> &s, int sortType);

extern string vardai[15];
extern string pavardes[15];

#endif