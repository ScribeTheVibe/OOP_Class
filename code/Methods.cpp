#include "Headers.h"

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

void sortS(vector<studentas> &s, int sortType)
{
    sort(s.begin(), s.end(),
         [sortType](const studentas &a, const studentas &b)
         {
             switch (sortType)
             {
             case 2: return a.vardas  > b.vardas;
             case 3: return a.pavarde > b.pavarde;
             case 4: return a.galVid  > b.galVid;
             case 5: return a.galMed  > b.galMed;
             case 6: return a.vardas  < b.vardas;
             case 7: return a.pavarde < b.pavarde;
             case 8: return a.galVid  < b.galVid;
             case 9: return a.galMed  < b.galMed;
             default: return false;
             }
         });
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