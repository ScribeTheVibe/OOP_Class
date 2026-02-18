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
    int* pazimys = nullptr;
    int rezultatas = 0;
    double vidurkis = 0;
    double mediana = 0;
};

int main()
{
    int n = 0;      // studentu kiekis
    int p = 0;      // pazymiu kiekis
    int m;

    cout << "Pasirinkite programos eiga" << endl;
    cout << "1 - ranka ivedami duomenys\n";
    cout << "2 - automatiskai sugeneruoti pazymius\n";
    cout << "3 - sugeneruoti studentu vardus, pavardes ir pazymius\n";
    cout << "4 - baigti darba\n";
    cin >> m;

    if (m == 4) return 0;

    studentas* s = nullptr;

    srand(time(NULL));

    // ===============================
    // 1 REZIMAS - rankinis ivedimas
    // ===============================
    if (m == 1)
    {
        string temp;

        while (true)
        {
            cout << "Iveskite studento varda (arba 'exit' baigti): ";
            cin >> temp;

            if (temp == "exit")
                break;

            // Padidiname masyva
            studentas* naujas = new studentas[n + 1];

            for (int i = 0; i < n; i++)
                naujas[i] = s[i];

            delete[] s;
            s = naujas;

            s[n].vardas = temp;

            cout << "Iveskite studento pavarde: ";
            cin >> s[n].pavarde;

            cout << "Iveskite pazymiu kieki: ";
            cin >> p;

            s[n].pazimys = new int[p];
            s[n].vidurkis = 0;

            for (int j = 0; j < p; j++)
            {
                cout << "Iveskite " << j + 1 << " pazymi: ";
                cin >> s[n].pazimys[j];
                s[n].vidurkis += s[n].pazimys[j];
            }

            cout << "Iveskite egzamino rezultata: ";
            cin >> s[n].rezultatas;

            sort(s[n].pazimys, s[n].pazimys + p);

            if (p % 2 == 0)
                s[n].mediana = (s[n].pazimys[p/2 - 1] + s[n].pazimys[p/2]) / 2.0;
            else
                s[n].mediana = s[n].pazimys[p/2];

            s[n].vidurkis /= p;

            n++;
        }
    }

    // ==================================
    // 2 IR 3 REZIMAS - generavimas
    // ==================================
    else if (m == 2 || m == 3)
    {
        cout << "Iveskite studentu kieki: ";
        cin >> n;

        cout << "Iveskite pazymiu kieki: ";
        cin >> p;

        s = new studentas[n];

        for (int i = 0; i < n; i++)
        {
            if (m == 3)
            {
                s[i].vardas = vardai[rand() % 15];
                s[i].pavarde = pavardes[rand() % 15];
            }
            else
            {
                cout << "Iveskite " << i + 1 << " studento varda: ";
                cin >> s[i].vardas;
                cout << "Iveskite " << i + 1 << " studento pavarde: ";
                cin >> s[i].pavarde;
            }

            s[i].pazimys = new int[p];
            s[i].vidurkis = 0;

            for (int j = 0; j < p; j++)
            {
                s[i].pazimys[j] = rand() % 11;
                s[i].vidurkis += s[i].pazimys[j];
            }

            s[i].rezultatas = rand() % 11;

            sort(s[i].pazimys, s[i].pazimys + p);

            if (p % 2 == 0)
                s[i].mediana = (s[i].pazimys[p/2 - 1] + s[i].pazimys[p/2]) / 2.0;
            else
                s[i].mediana = s[i].pazimys[p/2];

            s[i].vidurkis /= p;
        }
    }

    // =====================
    // Rezultatu spausdinimas
    // =====================
    for (int i = 0; i < n; i++)
    {
        cout << endl;
        cout << s[i].vardas << " " << s[i].pavarde << endl;
        cout << "Galutinis (vidurkis): "
             << s[i].vidurkis * 0.4 + s[i].rezultatas * 0.6 << endl;
        cout << "Mediana: "
             << s[i].mediana * 0.4 + s[i].rezultatas * 0.6 << endl;
    }

    // =====================
    // Atminties atlaisvinimas
    // =====================
    for (int i = 0; i < n; i++)
    {
        delete[] s[i].pazimys;
    }
    delete[] s;

    return 0;
}