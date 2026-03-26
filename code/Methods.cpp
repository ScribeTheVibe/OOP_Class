#include "Headers.h"

// ── Math / input helpers ──────────────────────────────────────────────────────

double skaiciuotiMediana(vector<int> &v)
{
    if (v.empty())
        return 0;

    sort(v.begin(), v.end());
    int p = v.size();

    if (p % 2 == 0)
        return (v[p / 2 - 1] + v[p / 2]) / 2.0;
    else
        return v[p / 2];
}

int saugusInt(string tekstas, int min, int max)
{
    int x;
    while (true)
    {
        cout << tekstas;
        if (cin >> x && x >= min && x <= max)
            return x;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Blogas ivedimas.\n";
    }
}

// ── File generation ───────────────────────────────────────────────────────────

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
    for (int i = 1; i <= gradeCount; i++)
        file << setw(10) << left << ("ND" + std::to_string(i));
    file << "Egz.\n";

    for (int i = 1; i <= studentCount; i++)
    {
        file << setw(24) << left << ("Vardas"  + std::to_string(i))
             << setw(30) << left << ("Pavarde" + std::to_string(i));
        for (int j = 0; j < gradeCount; j++)
            file << setw(10) << left << (rand() % 11);
        file << (rand() % 11) << "\n";
    }
}

void generuotiVisusFailus()
{
    srand(time(NULL));
    const int gradeCount = 5;

    int    sizes[] = {1000, 10000, 100000, 1000000, 10000000};
    string names[] = {
        "output/studentai_1000.txt",
        "output/studentai_10000.txt",
        "output/studentai_100000.txt",
        "output/studentai_1000000.txt",
        "output/studentai_10000000.txt"
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