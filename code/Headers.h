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
using std::deque;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::left;
using std::list;
using std::ofstream;
using std::setw;
using std::sort;
using std::string;
using std::vector;
using std::chrono::duration;
using std::chrono::high_resolution_clock;

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

// ── Non-templated declarations ────────────────────────────────────────────────

double skaiciuotiMediana(vector<int> &v);
int saugusInt(string tekstas, int min, int max);

void generuotiFaila(const string &filename, int studentCount, int gradeCount);
void generuotiVisusFailus();

extern string vardai[15];
extern string pavardes[15];

// ── Templated functions (must be defined in the header) ──────────────────────

// Works for vector<studentas>, list<studentas>, deque<studentas>
template <typename Container>
void sortS(Container &s, int sortType)
{
    auto cmp = [sortType](const studentas &a, const studentas &b)
    {
        switch (sortType)
        {
        case 2:
            return a.vardas > b.vardas;
        case 3:
            return a.pavarde > b.pavarde;
        case 4:
            return a.galVid > b.galVid;
        case 5:
            return a.galMed > b.galMed;
        case 6:
            return a.vardas < b.vardas;
        case 7:
            return a.pavarde < b.pavarde;
        case 8:
            return a.galVid < b.galVid;
        case 9:
            return a.galMed < b.galMed;
        default:
            return false;
        }
    };

    // list has its own .sort(); vector and deque use std::sort
    if constexpr (std::is_same_v<Container, list<studentas>>)
        s.sort(cmp);
    else
        std::sort(s.begin(), s.end(), cmp);
}

template <typename Container>
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

        tempS.rezultatas = tempS.pazimys.back();
        tempS.vidurkis -= tempS.rezultatas;
        tempS.pazimys.pop_back();

        if (tempS.pazimys.empty())
            continue;

        tempS.vidurkis /= tempS.pazimys.size();
        tempS.mediana = skaiciuotiMediana(tempS.pazimys);
        tempS.galVid = tempS.vidurkis * 0.4 + tempS.rezultatas * 0.6;
        tempS.galMed = tempS.mediana * 0.4 + tempS.rezultatas * 0.6;

        s.push_back(tempS);
        anyRead = true;
    }

    return anyRead;
}

template <typename Container>
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
template <typename Container>
void isskirtiStudentus2(Container &visi, Container &blogai)
{
    if constexpr (std::is_same_v<Container, list<studentas>>)
    {
        visi.remove_if([&blogai](const studentas &s)
                       {
            if (s.galVid < 5.0) { blogai.push_back(s); return true; }
            return false; });
    }
    else
    {
        auto it = std::remove_if(visi.begin(), visi.end(),
                                 [&blogai](const studentas &s)
                                 {
                                     if (s.galVid < 5.0)
                                     {
                                         blogai.push_back(s);
                                         return true;
                                     }
                                     return false;
                                 });
        visi.erase(it, visi.end());
    }
}

template <typename Container>
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

// ── Strategy 3: std::partition in-place + reserve for vector ─────────────────
// Builds on Strategy 2 (the faster single-container approach) with two
// algorithmic improvements:
//
//   1. reserve(): for vector, pre-allocates blogai to worst-case size before
//      the split, eliminating all heap reallocations during push_back.
//
//   2. std::partition (non-stable): rearranges elements via O(n) swaps rather
//      than copying/shifting, then blogai is filled from the already-separated
//      tail in one move. Unlike std::stable_partition — which is O(n log n)
//      or O(n) with a temporary O(n) buffer — std::partition is a single O(n)
//      pass with no extra allocation and no order-preservation overhead.
//
//   list: order-preserving remove_if is already optimal for a linked structure
//   (no random-access shifting), so the same S2 path is reused unchanged.
template <typename Container>
void isskirtiStudentus3(Container &visi, Container &blogai)
{
    if constexpr (std::is_same_v<Container, list<studentas>>)
    {
        // Linked list: remove_if is O(n) with no shifting — already optimal.
        visi.remove_if([&blogai](const studentas &s)
                       {
            if (s.galVid < 5.0) { blogai.push_back(s); return true; }
            return false; });
    }
    else
    {
        // vector / deque: reserve blogai to avoid repeated reallocations,
        // then use non-stable partition (O(n) swaps, no extra buffer).
        if constexpr (std::is_same_v<Container, vector<studentas>>)
            blogai.reserve(visi.size());

        auto mid = std::partition(visi.begin(), visi.end(),
                                  [](const studentas &s)
                                  { return s.galVid >= 5.0; });

        // Move elements from the vargsiukai tail into blogai, then drop them.
        blogai.assign(std::make_move_iterator(mid),
                      std::make_move_iterator(visi.end()));
        visi.erase(mid, visi.end());
    }
}

// Number of timed runs — results are averaged across all runs.
// The write step is always done once only (after all runs complete).
static constexpr int RUNS = 3;

// ── Strategy 1 test runner ────────────────────────────────────────────────────
template <typename Container>
void testas_vienasTipas(const string &filename, int sorting, const string &tipoPavadinimas)
{
    cout << "  [" << tipoPavadinimas << " | 1 strategija]\n";

    double sumRead = 0, sumSort = 0, sumSplit = 0;
    size_t nVisi = 0, nGerai = 0, nBlogai = 0;
    Container lastGerai, lastBlogai; // kept from final run for writing

    for (int run = 0; run < RUNS; run++)
    {
        // 1. Reading — fresh container each run
        Container visi;
        auto t1 = high_resolution_clock::now();
        bool ok = nuskaitytiIsFailo(filename, visi);
        auto t2 = high_resolution_clock::now();

        if (!ok)
        {
            cout << "    Nepavyko nuskaityti.\n";
            return;
        }
        nVisi = visi.size();

        // 2. Sorting
        auto t3 = high_resolution_clock::now();
        if (sorting != 1)
            sortS(visi, sorting);
        auto t4 = high_resolution_clock::now();

        // 3. Split into two new containers
        Container gerai, blogai;
        auto t5 = high_resolution_clock::now();
        isskirtiStudentus(visi, gerai, blogai);
        auto t6 = high_resolution_clock::now();

        sumRead += duration<double>(t2 - t1).count();
        sumSort += duration<double>(t4 - t3).count();
        sumSplit += duration<double>(t6 - t5).count();

        if (run == RUNS - 1)
        {
            nGerai = gerai.size();
            nBlogai = blogai.size();
            lastGerai = std::move(gerai);
            lastBlogai = std::move(blogai);
        }
    }

    // Writing — NOT timed, done once after all runs
    string base = filename.substr(0, filename.find_last_of('.'));
    string sufx = "_" + tipoPavadinimas + "_s1";
    issaugotiStudentus(lastGerai, base + sufx + "_galvociai.txt");
    issaugotiStudentus(lastBlogai, base + sufx + "_vargsiukai.txt");

    double avgRead = sumRead / RUNS;
    double avgSort = sumSort / RUNS;
    double avgSplit = sumSplit / RUNS;
    double avgTotal = avgRead + avgSort + avgSplit;

    cout << std::fixed << std::setprecision(3);
    cout << "    Vidurkis is " << RUNS << " kartu:\n";
    cout << "    Nuskaitymas: " << avgRead << " s  (" << nVisi << " irasu)\n";
    cout << "    Rusiavimas:  " << avgSort << " s\n";
    cout << "    Skirstymas:  " << avgSplit << " s  (gerai: " << nGerai
         << ", blogai: " << nBlogai << ")\n";
    cout << "    VISO:        " << avgTotal << " s  (be issaugojimo)\n\n";
}

// ── Strategy 2 test runner ────────────────────────────────────────────────────
template <typename Container>
void testas_vienasTipas2(const string &filename, int sorting, const string &tipoPavadinimas)
{
    cout << "  [" << tipoPavadinimas << " | 2 strategija]\n";

    double sumRead = 0, sumSort = 0, sumSplit = 0;
    size_t nVisi = 0, nKietiakai = 0, nBlogai = 0;
    Container lastVisi, lastBlogai;

    for (int run = 0; run < RUNS; run++)
    {
        // 1. Reading — fresh container each run
        Container visi;
        auto t1 = high_resolution_clock::now();
        bool ok = nuskaitytiIsFailo(filename, visi);
        auto t2 = high_resolution_clock::now();

        if (!ok)
        {
            cout << "    Nepavyko nuskaityti.\n";
            return;
        }
        nVisi = visi.size();

        // 2. Sorting
        auto t3 = high_resolution_clock::now();
        if (sorting != 1)
            sortS(visi, sorting);
        auto t4 = high_resolution_clock::now();

        // 3. One new container; erase vargsiukai from original
        Container blogai;
        auto t5 = high_resolution_clock::now();
        isskirtiStudentus2(visi, blogai);
        auto t6 = high_resolution_clock::now();

        sumRead += duration<double>(t2 - t1).count();
        sumSort += duration<double>(t4 - t3).count();
        sumSplit += duration<double>(t6 - t5).count();

        if (run == RUNS - 1)
        {
            nKietiakai = visi.size();
            nBlogai = blogai.size();
            lastVisi = std::move(visi);
            lastBlogai = std::move(blogai);
        }
    }

    // Writing — NOT timed, done once after all runs
    string base = filename.substr(0, filename.find_last_of('.'));
    string sufx = "_" + tipoPavadinimas + "_s2";
    issaugotiStudentus(lastVisi, base + sufx + "_galvociai.txt");
    issaugotiStudentus(lastBlogai, base + sufx + "_vargsiukai.txt");

    double avgRead = sumRead / RUNS;
    double avgSort = sumSort / RUNS;
    double avgSplit = sumSplit / RUNS;
    double avgTotal = avgRead + avgSort + avgSplit;

    cout << std::fixed << std::setprecision(3);
    cout << "    Vidurkis is " << RUNS << " kartu:\n";
    cout << "    Nuskaitymas: " << avgRead << " s  (" << nVisi << " irasu)\n";
    cout << "    Rusiavimas:  " << avgSort << " s\n";
    cout << "    Skirstymas:  " << avgSplit << " s  (kietiakai: " << nKietiakai
         << ", vargsiukai: " << nBlogai << ")\n";
    cout << "    VISO:        " << avgTotal << " s  (be issaugojimo)\n\n";
}

// ── Strategy 3 test runner ────────────────────────────────────────────────────
template <typename Container>
void testas_vienasTipas3(const string &filename, int sorting, const string &tipoPavadinimas)
{
    cout << "  [" << tipoPavadinimas << " | 3 strategija]\n";

    double sumRead = 0, sumSort = 0, sumSplit = 0;
    size_t nVisi = 0, nKietiakai = 0, nBlogai = 0;
    Container lastVisi, lastBlogai;

    for (int run = 0; run < RUNS; run++)
    {
        // 1. Reading — fresh container each run
        Container visi;
        auto t1 = high_resolution_clock::now();
        bool ok = nuskaitytiIsFailo(filename, visi);
        auto t2 = high_resolution_clock::now();

        if (!ok)
        {
            cout << "    Nepavyko nuskaityti.\n";
            return;
        }
        nVisi = visi.size();

        // 2. Sorting
        auto t3 = high_resolution_clock::now();
        if (sorting != 1)
            sortS(visi, sorting);
        auto t4 = high_resolution_clock::now();

        // 3. partition in-place + reserve
        Container blogai;
        auto t5 = high_resolution_clock::now();
        isskirtiStudentus3(visi, blogai);
        auto t6 = high_resolution_clock::now();

        sumRead += duration<double>(t2 - t1).count();
        sumSort += duration<double>(t4 - t3).count();
        sumSplit += duration<double>(t6 - t5).count();

        if (run == RUNS - 1)
        {
            nKietiakai = visi.size();
            nBlogai = blogai.size();
            lastVisi = std::move(visi);
            lastBlogai = std::move(blogai);
        }
    }

    // Writing — NOT timed, done once after all runs
    string base = filename.substr(0, filename.find_last_of('.'));
    string sufx = "_" + tipoPavadinimas + "_s3";
    issaugotiStudentus(lastVisi, base + sufx + "_galvociai.txt");
    issaugotiStudentus(lastBlogai, base + sufx + "_vargsiukai.txt");

    double avgRead = sumRead / RUNS;
    double avgSort = sumSort / RUNS;
    double avgSplit = sumSplit / RUNS;
    double avgTotal = avgRead + avgSort + avgSplit;

    cout << std::fixed << std::setprecision(3);
    cout << "    Vidurkis is " << RUNS << " kartu:\n";
    cout << "    Nuskaitymas: " << avgRead << " s  (" << nVisi << " irasu)\n";
    cout << "    Rusiavimas:  " << avgSort << " s\n";
    cout << "    Skirstymas:  " << avgSplit << " s  (kietiakai: " << nKietiakai
         << ", vargsiukai: " << nBlogai << ")\n";
    cout << "    VISO:        " << avgTotal << " s  (be issaugojimo)\n\n";
}

// ── Runs all 3 strategies × 3 containers for one file ────────────────────────
inline void testas_duomenuApdorojimas(const string &filename, int sorting)
{
    cout << "\n=== " << filename << " ===\n\n";

    cout << "-- Strategija 1 (du nauji konteineriai) --\n";
    testas_vienasTipas<vector<studentas>>(filename, sorting, "vector");
    testas_vienasTipas<list<studentas>>(filename, sorting, "list");
    testas_vienasTipas<deque<studentas>>(filename, sorting, "deque");

    cout << "-- Strategija 2 (vienas naujas konteineris, trinimas is originalo) --\n";
    testas_vienasTipas2<vector<studentas>>(filename, sorting, "vector");
    testas_vienasTipas2<list<studentas>>(filename, sorting, "list");
    testas_vienasTipas2<deque<studentas>>(filename, sorting, "deque");

    cout << "-- Strategija 3 (std::partition + reserve) --\n";
    testas_vienasTipas3<vector<studentas>>(filename, sorting, "vector");
    testas_vienasTipas3<list<studentas>>(filename, sorting, "list");
    testas_vienasTipas3<deque<studentas>>(filename, sorting, "deque");
}

#endif