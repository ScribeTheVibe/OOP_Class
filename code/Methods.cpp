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
         });
}
