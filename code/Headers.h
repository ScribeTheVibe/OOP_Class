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

// ── Strategy 2: one new container (blogai), erase those from original ────────
// After the call: visi contains only kietiakai, blogai contains only vargsiukai.
// list uses its own .remove_if() to avoid the O(n) shifts that erase causes.
// vector and deque use the erase-remove idiom with std::remove_if.
template<typename Container>
void isskirtiStudentus2(Container &visi, Container &blogai)
{
    if constexpr (std::is_same_v<Container, list<studentas>>)
    {
        visi.remove_if([&blogai](const studentas &s)
        {
            if (s.galVid < 5.0) { blogai.push_back(s); return true; }
            return false;
        });
    }
    else
    {
        auto it = std::remove_if(visi.begin(), visi.end(),
            [&blogai](const studentas &s)
            {
                if (s.galVid < 5.0) { blogai.push_back(s); return true; }
                return false;
            });
        visi.erase(it, visi.end());
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

// ── Strategy 3: stable_partition in-place, then splice/move the boundary ─────
// std::stable_partition rearranges the container so that all elements satisfying
// the predicate (kietiakai) come first, vargsiukai come after, and returns an
// iterator to the first vargsiukas.
//   - list   → splice() moves the vargsiukai half into blogai in O(1), no copies
//   - vector/deque → construct blogai from [mid, end), then erase that range
template<typename Container>
void isskirtiStudentus3(Container &visi, Container &blogai)
{
    auto predicate = [](const studentas &s) { return s.galVid >= 5.0; };

    if constexpr (std::is_same_v<Container, list<studentas>>)
    {
        // stable_partition works on bidirectional iterators so list is fine
        auto mid = std::stable_partition(visi.begin(), visi.end(), predicate);
        // splice transfers [mid, end) to blogai in O(1) — no element copies
        blogai.splice(blogai.begin(), visi, mid, visi.end());
    }
    else
    {
        auto mid = std::stable_partition(visi.begin(), visi.end(), predicate);
        // construct blogai from the vargsiukai half, then drop it from visi
        blogai.assign(mid, visi.end());
        visi.erase(mid, visi.end());
    }
}

// ── Strategy 1 test runner ────────────────────────────────────────────────────
template<typename Container>
void testas_vienasTipas(const string &filename, int sorting, const string &tipoPavadinimas)
{
    cout << "  [" << tipoPavadinimas << " | 1 strategija]\n";

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

    // 3. Splitting into two NEW containers (original untouched)
    Container gerai, blogai;
    auto t5 = high_resolution_clock::now();
    isskirtiStudentus(visi, gerai, blogai);
    auto t6 = high_resolution_clock::now();

    // Writing — NOT timed
    string base = filename.substr(0, filename.find_last_of('.'));
    string sufx = "_" + tipoPavadinimas + "_s1";
    issaugotiStudentus(gerai,  base + sufx + "_galvociai.txt");
    issaugotiStudentus(blogai, base + sufx + "_vargsiukai.txt");

    duration<double> dtRead  = t2 - t1;
    duration<double> dtSort  = t4 - t3;
    duration<double> dtSplit = t6 - t5;
    duration<double> dtTotal = dtRead + dtSort + dtSplit;

    cout << std::fixed << std::setprecision(3);
    cout << "    Nuskaitymas: " << dtRead.count()  << " s  (" << visi.size() << " irasu)\n";
    cout << "    Rusiavimas:  " << dtSort.count()  << " s\n";
    cout << "    Skirstymas:  " << dtSplit.count() << " s  (gerai: " << gerai.size()
         << ", blogai: " << blogai.size() << ")\n";
    cout << "    VISO:        " << dtTotal.count() << " s  (be issaugojimo)\n\n";
}

// ── Strategy 2 test runner ────────────────────────────────────────────────────
template<typename Container>
void testas_vienasTipas2(const string &filename, int sorting, const string &tipoPavadinimas)
{
    cout << "  [" << tipoPavadinimas << " | 2 strategija]\n";

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

    // 3. Splitting: blogai filled, vargsiukai erased from visi → visi becomes kietiakai
    Container blogai;
    auto t5 = high_resolution_clock::now();
    isskirtiStudentus2(visi, blogai);
    auto t6 = high_resolution_clock::now();

    // Writing — NOT timed; visi now holds only kietiakai
    string base = filename.substr(0, filename.find_last_of('.'));
    string sufx = "_" + tipoPavadinimas + "_s2";
    issaugotiStudentus(visi,   base + sufx + "_galvociai.txt");
    issaugotiStudentus(blogai, base + sufx + "_vargsiukai.txt");

    duration<double> dtRead  = t2 - t1;
    duration<double> dtSort  = t4 - t3;
    duration<double> dtSplit = t6 - t5;
    duration<double> dtTotal = dtRead + dtSort + dtSplit;

    cout << std::fixed << std::setprecision(3);
    cout << "    Nuskaitymas: " << dtRead.count()  << " s  (" << visi.size() + blogai.size() << " irasu)\n";
    cout << "    Rusiavimas:  " << dtSort.count()  << " s\n";
    cout << "    Skirstymas:  " << dtSplit.count() << " s  (kietiakai: " << visi.size()
         << ", vargsiukai: " << blogai.size() << ")\n";
    cout << "    VISO:        " << dtTotal.count() << " s  (be issaugojimo)\n\n";
}

// ── Strategy 3 test runner ────────────────────────────────────────────────────
template<typename Container>
void testas_vienasTipas3(const string &filename, int sorting, const string &tipoPavadinimas)
{
    cout << "  [" << tipoPavadinimas << " | 3 strategija]\n";

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

    // 3. stable_partition in-place, then splice/move at the boundary
    Container blogai;
    auto t5 = high_resolution_clock::now();
    isskirtiStudentus3(visi, blogai);
    auto t6 = high_resolution_clock::now();

    // Writing — NOT timed; visi now holds only kietiakai
    string base = filename.substr(0, filename.find_last_of('.'));
    string sufx = "_" + tipoPavadinimas + "_s3";
    issaugotiStudentus(visi,   base + sufx + "_galvociai.txt");
    issaugotiStudentus(blogai, base + sufx + "_vargsiukai.txt");

    duration<double> dtRead  = t2 - t1;
    duration<double> dtSort  = t4 - t3;
    duration<double> dtSplit = t6 - t5;
    duration<double> dtTotal = dtRead + dtSort + dtSplit;

    cout << std::fixed << std::setprecision(3);
    cout << "    Nuskaitymas: " << dtRead.count()  << " s  (" << visi.size() + blogai.size() << " irasu)\n";
    cout << "    Rusiavimas:  " << dtSort.count()  << " s\n";
    cout << "    Skirstymas:  " << dtSplit.count() << " s  (kietiakai: " << visi.size()
         << ", vargsiukai: " << blogai.size() << ")\n";
    cout << "    VISO:        " << dtTotal.count() << " s  (be issaugojimo)\n\n";
}

// ── Runs all 3 strategies × 3 containers for one file ────────────────────────
inline void testas_duomenuApdorojimas(const string &filename, int sorting)
{
    cout << "\n=== " << filename << " ===\n\n";

    cout << "-- Strategija 1 (du nauji konteineriai) --\n";
    testas_vienasTipas<vector<studentas>>(filename, sorting, "vector");
    testas_vienasTipas<list<studentas>>  (filename, sorting, "list");
    testas_vienasTipas<deque<studentas>> (filename, sorting, "deque");

    cout << "-- Strategija 2 (vienas naujas konteineris, trinimas is originalo) --\n";
    testas_vienasTipas2<vector<studentas>>(filename, sorting, "vector");
    testas_vienasTipas2<list<studentas>>  (filename, sorting, "list");
    testas_vienasTipas2<deque<studentas>> (filename, sorting, "deque");

    cout << "-- Strategija 3 (stable_partition + splice/move) --\n";
    testas_vienasTipas3<vector<studentas>>(filename, sorting, "vector");
    testas_vienasTipas3<list<studentas>>  (filename, sorting, "list");
    testas_vienasTipas3<deque<studentas>> (filename, sorting, "deque");
}

#endif