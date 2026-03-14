#include "Headers.h"

void generuotiFaila(const string &filename, int studentCount, int gradeCount)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Klaida: nepavyko sukurti failo " << filename << "\n";
        return;
    }

    file << "Vardas Pavarde";
    for (int i = 1; i <= gradeCount; i++)
        file << " ND" << i;
    file << " Egz.\n";

    for (int i = 1; i <= studentCount; i++)
    {
        file << "Vardas" << i << " Pavarde" << i;
        for (int j = 0; j < gradeCount; j++)
            file << " " << rand() % 11;
        file << " " << rand() % 11 << "\n";
    }

    file.close();
}

void generuotiVisusFailus()
{
    srand(time(NULL));
    const int gradeCount = 5;

    int sizes[] = {1000, 10000, 100000, 1000000, 10000000};
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

bool nuskaitytiIsFailo(const string &filename, vector<studentas> &s)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Klaida: nepavyko atidaryti " << filename << "\n";
        return false;
    }

    string line;
    getline(file, line);

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

void issaugotiStudentus(const vector<studentas> &s, const string &filename)
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
            << setw(17) << std::setprecision(3) << st.galVid
            << setw(17) << std::setprecision(3) << st.galMed << "\n";
    }
}

void testas1_failuKurimas()
{
    cout << "\n===== TYRIMAS 1: Failu kurimas =====\n";
    cout << std::left << setw(25) << "Failas"
         << setw(12) << "Irasu"
         << "Laikas (s)\n";
    cout << string(50, '-') << "\n";

    int sizes[] = {1000, 10000, 100000, 1000000, 10000000};
    string names[] = {
        "test1_1000.txt",
        "test1_10000.txt",
        "test1_100000.txt",
        "test1_1000000.txt",
        "test1_10000000.txt"
    };

    srand(42);

    for (int i = 0; i < 5; i++)
    {
        auto t1 = high_resolution_clock::now();
        generuotiFaila(names[i], sizes[i], 5);
        auto t2 = high_resolution_clock::now();
        duration<double> dt = t2 - t1;

        cout << std::left << setw(25) << names[i]
             << setw(12) << sizes[i]
             << std::fixed << std::setprecision(3) << dt.count() << "\n";
    }
    cout << "\n";
}

void testas2_duomenuApdorojimas(const string &filename)
{
    cout << "\n--- " << filename << " ---\n";

    vector<studentas> visi;
    auto t1 = high_resolution_clock::now();
    bool ok = nuskaitytiIsFailo(filename, visi);
    auto t2 = high_resolution_clock::now();

    if (!ok)
    {
        cout << "  Nepavyko nuskaityti.\n";
        return;
    }

    vector<studentas> gerai, blogai;
    auto t3 = high_resolution_clock::now();
    isskirtiStudentus(visi, gerai, blogai);
    auto t4 = high_resolution_clock::now();

    string baseName = filename.substr(0, filename.find_last_of('.'));
    auto t5 = high_resolution_clock::now();
    issaugotiStudentus(gerai,  baseName + "_galvociai.txt");
    issaugotiStudentus(blogai, baseName + "_vargsiukai.txt");
    auto t6 = high_resolution_clock::now();

    duration<double> dtRead  = t2 - t1;
    duration<double> dtSplit = t4 - t3;
    duration<double> dtWrite = t6 - t5;
    duration<double> dtTotal = t6 - t1;

    cout << std::fixed << std::setprecision(3);
    cout << "  Nuskaitymas:  " << dtRead.count()  << " s  (" << visi.size()  << " irasu)\n";
    cout << "  Rusiavimas:   " << dtSplit.count() << " s  (gerai: " << gerai.size()
         << ", blogai: " << blogai.size() << ")\n";
    cout << "  Issaugojimas: " << dtWrite.count() << " s\n";
    cout << "  VISO:         " << dtTotal.count() << " s\n";
}