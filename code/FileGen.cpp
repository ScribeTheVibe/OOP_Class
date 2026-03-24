#include "Headers.h"

void generuotiFaila(const string &filename, int studentCount, int gradeCount)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Klaida: nepavyko sukurti failo " << filename << "\n";
        return;
    }

    file << setw(24) << left << "Vardas" 
        << setw(30) << left << "Pavarde";
    for (int i = 1; i <= gradeCount; i++) {
        file << setw(10) << left << ("ND" + std::to_string(i));
    }
    file << "Egz.\n";

    for (int i = 1; i <= studentCount; i++) {
        file << setw(24) << left << ("Vardas" + std::to_string(i))
            << setw(30) << left << ("Pavarde" + std::to_string(i));

        for (int j = 0; j < gradeCount; j++) {
            file << setw(10) << left << (rand() % 11);
        }
        file << (rand() % 11) << "\n";
    }

    file.close();
}

void generuotiVisusFailus()
{
    srand(time(NULL));
    const int gradeCount = 5;

    int    sizes[] = {1000, 10000, 100000, 1000000, 10000000};
    string names[] = {
        "studentai_1000.txt",
        "studentai_10000.txt",
        "studentai_100000.txt",
        "studentai_1000000.txt",
        "studentai_10000000.txt"
    };

    for (int i = 0; i < 5; i++)
    {
        cout << "Generuojamas " << names[i] << " (" << sizes[i] << " irasu)...";
        cout.flush();
        auto t1 = high_resolution_clock::now();
        generuotiFaila(names[i], sizes[i], gradeCount);
        auto t2 = high_resolution_clock::now();
        duration<double> dt = t2 - t1;
        cout << " " << std::fixed << std::setprecision(3) << dt.count() << " s\n";
    }
    cout << "Visi failai sugeneruoti.\n";
}

void isskirtiStudentus(const vector<studentas> &visi,
                       vector<studentas> &gerai,
                       vector<studentas> &blogai)
{
    for (const auto &st : visi)
    {
        if (st.galVid >= 5.0)
            gerai.push_back(st);
        else
            blogai.push_back(st);
    }
}

void issaugotiStudentus(vector<studentas> &s, const string &filename, int sor)
{
    if (sor != 1)
    {
        sortS(s, sor);
    }

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
            << setw(17) << std::setprecision(3) << st.galVid
            << setw(17) << std::setprecision(3) << st.galMed << "\n";
    }
}

void testas_duomenuApdorojimas(const string &filename, int sorting)
{
    cout << "\n--- " << filename << " ---\n";

    vector<studentas> visi;
    auto t1 = high_resolution_clock::now();
    bool ok = nuskaitytiIsFailo(filename, visi);
    auto t2 = high_resolution_clock::now();

    if (!ok) { cout << "  Nepavyko nuskaityti.\n"; return; }

    vector<studentas> gerai, blogai;
    auto t3 = high_resolution_clock::now();
    isskirtiStudentus(visi, gerai, blogai);
    auto t4 = high_resolution_clock::now();

    string base = filename.substr(0, filename.find_last_of('.'));
    auto t5 = high_resolution_clock::now();
    issaugotiStudentus(gerai,  base + "_galvociai.txt", sorting);
    issaugotiStudentus(blogai, base + "_vargsiukai.txt", sorting);
    auto t6 = high_resolution_clock::now();

    duration<double> dtRead  = t2 - t1;
    duration<double> dtSplit = t4 - t3;
    duration<double> dtWrite = t6 - t5;
    duration<double> dtTotal = t6 - t1;

    cout << std::fixed << std::setprecision(3);
    cout << "  Nuskaitymas:  " << dtRead.count()  << " s  (" << visi.size() << " irasu)\n";
    cout << "  Skirstymas:   " << dtSplit.count() << " s  (gerai: " << gerai.size()
         << ", blogai: " << blogai.size() << ")\n";
    cout << "  Rusiavimas + Issaugojimas: " << dtWrite.count() << " s\n";
    cout << "  VISO:         " << dtTotal.count() << " s\n";
}