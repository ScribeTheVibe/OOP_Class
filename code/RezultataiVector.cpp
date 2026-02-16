#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "VardaiPavardes.h"

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::sort;

struct studentas {
    string vardas, pavarde;
    vector<int> pazimys;
    int rezultatas = 0;
    double vidurkis = 0;
    double mediana = 0;
};

int main()
{
    vector<studentas> s;
    studentas tempS;
    int n, p, m;
    
    cout << "Pasirinkite programos eiga" << endl;
    cout << "1 - ranka ivedami duomenys\n2 - automatiskai sugeneruoti pazymius\n3 - sugeneruoti studentu vardus, pavardes ir pazymius\n4 - baigti darba\n";
    cin >> m;
    
    if (m == 4) return 0;
    if (m == 2 || m == 3) srand(time(NULL));
    
    cout << "Iveskite studentu kieki" << endl;
    cin >> n;
    cout << "Iveskite pazymiu kieki" << endl;
    cin >> p;
    
    s.reserve(n);

    int temp;
    for (int i = 0; i < n; i++)
    {
        if (m == 3)
        {
            tempS.vardas = vardai[rand() % 15];
            tempS.pavarde = pavardes[rand() % 15];
        }
        else
        {
            cout << "Iveskite " << i + 1 << " studento varda" << endl;
            cin >> tempS.vardas;
            cout << "Iveskite " << i + 1 << " studento pavarde" << endl;
            cin >> tempS.pavarde;
        }

        for (int j = 0; j < p; j++)
        {
            if (m == 2 || m == 3)
            {
                temp = rand() % 11;
            }
            else 
            {
                cout << "Iveskite pazymi" << endl;
                cin >> temp;
            }
            tempS.pazimys.push_back(temp);
            tempS.vidurkis += temp;
        }

        if (m == 2 || m == 3)
        {
            tempS.rezultatas = rand() % 11;
        }
        else 
        {
            cout << "Iveskite egzamino rezultata" << endl;
            cin >> tempS.rezultatas;
        }

        sort(tempS.pazimys.begin(), tempS.pazimys.end());

        if (p % 2 == 0)
        {
            tempS.mediana = (tempS.pazimys[p / 2 - 1] + tempS.pazimys[p / 2]) / 2.0;
        }
        else
        {
            tempS.mediana = tempS.pazimys[p / 2];
        }

        tempS.vidurkis /= p;
        s.push_back(tempS);
        tempS.pazimys.clear();
        tempS.vidurkis = 0;
    }
    
    for (int i = 0; i < s.size(); i++)
    {
        cout << endl;
        cout << s[i].vardas << " " << s[i].pavarde << " galutinis rezultatas:" << endl;
        cout << s[i].vidurkis * 0.4 + s[i].rezultatas * 0.6 << endl;
        cout << s[i].vardas << " " << s[i].pavarde << " mediana:" << endl;
        cout << s[i].mediana << endl << endl;
    }
    return 0;
}