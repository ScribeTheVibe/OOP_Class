#include <iostream>
#include <algorithm>
#include <ctime>
#include <string>
#include <cctype>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::sort;

struct studentas {
    string vardas, pavarde;
    int* pazimys = nullptr;
    int pazymiuKiekis = 0;
    int rezultatas = 0;
    double vidurkis = 0;
    double mediana = 0;

    ~studentas() {
        delete[] pazimys;
    }
};

double skaiciuotiMediana(int* arr, int kiekis)
{
    if (kiekis == 0) return 0;

    sort(arr, arr + kiekis);

    if (kiekis % 2 == 0)
        return (arr[kiekis / 2 - 1] + arr[kiekis / 2]) / 2.0;
    else
        return arr[kiekis / 2];
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
        cout << "Blogas ivedimas. Bandykite dar karta.\n";
    }
}

int main()
{
    srand(time(NULL));

    int n = 0;
    int m;

    cout << "Pasirinkite programos eiga\n";
    cout << "1 - ranka ivedami duomenys\n";
    cout << "2 - automatiskai sugeneruoti pazymius\n";
    cout << "3 - sugeneruoti studentus ir pazymius\n";
    cout << "4 - baigti darba\n";

    m = saugusInt("Pasirinkimas: ", 1, 4);

    if (m == 4) return 0;

    studentas* s = nullptr;

    if (m == 1)
    {
        string temp;

        while (true)
        {
            cout << "\nIveskite studento varda (arba 'exit'): ";
            cin >> temp;

            if (temp == "exit")
                break;

            studentas* naujas = new studentas[n + 1];

            for (int i = 0; i < n; i++)
                naujas[i] = s[i];

            delete[] s;
            s = naujas;

            s[n].vardas = temp;

            cout << "Iveskite pavarde: ";
            cin >> s[n].pavarde;

            int capacity = 10;
            int kiekis = 0;
            s[n].pazimys = new int[capacity];

            string input;

            cout << "Iveskite pazymius (exit - baigti):\n";

            while (true)
            {
                cin >> input;

                if (input == "exit")
                    break;

                bool valid = true;
                for (char c : input)
                    if (!isdigit(c)) valid = false;

                if (!valid)
                {
                    cout << "Blogas ivedimas.\n";
                    continue;
                }

                int pazymys = stoi(input);

                if (pazymys < 0 || pazymys > 10)
                {
                    cout << "Pazymys turi buti 0-10.\n";
                    continue;
                }

                if (kiekis == capacity)
                {
                    capacity *= 2;
                    int* tempArr = new int[capacity];

                    for (int i = 0; i < kiekis; i++)
                        tempArr[i] = s[n].pazimys[i];

                    delete[] s[n].pazimys;
                    s[n].pazimys = tempArr;
                }

                s[n].pazimys[kiekis++] = pazymys;
                s[n].vidurkis += pazymys;
            }

            if (kiekis == 0)
            {
                cout << "Nera pazymiu. Studentas praleistas.\n";
                delete[] s[n].pazimys;
                continue;
            }

            s[n].pazymiuKiekis = kiekis;
            s[n].vidurkis /= kiekis;

            s[n].rezultatas =
                saugusInt("Egzamino pazymys (0-10): ", 0, 10);

            s[n].mediana =
                skaiciuotiMediana(
                    s[n].pazimys,
                    s[n].pazymiuKiekis
                );

            n++;
        }
    }

    else
    {
        n = saugusInt("Studentu kiekis: ", 1, 1000000);
        int p = saugusInt("Pazymiu kiekis: ", 1, 1000);

        s = new studentas[n];

        for (int i = 0; i < n; i++)
        {
            if (m == 3)
            {
                s[i].vardas = "Vardas" + std::to_string(i + 1);
                s[i].pavarde = "Pavarde" + std::to_string(i + 1);
            }
            else
            {
                cout << "Vardas: ";
                cin >> s[i].vardas;
                cout << "Pavarde: ";
                cin >> s[i].pavarde;
            }

            s[i].pazimys = new int[p];
            s[i].pazymiuKiekis = p;

            for (int j = 0; j < p; j++)
            {
                s[i].pazimys[j] = rand() % 11;
                s[i].vidurkis += s[i].pazimys[j];
            }

            s[i].vidurkis /= p;
            s[i].rezultatas = rand() % 11;

            s[i].mediana =
                skaiciuotiMediana(s[i].pazimys, p);
        }
    }

    cout << "\n===== REZULTATAI =====\n";

    for (int i = 0; i < n; i++)
    {
        double galVid =
            s[i].vidurkis * 0.4 +
            s[i].rezultatas * 0.6;

        double galMed =
            s[i].mediana * 0.4 +
            s[i].rezultatas * 0.6;

        cout << "\n"
             << s[i].vardas << " "
             << s[i].pavarde << endl;

        cout << "Galutinis (vid.): "
             << galVid << endl;

        cout << "Galutinis (med.): "
             << galMed << endl;
    }

    delete[] s;

    return 0;
}
