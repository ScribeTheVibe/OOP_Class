#ifndef Headers_H
#define Headers_H

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <ctime>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <chrono>
#include <type_traits>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::left;
using std::list;
using std::deque;
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
    double mediana  = 0;
    double galVid   = 0;
    double galMed   = 0;
};

// ── Non-templated declarations ────────────────────────────────────────────────

double skaiciuotiMediana(vector<int> &v);
int    saugusInt(string tekstas, int min, int max);

void generuotiFaila(const string &filename, int studentCount, int gradeCount);
void generuotiVisusFailus();

extern string vardai[15];
extern string pavardes[15];

// ── Templated functions (must be defined in the header) ──────────────────────

// Works for vector<studentas>, list<studentas>, deque<studentas>
template<typename Container>
void sortS(Container &s, int sortType)
{
    auto cmp = [sortType](const studentas &a, const studentas &b)
    {
        switch (sortType)
        {
        case 2:  return a.vardas  > b.vardas;
        case 3:  return a.pavarde > b.pavarde;
        case 4:  return a.galVid  > b.galVid;
        case 5:  return a.galMed  > b.galMed;
        case 6:  return a.vardas  < b.vardas;
        case 7:  return a.pavarde < b.pavarde;
        case 8:  return a.galVid  < b.galVid;
        case 9:  return a.galMed  < b.galMed;
        default: return false;
        }
    };

    // list has its own .sort(); vector and deque use std::sort
    if constexpr (std::is_same_v<Container, list<studentas>>)
        s.sort(cmp);
    else
        std::sort(s.begin(), s.end(), cmp);
}

template<typename Container>
bool nuskaitytiIsFailo(const string &filename, Container &s)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Klaida: nepavyko atidaryti " << filename << "\n";
        return false;
    }

    string line;
    getline(file, line); // skip header

    bool anyRead = false;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        istringstream iss(line);
        studentas tempS;

        if (!(iss >> tempS.vardas >> tempS.pavarde))
            continue;

        int temp;
        while (iss >> temp)
        {
            tempS.pazimys.push_back(temp);
            tempS.vidurkis += temp;
        }

        if (tempS.pazimys.empty())
            continue;

        tempS.rezultatas  = tempS.pazimys.back();
        tempS.vidurkis   -= tempS.rezultatas;
        tempS.pazimys.pop_back();

        if (tempS.pazimys.empty())
            continue;

        tempS.vidurkis /= tempS.pazimys.size();
        tempS.mediana   = skaiciuotiMediana(tempS.pazimys);
        tempS.galVid    = tempS.vidurkis * 0.4 + tempS.rezultatas * 0.6;
        tempS.galMed    = tempS.mediana  * 0.4 + tempS.rezultatas * 0.6;

        s.push_back(tempS);
        anyRead = true;
    }

    return anyRead;
}

template<typename Container>
void isskirtiStudentus(const Container &visi,
                       Container &gerai,
                       Container &blogai)
{
    for (const auto &st : visi)
    {
        if (st.galVid >= 5.0)
            gerai.push_back(st);
        else
            blogai.push_back(st);
    }
}

template<typename Container>
void issaugotiStudentus(const Container &s, const string &filename)
{
    ofstream out(filename);
    out << std::left
        << setw(20) << "Vardas"
        << setw(20) << "Pavarde"
        << setw(17) << "Galutinis (vid.)"
        << setw(17) << "Galutinis (med.)" << "\n\n";

    for (const auto &st : s)
    {
        out << std::left
            << setw(20) << st.vardas
            << setw(20) << st.pavarde
            << setw(17) << std::fixed << std::setprecision(3) << st.galVid
            << setw(17) << std::fixed << std::setprecision(3) << st.galMed << "\n";
    }
}

// Runs the full pipeline for one container type and prints timing.
// Only reading, sorting, and splitting are measured — writing is excluded
// because it does not depend on the container type.
template<typename Container>
void testas_vienasTipas(const string &filename, int sorting, const string &tipoPavadinimas)
{
    cout << "  [" << tipoPavadinimas << "]\n";

    // 1. Reading
    Container visi;
    auto t1 = high_resolution_clock::now();
    bool ok = nuskaitytiIsFailo(filename, visi);
    auto t2 = high_resolution_clock::now();

    if (!ok) { cout << "    Nepavyko nuskaityti.\n"; return; }

    // 2. Sorting
    auto t3 = high_resolution_clock::now();
    if (sorting != 1)
        sortS(visi, sorting);
    auto t4 = high_resolution_clock::now();

    // 3. Splitting into two groups
    Container gerai, blogai;
    auto t5 = high_resolution_clock::now();
    isskirtiStudentus(visi, gerai, blogai);
    auto t6 = high_resolution_clock::now();

    // Writing — NOT timed, does not affect total
    string base = filename.substr(0, filename.find_last_of('.'));
    string sufx = "_" + tipoPavadinimas;
    issaugotiStudentus(gerai,  base + sufx + "_galvociai.txt");
    issaugotiStudentus(blogai, base + sufx + "_vargsiukai.txt");

    duration<double> dtRead  = t2 - t1;
    duration<double> dtSort  = t4 - t3;
    duration<double> dtSplit = t6 - t5;
    duration<double> dtTotal = dtRead + dtSort + dtSplit; // write excluded

    cout << std::fixed << std::setprecision(3);
    cout << "    Nuskaitymas: " << dtRead.count()  << " s  (" << visi.size() << " irasu)\n";
    cout << "    Rusiavimas:  " << dtSort.count()  << " s\n";
    cout << "    Skirstymas:  " << dtSplit.count() << " s  (gerai: " << gerai.size()
         << ", blogai: " << blogai.size() << ")\n";
    cout << "    VISO:        " << dtTotal.count() << " s  (be issaugojimo)\n\n";
}

// Runs all three container types for one file
inline void testas_duomenuApdorojimas(const string &filename, int sorting)
{
    cout << "\n--- " << filename << " ---\n";
    testas_vienasTipas<vector<studentas>>(filename, sorting, "vector");
    testas_vienasTipas<list<studentas>>  (filename, sorting, "list");
    testas_vienasTipas<deque<studentas>> (filename, sorting, "deque");
}

#endif