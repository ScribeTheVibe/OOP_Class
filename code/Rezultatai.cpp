#include <iostream>
#include <algorithm>
#include <ctime>
#include <string>
#include "VardaiPavardes.h" 

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::sort;

struct studentas {
    string vardas, pavarde;
    int* pazimys;
    int rezultatas = 0;
    double vidurkis = 0;
    double mediana = 0;
};

int main()
{
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

    studentas* s = new studentas[n];

    for (int i = 0; i < n; i++)
    {
        if (m == 3)
        {
            s[i].vardas = vardai[rand() % 15];
            s[i].pavarde = pavardes[rand() % 15];
        }
        else
        {
            cout << "Iveskite " << i + 1 << " studento varda" << endl;
            cin >> s[i].vardas;
            cout << "Iveskite " << i + 1 << " studento pavarde" << endl;
            cin >> s[i].pavarde;
        }

        s[i].pazimys = new int[p];

        for (int j = 0; j < p; j++)
        {
            if (m == 2 || m == 3)
            {
                s[i].pazimys[j] = rand() % 11;
            }
            else 
            {
                cout << "Iveskite pazymi" << endl;
                cin >> s[i].pazimys[j];
            }
            s[i].vidurkis += s[i].pazimys[j];
        }

        if (m == 2 || m == 3)
        {
            s[i].rezultatas = rand() % 11;
        }
        else 
        {
            cout << "Iveskite egzamino rezultata" << endl;
            cin >> s[i].rezultatas;
        }

        sort(s[i].pazimys, s[i].pazimys + p);

        if (p % 2 == 0)
        {
            s[i].mediana = (s[i].pazimys[p / 2 - 1] + s[i].pazimys[p / 2]) / 2.0;
        }
        else
        {
            s[i].mediana = s[i].pazimys[p / 2];
        }
        s[i].vidurkis /= p;
    }

    for (int i = 0; i < n; i++)
    {
        cout << endl;
        cout << s[i].vardas << " " << s[i].pavarde << " galutinis rezultatas:" << endl;
        cout << s[i].vidurkis * 0.4 + s[i].rezultatas * 0.6 << endl;
        cout << s[i].vardas << " " << s[i].pavarde << " mediana:" << endl;
        cout << s[i].mediana << endl << endl;
    }

    for (int i = 0; i < n; i++)
    {
        delete[] s[i].pazimys;
    }
    delete[] s;

    return 0;
}