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
#include <chrono>

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
using std::chrono::high_resolution_clock;
using std::chrono::duration;

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
int    saugusInt(string tekstas, int min, int max);
void   sortS(vector<studentas> &s, int sortType);
bool   nuskaitytiIsFailo(const string &filename, vector<studentas> &s);

void generuotiFaila(const string &filename, int studentCount, int gradeCount);
void generuotiVisusFailus();
void isskirtiStudentus(const vector<studentas> &visi,
                       vector<studentas> &gerai,
                       vector<studentas> &blogai);
void testas_duomenuApdorojimas(const string &filename, int sorting);

extern string vardai[15];
extern string pavardes[15];

#endif