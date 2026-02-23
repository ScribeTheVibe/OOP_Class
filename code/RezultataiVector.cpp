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
using std::ofstream;
using std::sort;
using std::string;
using std::vector;
using std::setw;
using std::left;

struct studentas
{
    string vardas, pavarde;
    vector<int> pazimys;
    int rezultatas = 0;
    double vidurkis = 0;
    double mediana = 0;
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

int main()
{
    vector<studentas> s;
    studentas tempS;

    int n, p, m;

    cout << "Pasirinkite programos eiga\n";
    cout << "1 - ranka ivedami duomenys\n";
    cout << "2 - is failo ivedami duomenys\n";
    cout << "3 - automatiskai sugeneruoti pazymius\n";
    cout << "4 - sugeneruoti studentu vardus, pavardes ir pazymius\n";
    cout << "5 - baigti darba\n\n";

    m = saugusInt("Pasirinkimas: ", 1, 5);

    if (m == 5)
        return 0;

    if (m == 3 || m == 4)
        srand(time(NULL));

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

            tempS.rezultatas =
                saugusInt("Egzamino rezultatas: ", 0, 10);

            tempS.mediana =
                skaiciuotiMediana(tempS.pazimys);

            s.push_back(tempS);
        }
    }

    else if (m == 3 || m == 4)
    {
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
                for (int i = 0; i < 15; i++)
                {
                    if(file >> temp)
                    {
                        tempS.pazimys.push_back(temp);
                        tempS.vidurkis += temp;
                    }
                    else
                    {
                        cout<<"failas netinkamu formatu";
                        return 0;
                    }
                }
                file >> tempS.rezultatas;
                tempS.vidurkis /= tempS.pazimys.size();
                tempS.mediana = skaiciuotiMediana(tempS.pazimys);
                s.push_back(tempS);
                firstTime = false;
            }
            else if(firstTime)
            {
                cout<<"failas tuscias arba netinkamas formatas";
                return 0;
            } 
            else break;
        }
    }

    cout<<"\nPasirinkite isvedima\n"<<"1 - i terminala\n2 - i faila\n";
    cout<<"Pasirinkimas: ";
    m = saugusInt("Pasirinkimas: ", 1, 2);
    cout<<endl;

    if(m==1)
    {
        cout << "===== REZULTATAI =====\n";
        cout << "\nVardas       Pavarde      Galutinis (vid.)  Galutinis (med.)  \n\n";
        for (const auto &st : s)
        {
            double galVid =
                st.vidurkis * 0.4 +
                st.rezultatas * 0.6;

            double galMed =
                st.mediana * 0.4 +
                st.rezultatas * 0.6;

            cout << setw(12) << left;

            cout << st.vardas << " " << setw(12) << left << st.pavarde << " ";

            cout << setw(17) << left << std::setprecision(3);

            cout << galVid << " ";

            cout << galMed << endl;
        }
    }
    else
    {
        ofstream out ("isvedimas.txt");
        out << "===== REZULTATAI =====\n";
        out << "\nVardas       Pavarde      Galutinis (vid.)  Galutinis (med.)  \n\n";
        for (const auto &st : s)
        {
            double galVid =
                st.vidurkis * 0.4 +
                st.rezultatas * 0.6;

            double galMed =
                st.mediana * 0.4 +
                st.rezultatas * 0.6;

            out << setw(12) << left;

            out << st.vardas << " " << setw(12) << left << st.pavarde << " ";

            out << setw(17) << left << std::setprecision(3);

            out << galVid << " ";

            out << galMed << endl;
        }
    }
    return 0;
}
