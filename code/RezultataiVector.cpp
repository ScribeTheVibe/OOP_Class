#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string>
#include <cctype>
#include "VardaiPavardes.h"
#include <fstream>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::left;
using std::ofstream;
using std::setw;
using std::sort;
using std::string;
using std::vector;

struct studentas
{
    string vardas, pavarde;
    vector<int> pazimys;
    int rezultatas = 0;
    double vidurkis = 0;
    double mediana = 0;
    double galVid;
    double galMed;
};

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

int main()
{
    vector<studentas> s;
    studentas tempS;
    int m;

    cout << "Pasirinkite programos eiga\n";
    cout << "1 - ranka ivedami duomenys\n";
    cout << "2 - is failo ivedami duomenys\n";
    cout << "3 - automatiskai sugeneruoti pazymius\n";
    cout << "4 - sugeneruoti studentu vardus, pavardes ir pazymius\n";
    cout << "5 - baigti darba\n\n";

    m = saugusInt("Pasirinkimas: ", 1, 5);

    if (m == 5)
        return 0;

    if (m == 1)
    {
        string input;

        while (true)
        {
            tempS = studentas();

            cout << "\nIveskite studento varda (exit - baigti): ";
            cin >> input;

            if (input == "exit")
                break;

            tempS.vardas = input;

            cout << "Iveskite pavarde: ";
            cin >> tempS.pavarde;

            cout << "Iveskite pazymius (exit - baigti):\n";

            while (true)
            {
                cin >> input;

                if (input == "exit")
                    break;

                bool valid = true;
                for (char c : input)
                    if (!isdigit(c))
                        valid = false;

                if (!valid)
                {
                    cout << "Blogas ivedimas.\n";
                    continue;
                }

                int paz = stoi(input);

                if (paz < 0 || paz > 10)
                {
                    cout << "Pazymys 0-10.\n";
                    continue;
                }

                tempS.pazimys.push_back(paz);
                tempS.vidurkis += paz;
            }

            if (tempS.pazimys.empty())
            {
                cout << "Studentas neturi pazymiu — praleistas.\n";
                continue;
            }

            tempS.vidurkis /= tempS.pazimys.size();

            tempS.rezultatas = saugusInt("Egzamino rezultatas: ", 0, 10);

            tempS.mediana = skaiciuotiMediana(tempS.pazimys);

            tempS.galVid = tempS.vidurkis * 0.4 + tempS.rezultatas * 0.6;

            tempS.galMed = tempS.vidurkis * 0.4 + tempS.rezultatas * 0.6;

            s.push_back(tempS);
        }
    }

    else if (m == 3 || m == 4)
    {
        srand(time(NULL));
        int n, p;
        n = saugusInt("Iveskite studentu kieki: ", 1, 1000000);
        p = saugusInt("Iveskite pazymiu kieki: ", 1, 1000);

        s.reserve(n);

        for (int i = 0; i < n; i++)
        {
            tempS = studentas();

            if (m == 4)
            {
                tempS.vardas = vardai[rand() % 15];
                tempS.pavarde = pavardes[rand() % 15];
            }
            else
            {
                cout << "Vardas: ";
                cin >> tempS.vardas;
                cout << "Pavarde: ";
                cin >> tempS.pavarde;
            }

            for (int j = 0; j < p; j++)
            {
                int paz = rand() % 11;
                tempS.pazimys.push_back(paz);
                tempS.vidurkis += paz;
            }

            tempS.vidurkis /= p;
            tempS.rezultatas = rand() % 11;
            tempS.mediana = skaiciuotiMediana(tempS.pazimys);
            tempS.galVid = tempS.vidurkis * 0.4 + tempS.rezultatas * 0.6;
            tempS.galMed = tempS.vidurkis * 0.4 + tempS.rezultatas * 0.6;

            s.push_back(tempS);
        }
    }

    else
    {
        ifstream file("kursiokai.txt");
        string skip;
        bool firstTime = true;
        getline(file, skip);
        int temp;
        while (true)
        {
            tempS = studentas();
            if (file >> tempS.vardas >> tempS.pavarde)
            {
                while (true)
                {
                    if (file >> temp)
                    {
                        tempS.pazimys.push_back(temp);
                        tempS.vidurkis += temp;
                        tempS.rezultatas = temp;
                    }
                    else
                    {
                        file.clear();
                        tempS.pazimys.pop_back();
                        tempS.vidurkis -= tempS.rezultatas;
                        break;
                    }
                }
                tempS.vidurkis /= tempS.pazimys.size();
                tempS.mediana = skaiciuotiMediana(tempS.pazimys);
                tempS.galVid = tempS.vidurkis * 0.4 + tempS.rezultatas * 0.6;
                tempS.galMed = tempS.vidurkis * 0.4 + tempS.rezultatas * 0.6;
                s.push_back(tempS);
                firstTime = false;
            }
            else if (firstTime)
            {
                cout << "failas tuscias arba netinkamas formatas";
                return 0;
            }
            else
                break;
        }
    }

    cout << "\nPasirinkite isvedima\n"
         << "1 - i terminala\n2 - i faila\n\n";
    cout << "Pasirinkimas: ";
    m = saugusInt("Pasirinkimas: ", 1, 2);

    int sor;
    cout << "\nPasirinkite rusiavima\n"
         << "1 - nerusiuoti\n2 - pagal varda zemyn\n3 - pagal pavarde zemyn\n4 - pagal Galutinis (vid.) zemyn\n5 - pagal Galutinis (med).) zemyn\n"
         << "6 - pagal varda aukstyn\n7 - pagal pavarde aukstyn\n8 - pagal Galutinis (vid.) aukstyn\n9 - pagal Galutinis (med).) aukstyn\n\n";
    cout << "Pasirinkimas: ";
    sor = saugusInt("Pasirinkimas: ", 1, 9);
    cout << endl;

    if (m == 1)
    {
        if (sor != 1)
            sortS(s, sor);
        cout << "===== REZULTATAI =====\n";
        cout << "\nVardas       Pavarde      Galutinis (vid.)  Galutinis (med.)  \n\n";
        for (const auto &st : s)
        {
            cout << setw(20) << left;

            cout << st.vardas << " " << setw(20) << left << st.pavarde << " ";

            cout << setw(17) << left << std::setprecision(3);

            cout << st.galVid << " ";

            cout << setw(17) << left << std::setprecision(3);

            cout << st.galMed << endl;
        }
    }
    else
    {
        if (sor != 1)
            sortS(s, sor);
        ofstream out("isvedimas.txt");
        out << "===== REZULTATAI =====\n";
        out << "\nVardas               Pavarde              Galutinis (vid.)  Galutinis (med.)  \n\n";
        for (const auto &st : s)
        {
            out << setw(20) << left;

            out << st.vardas << " " << setw(20) << left << st.pavarde << " ";

            out << setw(17) << left << std::setprecision(3);

            out << st.galVid << " ";

            out << setw(17) << left << std::setprecision(3);

            out << st.galMed << endl;
        }
    }
    return 0;
}
